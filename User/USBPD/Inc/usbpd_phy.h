#ifndef USBPD_H
#define USBPD_H

#include "ch32l103.h"

#define CC_INVALID 0xFFu

typedef enum
{
    PD_EVENT_DETACH = 0u,
    PD_EVENT_ATTACH = 1u,
} PD_DetectEventType;

extern volatile PD_CONTROL USBPD_Control;

void USBPD_Phy_Init(void);
void USBPD_Phy_Run(void);
void USBPD_Phy_TxPacket(const uint8_t* pbuf, uint8_t len, uint8_t sop, uint8_t sync_mode);
void USBPD_Phy_SetRxBuffer(uint8_t* buf);
void USBPD_Phy_EnterRxMode(void);

#endif //USBPD_H
