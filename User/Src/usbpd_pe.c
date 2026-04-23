#include "usbpd_pe.h"

#include "usbpd_helper.h"

extern PD_CONTROL USBPD_Control;

void USBPD_PE_Run()
{
}

__attribute__((interrupt("WCH-Interrupt-fast")))void USBPD_IRQHandler(void)
{
    if (USBPD_STATUS_HAS_FLAG(IF_RX_ACT))
    {
        USBPD_STATUS_CLEAR_FLAG(IF_RX_ACT);
    }
    if (USBPD_STATUS_HAS_FLAG(IF_RX_RESET))
    {
        USBPD_STATUS_CLEAR_FLAG(IF_RX_RESET);
    }
    if (USBPD_STATUS_HAS_FLAG(IF_TX_END))
    {
        USBPD_STATUS_CLEAR_FLAG(IF_TX_END);
    }
    if (USBPD_STATUS_HAS_FLAG(BUF_ERR))
    {
        USBPD_STATUS_CLEAR_FLAG(BUF_ERR);
    }
}
