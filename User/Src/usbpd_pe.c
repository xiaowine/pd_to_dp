#include "usbpd_pe.h"
#include <string.h>
#include "pd_pdo.h"
#include "pd_rdo.h"
#include "tim.h"
#include "usbpd_phy.h"
#include "usbpd_helper.h"

__attribute__ ((aligned(4))) uint8_t pe_rx_buf[PD_BUF_SIZE];
__attribute__ ((aligned(4))) uint8_t pe_tx_buf[PD_BUF_SIZE];


void USBPD_PE_Init(void)
{
    USBPD_Phy_SetRxBuffer(pe_rx_buf);
}

void USBPD_PE_Reset(void)
{
    USBPD_Control.PD_State = STA_IDLE;
    USBPD_Control.Flag.PR_Role = 0;
    USBPD_Control.Flag.PD_Role = 0;
    USBPD_Control.Flag.Auto_Ack_PRRole = 0;
    USBPD_Control.Flag.PD_Version = 0;
    USBPD_Control.Flag.VDM_Version = 0;
    USBPD_Control.Flag.PD_Comm_Succ = 0;
}

void USBPD_PE_Run(void)
{
    switch (USBPD_Control.PD_State)
    {
    case STA_DISCONNECT:
        {
            break;
        }
    case STA_SRC_CONNECT:
        {
            USBPD_Control.PD_Comm_Timer += USBPD_Tim_Ms_Cnt;
            if (USBPD_Control.PD_Comm_Timer > 999)
            {
                USBPD_Control.PD_Comm_Timer = 0;
                USBPD_Control.Err_Op_Cnt++;
                if (USBPD_Control.Err_Op_Cnt > 5)
                {
                    USBPD_Control.Err_Op_Cnt = 0;
                    USBPD_Control.PD_State = STA_IDLE;
                }
                else
                {
                    USBPD_PE_Reset();
                }
            }
            break;
        }
    case STA_TX_GOODCRC:
        {
            Message_Header header = {0};
            header.Message_Header.MsgType = DEF_TYPE_GOODCRC;
            header.Message_Header.NumDO = 0;
            header.Message_Header.PDRole = USBPD_Control.Flag.PD_Role;
            header.Message_Header.SpecRev = USBPD_Control.Flag.PD_Version;
            header.Message_Header.PRRole = USBPD_Control.Flag.PR_Role;
            header.Message_Header.MsgID = USBPD_Control.Msg_ID & 0x07u;
            memcpy(pe_tx_buf, &header.raw, 2);
            USBPD_Phy_TxPacket(pe_tx_buf, 2, UPD_SOP0, 1);
            SWITCH_PD_STATE(STA_IDLE);
            USBPD_Phy_EnterRxMode();
            break;
        }
    case STA_TX_REQ:
        {
            const uint8_t pdo_index = USBPD_FIND_5V_PDO(pe_rx_buf);
            if (pdo_index)
            {
                const Message_Header header = {
                    .Message_Header = {
                        .MsgType = DEF_TYPE_REQUEST,
                        .NumDO = 0,
                        .PDRole = USBPD_Control.Flag.PD_Role,
                        .SpecRev = USBPD_Control.Flag.PD_Version,
                        .PRRole = USBPD_Control.Flag.PR_Role,
                        .MsgID = USBPD_Control.Msg_ID & 0x07u,
                        .Ext = 0,
                    }
                };

                /* USBPD_FIND_5V_PDO guarantees selected PDO is Fixed 5V. */
                const uint32_t pdo_raw = USBPD_READ_LE32(&pe_rx_buf[2u + (uint8_t)((pdo_index - 1u) * 4u)]);
                USBPD_PDO_Fixed5V_Source fpdo;
                fpdo.Raw = pdo_raw;
                const uint32_t op_cur = fpdo.Bit.MaxCurrentIn10mA;
                const USBPD_RDO_FixedVariable rdo_obj = {
                    .Bit.MaxOperatingCurrentIn10mA = op_cur,
                    .Bit.OperatingCurrentIn10mA = op_cur,
                    .Bit.USBCommCapable = 1,
                    .Bit.NoUSBSuspend = 1,
                    .Bit.ObjectPosition = (uint32_t)(pdo_index & 0x0Fu),
                };
                memset(pe_tx_buf, 0, sizeof(pe_tx_buf));
                memcpy(&pe_tx_buf[0], &header.raw, sizeof(header.raw));
                memcpy(&pe_tx_buf[2], &rdo_obj.Raw, sizeof(rdo_obj.Raw));
                USBPD_Phy_TxPacket(pe_tx_buf, sizeof(pe_tx_buf),UPD_SOP0, 1);
                SWITCH_PD_STATE(STA_IDLE);
                USBPD_Phy_EnterRxMode();
            }
            break;
        }
    default: break;
    }
    if (USBPD_Control.Flag.Msg_Recvd)
    {
        switch (USBPD_MSG_TYPE_FROM_HEADER(pe_rx_buf))
        {
        case DEF_TYPE_SRC_CAP:
            {
                SWITCH_PD_STATE(STA_TX_REQ);
                USBPD_PDO_Analyse(pe_rx_buf);
                break;
            }
        case DEF_TYPE_SOFT_RESET:
            {
                USBPD_PE_Reset();
                break;
            }
        default: break;
        }
        USBPD_Control.Msg_ID++;
        USBPD_Control.Flag.Msg_Recvd = 0;
    }
}

__attribute__((interrupt("WCH-Interrupt-fast")))void USBPD_IRQHandler(void)
{
    if (USBPD_STATUS_HAS_FLAG(IF_RX_ACT))
    {
        USBPD_STATUS_CLEAR_FLAG(IF_RX_ACT);
        Message_Header header = {0};
        header.raw = USBPD_READ_LE16(pe_rx_buf);
        // GOODCRC 报文的 NumDO 字段为 0，且报文类型为 GOODCRC 时不通知主程序接收消息，以免干扰正常通信流程中的 GOODCRC 应答
        if (!(header.Message_Header.NumDO == 0u && header.Message_Header.MsgType == DEF_TYPE_GOODCRC))
        {
            SWITCH_PD_STATE(STA_TX_GOODCRC);
            USBPD_Control.Flag.Msg_Recvd = 1;
        }
    }
    if (USBPD_STATUS_HAS_FLAG(IF_RX_RESET))
    {
        PRINT("IF_RX_RESET\r\n");
        USBPD_STATUS_CLEAR_FLAG(IF_RX_RESET);
        /* RX 状态异常时重新进入接收模式，避免卡死在异常状态 */
        USBPD_Phy_EnterRxMode();
    }
    if (USBPD_STATUS_HAS_FLAG(IF_TX_END))
    {
        PRINT("IF_TX_END\r\n");
        USBPD_STATUS_CLEAR_FLAG(IF_TX_END);
    }
    if (USBPD_STATUS_HAS_FLAG(BUF_ERR))
    {
        PRINT("BUFERR\r\n");
        NVIC_SystemReset();
    }
}
