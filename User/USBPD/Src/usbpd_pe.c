#include "usbpd_pe.h"
#include <string.h>
#include "pd_pdo.h"
#include "pd_rdo.h"
#include "tim.h"
#include "usbpd_phy.h"
#include "usbpd_helper.h"
#include "usbpd_hpd.h"
#include "usbpd_vdm_handler.h"
#include "vl171.h"

__attribute__ ((aligned(4))) uint8_t pe_rx_buf[PD_BUF_SIZE];
__attribute__ ((aligned(4))) uint8_t pe_tx_buf[PD_BUF_SIZE];
Message_Header last_rx_header = {0};

static void USBPD_PE_ResetProtocolLayer(void)
{
    USBPD_Control.Msg_ID = 0u;
    USBPD_Control.Tx_GoodCRC_MsgID = 0xFFu;
    USBPD_Control.Rx_Last_MsgID = 0xFFu;
    USBPD_Control.Flag.Msg_Recvd = 0u;
    USBPD_Control.Flag.Tx_GoodCRC_Received = 0u;
    USBPD_Control.Flag.Rx_MsgID_Valid = 0u;
    memset(pe_rx_buf, 0, sizeof(pe_rx_buf));
    memset(pe_tx_buf, 0, sizeof(pe_tx_buf));
    last_rx_header.raw = 0u;
}

static Message_Header USBPD_PE_BuildHeader(uint8_t msg_type, uint8_t num_do)
{
    const Message_Header header = {
        .Message_Header = {
            .MsgType = msg_type,
            .NumDO = num_do,
            .PDRole = USBPD_Control.Flag.PD_Role,
            .SpecRev = USBPD_Control.Flag.PD_Version ? 0b10 : 0b01,
            .PRRole = USBPD_Control.Flag.PR_Role,
            .MsgID = USBPD_Control.Msg_ID & 0x07u,
            .Ext = 0,
        }
    };

    return header;
}

static uint8_t USBPD_PE_SendControlMessage(uint8_t msg_type)
{
    const Message_Header header = USBPD_PE_BuildHeader(msg_type, 0u);

    memcpy(pe_tx_buf, &header.raw, sizeof(header.raw));
    if (USBPD_Phy_TxMessageWaitGoodCRC(pe_tx_buf, 2u, UPD_SOP0) == DEF_PD_TX_OK)
    {
        USBPD_Control.Msg_ID = (uint8_t)((USBPD_Control.Msg_ID + 1u) & 0x07u);
        return DEF_PD_TX_OK;
    }

    return DEF_PD_TX_FAIL;
}

static uint8_t USBPD_PE_SendSinkCapabilities(void)
{
    const Message_Header header = USBPD_PE_BuildHeader(DEF_TYPE_SNK_CAP, 1u);
    const USBPD_PDO_Fixed5V_Sink sink_pdo = {
        .Bit = {
            .OperationalCurrentIn10mA = 100u,
            .VoltageIn50mV = 100u,
            .USBCommCapable = 1u,
        }
    };

    memcpy(&pe_tx_buf[0], &header.raw, sizeof(header.raw));
    memcpy(&pe_tx_buf[2], &sink_pdo.Raw, sizeof(sink_pdo.Raw));
    if (USBPD_Phy_TxMessageWaitGoodCRC(pe_tx_buf, 6u, UPD_SOP0) == DEF_PD_TX_OK)
    {
        USBPD_Control.Msg_ID = (uint8_t)((USBPD_Control.Msg_ID + 1u) & 0x07u);
        return DEF_PD_TX_OK;
    }

    return DEF_PD_TX_FAIL;
}

static void USBPD_PE_StartProtocolRecovery(void)
{
    (void)USBPD_PE_SendControlMessage(DEF_TYPE_SOFT_RESET);
    USBPD_PE_ResetProtocolLayer();
    USBPD_Control.Flag.Explicit_Contract = 0u;
    if (USBPD_Control.Flag.Connected)
    {
        SWITCH_PD_STATE(STA_RX_SRC_CAP_WAIT);
    }
    else
    {
        SWITCH_PD_STATE(STA_DISCONNECT);
    }
}

