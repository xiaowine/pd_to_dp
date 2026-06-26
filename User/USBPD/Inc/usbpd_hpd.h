#ifndef USBPD_HPD_H
#define USBPD_HPD_H

#include <stdint.h>

typedef enum
{
    USBPD_HPD_EVENT_NONE = 0,
    USBPD_HPD_EVENT_HIGH,
    USBPD_HPD_EVENT_LOW,
    USBPD_HPD_EVENT_IRQ,
} USBPD_HPDEventType;

typedef struct
{
    uint8_t logical_high;
    uint8_t gpio_high;
    uint8_t irq_hpd;
    uint16_t low_us;
} USBPD_HPDStatus;

typedef struct
{
    USBPD_HPDEventType type;
    USBPD_HPDStatus status;
} USBPD_HPDEvent;

void USBPD_HPD_Reset(void);
void USBPD_HPD_EnterMode(void);
void USBPD_HPD_Disable(void);
uint8_t USBPD_HPD_IsEnabled(void);
USBPD_HPDStatus USBPD_HPD_ReadStatus(void);
USBPD_HPDStatus USBPD_HPD_GetSnapshot(void);
uint8_t USBPD_HPD_PollEvent(USBPD_HPDEvent* event);
void USBPD_HPD_RecordReported(uint8_t logical_high);
uint8_t USBPD_HPD_GetReportedValid(void);
uint8_t USBPD_HPD_GetReportedHigh(void);

#endif /* USBPD_HPD_H */
