#include "pd.h"

#include <string.h>

#include "helper.h"

#define PD_CC_INVALID 0xFFu

PD_CONTROL USBPD_Ctl = {0};

__attribute__ ((aligned(4))) uint8_t USBPD_Rx_Buf[34]; /* PD receive buffer */
__attribute__ ((aligned(4))) uint8_t USBPD_Tx_Buf[34]; /* PD send buffer */

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
    USBPD->DMA = (UINT32)(UINT8*)USBPD_Rx_Buf;
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


void USBPD_SendPack(const uint8_t is_async, const uint8_t* pbuf, const uint8_t len, const uint8_t sop)
{
    USBPD_LVE_ENABLE();

    USBPD->BMC_CLK_CNT = UPD_TMR_TX_96M;

    USBPD->DMA = (uint32_t)pbuf;
    USBPD->TX_SEL = sop;
    USBPD->BMC_TX_SZ = len;
    USBPD->CONTROL |= PD_TX_EN;
    USBPD->STATUS &= BMC_AUX_INVALID;
    USBPD->CONTROL |= BMC_START;
    if (!is_async)
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
    default:
        break;
    }
    if (USBPD_Ctl.Flag.Bit.Msg_Recvd)
    {
        USBPD_Ctl.Flag.Bit.Msg_Recvd = 0;
        USBPD_Ctl.Adapter_Idle_Cnt = 0x00;
        Message_Header h;
        h.Data = (uint16_t)USBPD_Rx_Buf[0] | ((uint16_t)USBPD_Rx_Buf[1] << 8);
        switch (h.Message_Header.MsgType)
        {
        case DEF_TYPE_SRC_CAP:
            {
                break;
            }
        default:
            break;
        }
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
                    h.Message_Header.MsgID = (USBPD_Rx_Buf[1] >> 1) & 0b1110;
                    h.Message_Header.SpecRev = USBPD_Ctl.Flag.Bit.PD_Version ? 0b10 : 0b01;
                    static uint8_t ack[2];
                    ack[0] = (uint8_t)(h.Data & 0xFF);
                    ack[1] = (uint8_t)((h.Data >> 8) & 0xFF);

                    USBPD->CONFIG |= IE_TX_END;
                    USBPD_SendPack(0, ack, sizeof(ack), UPD_SOP0);
                    // PD_Phy_SendPack(0, USBPD_Tx_Buf, 2, UPD_SOP0);
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
        NVIC_DisableIRQ(USBPD_IRQn);
        USBPD_Ctl.Flag.Bit.Msg_Recvd = 1;
        USBPD_CLEAR_STATUS(IF_TX_END);
    }

    if (USBPD_STATUS(BUF_ERR))
    {
        printf("BUFERR Reload\r\n");
        USBPD_Init();
    }
}