void USBPD_PE_Init(void)
{
    USBPD_Phy_SetRxBuffer(pe_rx_buf);
    USBPD_Control.Flag.PD_Version = 1; /* 默认使用 PD3.0 版本进行通信 */
    USBPD_PE_ResetProtocolLayer();
}

void USBPD_PE_Reset(void)
{
    USBPD_Control.PD_State = STA_IDLE;
    USBPD_Control.Flag.PR_Role = 0;
    USBPD_Control.Flag.PD_Role = 0;
    USBPD_Control.Flag.Auto_Ack_PRRole = 0;
    USBPD_Control.Flag.VDM_Version = 0;
    USBPD_Control.Flag.PD_Comm_Succ = 0;
    USBPD_Control.Flag.Explicit_Contract = 0;
    USBPD_Control.Flag.DP_Modes_Discovered = 0;
    USBPD_Control.Mode_Try_Cnt &= (uint8_t)~0x80u;
    USBPD_PE_ResetProtocolLayer();
    USBPD_HPD_Reset();
    VL171_ApplyMode(VL171_MODE_USB);
}

void STA_Connect(void)
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
}

void STA_Tx_GoodCRC(void)
{
    const CC_STATUS resume_state = USBPD_Control.PD_State_Last;
    const Message_Header header = {
        .Message_Header = {
            .MsgType = DEF_TYPE_GOODCRC,
            .NumDO = 0,
            .PDRole = USBPD_Control.Flag.PD_Role,
            .SpecRev = USBPD_Control.Flag.PD_Version ? 0b10 : 0b01,
            .PRRole = USBPD_Control.Flag.PR_Role,
            .MsgID = last_rx_header.Message_Header.MsgID & 0x07u,
            .Ext = 0,
        }
    };
    memcpy(pe_tx_buf, &header.raw, 2);
    USBPD_Phy_TxPacket(pe_tx_buf, 2, UPD_SOP0, 1);
    USBPD_Control.PD_State = resume_state;
}

void STA_Req(void)
{
    const uint8_t pdo_index = USBPD_FIND_5V_PDO(pe_rx_buf);
    if (pdo_index)
    {
        const Message_Header header = USBPD_PE_BuildHeader(DEF_TYPE_REQUEST, 1u);

        /* USBPD_FIND_5V_PDO guarantees selected PDO is Fixed 5V. */
        const uint32_t pdo_raw = USBPD_READ_LE32(&pe_rx_buf[2u + (uint8_t)((pdo_index - 1u) * 4u)]);
        USBPD_PDO_Fixed5V_Source fpdo;
        fpdo.Raw = pdo_raw;
        const uint32_t op_cur = fpdo.Bit.MaxCurrentIn10mA;
        if (op_cur == 0u)
        {
            SWITCH_PD_STATE(STA_RX_SRC_CAP_WAIT);
            return;
        }
        const USBPD_RDO_FixedVariable rdo_obj = {
            .Bit.MaxOperatingCurrentIn10mA = op_cur,
            .Bit.OperatingCurrentIn10mA = op_cur,
            .Bit.USBCommCapable = 1,
            .Bit.NoUSBSuspend = 1,
            .Bit.CapabilityMismatch = fpdo.Bit.USBCommCapable ? 0u : 1u,
            .Bit.ObjectPosition = (uint32_t)(pdo_index & 0x0Fu),
        };
        memcpy(&pe_tx_buf[0], &header.raw, sizeof(header.raw));
        memcpy(&pe_tx_buf[2], &rdo_obj.Raw, sizeof(rdo_obj.Raw));
        if (USBPD_Phy_TxMessageWaitGoodCRC(pe_tx_buf, 6u, UPD_SOP0) == DEF_PD_TX_OK)
        {
            USBPD_Control.Msg_ID = (uint8_t)((USBPD_Control.Msg_ID + 1u) & 0x07u);
            SWITCH_PD_STATE(STA_RX_ACCEPT_WAIT);
            return;
        }
    }
    SWITCH_PD_STATE(STA_IDLE);
}

