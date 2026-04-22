#include "pd.h"

#include <string.h>

#include "pd_helper.h"

#define PD_CC_INVALID 0xFFu
#define USBPD_REQ_USB_COMM_CAPABLE 1u
#define USBPD_REQ_NO_USB_SUSPEND 1u

PD_CONTROL USBPD_Ctl = {0};

__attribute__ ((aligned(4))) uint8_t USBPD_Rx_Buf[34]; /* PD receive buffer */
__attribute__ ((aligned(4))) uint8_t USBPD_Tx_Buf[34]; /* PD send buffer */

extern uint8_t Tmr_Ms_Dlt;
extern uint8_t Tmr_Ms_Cnt_Last;

__attribute__((weak)) void PD_Detect_EventCallback(const PD_DetectEventType event, const uint8_t cc)
{
    (void)event;
    (void)cc;
}

uint8_t USBPD_GetCcCmpFlags(volatile uint16_t* port_reg, GPIO_TypeDef* gpiox, uint16_t gpio_pin)
{
    uint8_t cmp = 0;

    PD_CC_CHECK_AND_RUN((*port_reg), CC_CMP_22,
                        {
                        cmp |= bCC_CMP_22;
                        });
    PD_CC_CHECK_AND_RUN((*port_reg), CC_CMP_66,
                        {
                        cmp |= bCC_CMP_66;
                        });

    if (GPIO_ReadInputDataBit(gpiox, gpio_pin) != Bit_RESET)
    {
        cmp |= bCC_CMP_220;
    }

    return cmp;
}

void USBPD_Rx_Mode(void)
{
    USBPD->CONFIG |= PD_ALL_CLR;
    USBPD->CONFIG &= ~PD_ALL_CLR;
    USBPD->CONFIG |= IE_RX_ACT | IE_RX_RESET | PD_DMA_EN;
    USBPD->DMA = (uint32_t)(uint8_t*)USBPD_Rx_Buf;
    USBPD->CONTROL &= ~PD_TX_EN;
    USBPD->BMC_CLK_CNT = UPD_TMR_RX_96M;
    USBPD->CONTROL |= BMC_START;
    NVIC_EnableIRQ(USBPD_IRQn);
}

void USBPD_Flag_Init()
{
    USBPD_Ctl.Flag.Bit.PR_Role = 0; /* SINK mode */
    USBPD_Ctl.Flag.Bit.Auto_Ack_PRRole = 0; /* Default auto-responder role is SINK */
    USBPD->PORT_CC1 = CC_CMP_66 | CC_PD;
    USBPD->PORT_CC2 = CC_CMP_66 | CC_PD;
}

void USBPD_Flag_Reset(void)
{
    USBPD_Flag_Init();
    USBPD_Ctl.Flag.Bit.Stop_Det_Chk = 0; /* PD disconnection detection is enabled by default */
    USBPD_Ctl.PD_State = STA_IDLE; /* Set idle state */
    USBPD_Ctl.Flag.Bit.PD_Comm_Succ = 0;
}

void USBPD_SendPack(const uint8_t sync_mode, const uint8_t* pbuf, const uint8_t len, const uint8_t sop)
{
    USBPD_LVE_ENABLE();

    USBPD->BMC_CLK_CNT = UPD_TMR_TX_96M;

    USBPD->DMA = (uint32_t)pbuf;
    USBPD->TX_SEL = sop;
    USBPD->BMC_TX_SZ = len;
    USBPD->CONTROL |= PD_TX_EN;
    USBPD->STATUS &= BMC_AUX_INVALID;
    USBPD->CONTROL |= BMC_START;
    if (sync_mode)
    {
        while (!USBPD_STATUS(IF_TX_END))
        {
        }
        USBPD_CLEAR_STATUS(IF_TX_END);
        USBPD_LVE_DISABLE();
        USBPD_Rx_Mode();
    }
}

