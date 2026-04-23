#include "usbpd_pe.h"

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
    default: break;
    }
    if (USBPD_Control.Flag.Msg_Recvd)
    {
        switch (USBPD_MSG_TYPE_FROM_HEADER(pe_rx_buf))
        {
        case DEF_TYPE_SRC_CAP:
            {
                USBPD_PDO_Analyse(pe_rx_buf);
                break;
            }
        default: break;
        }
        USBPD_Control.Flag.Msg_Recvd = 0;
        USBPD_Phy_EnterRxMode();
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
            USBPD_Control.Flag.Msg_Recvd = 1;
        }
    }
    if (USBPD_STATUS_HAS_FLAG(IF_RX_RESET))
    {
        PRINT("IF_RX_RESET\r\n");
        USBPD_STATUS_CLEAR_FLAG(IF_RX_RESET);
    }
    if (USBPD_STATUS_HAS_FLAG(IF_TX_END))
    {
        USBPD_STATUS_CLEAR_FLAG(IF_TX_END);
    }
    if (USBPD_STATUS_HAS_FLAG(BUF_ERR))
    {
        PRINT("BUFERR\r\n");
        NVIC_SystemReset();
    }
}