void STA_Vdm(void)
{
    USBPD_VDM_Handle(pe_rx_buf, pe_tx_buf, &last_rx_header);
    SWITCH_PD_STATE(STA_IDLE);
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
            STA_Connect();
            break;
        }
    case STA_RX_SRC_CAP_WAIT:
        {
            break;
        }
    case STA_RX_ACCEPT_WAIT:
    case STA_RX_PS_RDY_WAIT:
        {
            break;
        }
    case STA_TX_GOODCRC:
        {
            STA_Tx_GoodCRC();
            break;
        }
    case STA_TX_REQ:
        {
            STA_Req();
            break;
        }
    case STA_VDM:
        {
            STA_Vdm();
            break;
        }
    default: break;
    }
    if (USBPD_Control.Flag.Msg_Recvd)
    {
        const uint8_t msg_type = USBPD_MSG_TYPE_FROM_HEADER(pe_rx_buf);

        if (last_rx_header.Message_Header.Ext)
        {
            USBPD_PE_SendControlMessage(DEF_TYPE_NOT_SUPPORT);
            USBPD_Control.Flag.Msg_Recvd = 0;
            return;
        }

        /* NumDO==0: Control Message, NumDO>0: Data Message */
        if (last_rx_header.Message_Header.NumDO == 0u)
        {
            switch (msg_type)
            {
            case DEF_TYPE_SOFT_RESET:
                {
                    USBPD_PE_ResetProtocolLayer();
                    USBPD_Control.Flag.Explicit_Contract = 0u;
                    USBPD_PE_SendControlMessage(DEF_TYPE_ACCEPT);
                    SWITCH_PD_STATE(STA_RX_SRC_CAP_WAIT);
                    break;
                }
            case DEF_TYPE_ACCEPT:
                {
                    PRINT("ACCEPT received\r\n");
                    if (USBPD_Control.PD_State == STA_RX_ACCEPT_WAIT)
                    {
                        SWITCH_PD_STATE(STA_RX_PS_RDY_WAIT);
                    }
                    else
                    {
                        USBPD_PE_StartProtocolRecovery();
                    }
                    break;
                }
            case DEF_TYPE_REJECT:
            case DEF_TYPE_WAIT:
                {
                    PRINT("REJECT/WAIT received\r\n");
                    if (USBPD_Control.PD_State == STA_RX_ACCEPT_WAIT)
                    {
                        SWITCH_PD_STATE(USBPD_Control.Flag.Explicit_Contract ? STA_IDLE : STA_RX_SRC_CAP_WAIT);
                    }
                    else
                    {
                        USBPD_PE_StartProtocolRecovery();
                    }
                    break;
                }
            case DEF_TYPE_PS_RDY:
                {
                    PRINT("PS_RDY received\r\n");
                    if (USBPD_Control.PD_State == STA_RX_PS_RDY_WAIT)
                    {
                        USBPD_Control.Flag.Explicit_Contract = 1u;
                        SWITCH_PD_STATE(STA_IDLE);
                    }
                    else
                    {
                        USBPD_PE_StartProtocolRecovery();
                    }
                    break;
                }
            case DEF_TYPE_GET_SNK_CAP:
                {
                    USBPD_PE_SendSinkCapabilities();
                    break;
                }
            case DEF_TYPE_DR_SWAP:
            case DEF_TYPE_PR_SWAP:
            case DEF_TYPE_VCONN_SWAP:
                {
                    USBPD_PE_SendControlMessage(DEF_TYPE_REJECT);
                    break;
                }
            default:
                {
                    USBPD_PE_SendControlMessage(DEF_TYPE_NOT_SUPPORT);
                    break;
                }
            }
        }
        else
        {
            switch (msg_type)
            {
            case DEF_TYPE_SRC_CAP:
                {
                    PRINT("SRC_CAP received\r\n");
                    if (USBPD_Control.PD_State == STA_RX_SRC_CAP_WAIT ||
                        (USBPD_Control.Flag.Explicit_Contract && USBPD_Control.PD_State == STA_IDLE))
                    {
                        SWITCH_PD_STATE(STA_TX_REQ);
                        USBPD_PDO_Analyse(pe_rx_buf);
                    }
                    else
                    {
                        USBPD_PE_StartProtocolRecovery();
                    }
                    break;
                }
            case DEF_TYPE_VENDOR_DEFINED:
                {
                    PRINT("Vendor Defined Message received\r\n");
                    if (USBPD_Control.Flag.Explicit_Contract && USBPD_Control.PD_State == STA_IDLE)
                    {
                        SWITCH_PD_STATE(STA_VDM);
                    }
                    else
                    {
                        USBPD_PE_StartProtocolRecovery();
                    }
                    break;
                }
            default:
                {
                    USBPD_PE_SendControlMessage(DEF_TYPE_NOT_SUPPORT);
                    break;
                }
            }
        }
        USBPD_Control.Flag.Msg_Recvd = 0;
    }

    if (!USBPD_Control.Flag.Msg_Recvd && USBPD_Control.PD_State == STA_IDLE &&
        USBPD_Control.Flag.Explicit_Contract)
    {
        USBPD_VDM_TrySendAttention(pe_tx_buf);
    }
}