void USBPD_DisConnect(void)
{
    USBPD_Ctl.Det_Cnt = 0;
    const uint8_t active_cc = ((USBPD->CONFIG & CC_SEL) == 0u) ? DEF_PD_CC1 : DEF_PD_CC2;
    USBPD_Ctl.Flag.Bit.Connected = 0;
    PD_Detect_EventCallback(PD_EVENT_DETACH, active_cc);
    if (USBPD_Ctl.Flag.Bit.Stop_Det_Chk == 0)
    {
        USBPD_Ctl.PD_State = STA_DISCONNECT;
    }
}

void USBPD_Detect_Check(void)
{
    uint8_t ret = PD_CC_INVALID;
    const uint8_t cc1 = USBPD_GetCcCmpFlags(&USBPD->PORT_CC1, CC_PORT, CC1_PIN);
    const uint8_t cc2 = USBPD_GetCcCmpFlags(&USBPD->PORT_CC2, CC_PORT, CC2_PIN);
    if (PD_CC_IN_066_220(cc1) && !PD_CC_IN_022(cc2))
    {
        ret = DEF_PD_CC1;
    }

    if (PD_CC_IN_066_220(cc2) && !PD_CC_IN_022(cc1))
    {
        ret = DEF_PD_CC2;
    }
    if (USBPD_Ctl.Flag.Bit.Connected)
    {
        /* 已连接时，ret 需要与当前选中的 CC 通道一致，否则判定为异常/疑似断开 */
        if (((USBPD->CONFIG & CC_SEL) == 0u && ret == DEF_PD_CC1) ||
            ((USBPD->CONFIG & CC_SEL) != 0u && ret == DEF_PD_CC2))
        {
            USBPD_Ctl.Det_Cnt = 0;
        }
        else
        {
            USBPD_Ctl.Det_Cnt++;
            if (USBPD_Ctl.Det_Cnt >= 5u)
            {
                USBPD_DisConnect();
            }
        }
    }
    else
    {
        if (ret == PD_CC_INVALID)
        {
            USBPD_Ctl.Det_Cnt = 0;
        }
        else
        {
            USBPD_Ctl.Det_Cnt++;
        }
        // PRINT("ret %d Det_cnt :%d\r\n", ret, PD_Ctl.Det_Cnt);
        if (USBPD_Ctl.Det_Cnt >= 5)
        {
            USBPD_Ctl.Det_Cnt = 0;
            USBPD_Ctl.Flag.Bit.Connected = 1;
            if (ret == DEF_PD_CC1)
            {
                USBPD->CONFIG &= ~CC_SEL;
            }
            else
            {
                USBPD->CONFIG |= CC_SEL;
            }
            PD_Detect_EventCallback(PD_EVENT_ATTACH, ret);
            if (USBPD_Ctl.Flag.Bit.Stop_Det_Chk == 0u)
            {
                USBPD_Ctl.PD_State = STA_SRC_CONNECT;
            }
        }
    }
}

void USBPD_Init(void)
{
    RCC_HBPeriphClockCmd(RCC_HBPeriph_USBPD, ENABLE);
    RCC_PB2PeriphClockCmd(RCC_PB2Periph_AFIO, ENABLE);
    RCC_PB2PeriphClockCmd(RCC_PB2Periph_GPIOB, ENABLE);

    GPIO_InitTypeDef GPIO_InitStructure = {0};
    GPIO_InitStructure.GPIO_Pin = CC1_PIN | CC2_PIN;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(CC_PORT, &GPIO_InitStructure);

    AFIO->CR |= USBPD_IN_HVT;
    // USBPD->CONFIG = PD_DMA_EN;
    USBPD->STATUS &= BMC_AUX_INVALID;

    memset(&USBPD_Ctl, 0, sizeof(PD_CONTROL));
    USBPD_SendPack(0, NULL, 0, UPD_SOP0); /* 进入 PD 通信模式，发送一个空包作为触发，进入接收状态 */
    USBPD_Flag_Init();
    // NVIC_EnableIRQ(USBPD_IRQn);
    USBPD_IQR_DISABLE();
    USBPD_Rx_Mode();
}

void USBPD_Detect_Process(void)
{
    USBPD_Detect_Check();
    // if (PD_Ctl.Flag.Bit.Connected)
    // {
    // }
    // else
    // {
    // }
}

void USBPD_Main_Proc(void)
{
    switch (USBPD_Ctl.PD_State)
    {
    case STA_SRC_CONNECT:
        {
            USBPD_Ctl.PD_Comm_Timer += Tmr_Ms_Dlt;
            if (USBPD_Ctl.PD_Comm_Timer > 999)
            {
                /* Retry on exception (abort after 5 attempts) */
                USBPD_Ctl.Err_Op_Cnt++;
                if (USBPD_Ctl.Err_Op_Cnt > 5)
                {
                    USBPD_Ctl.Err_Op_Cnt = 0;
                    USBPD_Ctl.PD_State = STA_IDLE;
                    PRINT("No SRC,PD Idle\r\n");
                }
                else
                {
                    USBPD_Flag_Reset();
                }
            }
            break;
        }
    default:
        break;
    }
    if (USBPD_Ctl.Flag.Bit.Msg_Recvd)
    {
        USBPD_Ctl.Flag.Bit.Msg_Recvd = 0;
        USBPD_Ctl.Adapter_Idle_Cnt = 0x00;
        Message_Header h;
        h.raw = (uint16_t)USBPD_Rx_Buf[0] | ((uint16_t)USBPD_Rx_Buf[1] << 8);
        switch (h.Message_Header.MsgType)
        {
        case DEF_TYPE_SRC_CAP:
            {
                if (h.Message_Header.NumDO == 0u)
                {
                    /* MsgType=1 also matches GoodCRC(control msg), skip it here. */
                    break;
                }
                PRINT("Received SRC_CAP\r\n");
                // USBPD_PDO_Analyse(USBPD_Rx_Buf);
                const uint8_t pdo_index = USBPD_FIND_5V_PDO(USBPD_Rx_Buf);
                if (pdo_index)
                {
                    const Message_Header req = {
                        .Message_Header = {
                            .MsgType = DEF_TYPE_REQUEST,
                            .NumDO = 1,
                            .PDRole = 0,
                            .PRRole = 0,
                            .SpecRev = h.Message_Header.SpecRev,
                            .MsgID = USBPD_Ctl.Msg_ID & 0x07u,
                            .Ext = 0,
                        }
                    };


                    /* USBPD_FIND_5V_PDO guarantees selected PDO is Fixed 5V. */
                    const uint32_t pdo_raw = USBPD_READ_U32_LE(&USBPD_Rx_Buf[2u + (uint8_t)((pdo_index - 1u) * 4u)]);
                    USBPD_PDO_Fixed5V_Source fpdo;
                    fpdo.Raw = pdo_raw;
                    const uint32_t op_cur = fpdo.Bit.MaxCurrentIn10mA;
                    const USBPD_RDO_FixedVariable rdo_obj = {
                        .Bit.MaxOperatingCurrentIn10mA = op_cur,
                        .Bit.OperatingCurrentIn10mA = op_cur,
                        .Bit.USBCommCapable = USBPD_REQ_USB_COMM_CAPABLE,
                        .Bit.NoUSBSuspend = USBPD_REQ_NO_USB_SUSPEND,
                        .Bit.ObjectPosition = (uint32_t)(pdo_index & 0x0Fu),
                    };

                    uint8_t req_buf[6];
                    memcpy(&req_buf[0], &req.raw, sizeof(req.raw));
                    memcpy(&req_buf[2], &rdo_obj.Raw, sizeof(rdo_obj.Raw));

                    USBPD_LVE_DISABLE();
                    USBPD_SendPack(1, req_buf, sizeof(req_buf), UPD_SOP0);
                    // USBPD_Ctl.Msg_ID = (uint8_t)((USBPD_Ctl.Msg_ID + 1u) & 0x07u);
                }
                PRINT("Requested PDO index %d\r\n", pdo_index);
                break;
            }
        case DEF_TYPE_ACCEPT:
            {
                PRINT("Received ACCEPT\r\n");
                break;
            }
        case DEF_TYPE_PS_RDY:
            {
                PRINT("Received PS_RDY\r\n");
                break;
            }
        case DEF_TYPE_SOFT_RESET:
            {
                PRINT("Received SOFT_RESET\r\n");
                break;
            }
        default:
            break;
        }
        /*
         * Do not blindly reset RX here:
         * - REQUEST path already re-enters RX inside USBPD_SendPack(sync=1)
         * - calling USBPD_Rx_Mode() again may clear a just-arrived GoodCRC/ACCEPT
         *   (PD_ALL_CLR) before IRQ handles it.
         * Re-enter RX only when still in TX state.
         */
        if (USBPD->CONTROL & PD_TX_EN)
        {
            USBPD_Rx_Mode();
        }
        USBPD_Ctl.Flag.Bit.Msg_Recvd = 0;
    }
}