__attribute__((interrupt("WCH-Interrupt-fast")))void USBPD_IRQHandler(void)
{
    if (USBPD_STATUS_HAS_FLAG(IF_RX_ACT))
    {
        USBPD_STATUS_CLEAR_FLAG(IF_RX_ACT);
        if (USBPD_STATUS_IS_SOP0())
        {
            last_rx_header.raw = USBPD_READ_LE16(pe_rx_buf);

            if (last_rx_header.Message_Header.NumDO == 0u &&
                last_rx_header.Message_Header.MsgType == DEF_TYPE_GOODCRC)
            {
                USBPD_Control.Tx_GoodCRC_MsgID = last_rx_header.Message_Header.MsgID & 0x07u;
                USBPD_Control.Flag.Tx_GoodCRC_Received = 1u;
            }
            else
            {
                SWITCH_PD_STATE(STA_TX_GOODCRC);
                const uint8_t rx_msg_id = last_rx_header.Message_Header.MsgID & 0x07u;
                if (USBPD_Control.Flag.Rx_MsgID_Valid &&
                    ((USBPD_Control.Rx_Last_MsgID & 0x07u) == rx_msg_id))
                {
                    /* Duplicate retry: GoodCRC it again, but do not deliver it to PE. */
                }
                else
                {
                    USBPD_Control.Rx_Last_MsgID = rx_msg_id;
                    USBPD_Control.Flag.Rx_MsgID_Valid = 1u;
                    USBPD_Control.Flag.Msg_Recvd = 1;
                }
            }
        }
    }
    if (USBPD_STATUS_HAS_FLAG(IF_RX_RESET))
    {
        PRINT("IF_RX_RESET\r\n");
        USBPD_STATUS_CLEAR_FLAG(IF_RX_RESET);
        USBPD_PE_Reset();
        if (USBPD_Control.Flag.Connected)
        {
            SWITCH_PD_STATE(STA_RX_SRC_CAP_WAIT);
        }
        /* RX 状态异常或收到 Hard Reset 后重新进入接收模式，避免卡死在异常状态 */
        USBPD_Phy_EnterRxMode();
    }
    if (USBPD_STATUS_HAS_FLAG(IF_TX_END))
    {
        PRINT("IF_TX_END\r\n");
        USBPD_STATUS_CLEAR_FLAG(IF_TX_END);
        USBPD_Phy_EnterRxMode();
    }
    if (USBPD_STATUS_HAS_FLAG(BUF_ERR))
    {
        PRINT("BUFERR\r\n");
        NVIC_SystemReset();
    }
}