__attribute__((interrupt("WCH-Interrupt-fast"))) void USBPD_IRQHandler(void)
{
    if (USBPD_STATUS(IF_RX_ACT))
    {
        USBPD_CLEAR_STATUS(IF_RX_ACT);
        // USBPD_Ctl.Flag.Bit.Msg_Recvd = 1; /* Packet received flag */
        // USBPD_Ctl.Adapter_Idle_Cnt = 0x00; /* Idle time cleared */
        if (USBPD_SOP0())
        {
            if (USBPD_BMC_CNT() >= 6)
            {
                if (!(USBPD_HEADER_MESSAGE_TYPE(USBPD_Rx_Buf) == DEF_TYPE_GOODCRC && USBPD_BMC_CNT() == 6))
                {
                    Delay_Us(30); /* Delay 30us, answer GoodCRC */

                    Message_Header h = kGoodCrcBase;
                    h.Message_Header.PRRole = USBPD_Ctl.Flag.Bit.Auto_Ack_PRRole;
                    h.Message_Header.MsgID = (USBPD_Rx_Buf[1] & 0b1110) >> 1;
                    /* PD_Version: 0=PD2.0(01b), 1=PD3.0(10b) */
                    h.Message_Header.SpecRev = USBPD_Ctl.Flag.Bit.PD_Version ? 0b10 : 0b01;
                    static uint8_t ack[2];
                    ack[0] = (uint8_t)(h.raw & 0xFF);
                    ack[1] = (uint8_t)((h.raw >> 8) & 0xFF);

                    USBPD->CONFIG |= IE_TX_END;
                    USBPD_SendPack(0, ack, sizeof(ack), UPD_SOP0);
                }
            }
        }
    }
    if (USBPD_STATUS(IF_RX_RESET))
    {
        USBPD_CLEAR_STATUS(IF_RX_RESET);
        USBPD_Flag_Reset();
        printf("IF_RX_RESET\r\n");
    }
    if (USBPD_STATUS(IF_TX_END))
    {
        // 只有发送goodcrc才会使用异步发送，其他发送都是同步发送，在发送函数中等待发送完成
        USBPD_LVE_DISABLE();
        /* Interrupts are turned off and can be turned on after the main function has finished processing the data */
        // NVIC_DisableIRQ(USBPD_IRQn);
        USBPD_Ctl.Flag.Bit.Msg_Recvd = 1;
        USBPD_CLEAR_STATUS(IF_TX_END);
    }

    if (USBPD_STATUS(BUF_ERR))
    {
        printf("BUFERR Reload\r\n");
        USBPD_Init();
    }
}
