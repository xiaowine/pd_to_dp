#ifndef HELPER_H
#define HELPER_H

#include <stdint.h>

#include "ch32l103.h"
#include "pd_pdo.h"
#include "pd_rdo.h"

#define USBPD_HEADER_MESSAGE_TYPE(HEADER) (HEADER[ 0 ] & 0b11111 )
#define USBPD_READ_U16_LE(PTR) \
    ((uint16_t)((uint16_t)((const uint8_t*)(PTR))[0] \
                | ((uint16_t)((const uint8_t*)(PTR))[1] << 8)))
#define USBPD_READ_U32_LE(PTR) \
    ((uint32_t)((uint32_t)((const uint8_t*)(PTR))[0] \
                | ((uint32_t)((const uint8_t*)(PTR))[1] << 8) \
                | ((uint32_t)((const uint8_t*)(PTR))[2] << 16) \
                | ((uint32_t)((const uint8_t*)(PTR))[3] << 24)))
#define USBPD_IQR_ENABLE()     do {  NVIC->IENR[2] = 0x00000000; } while (0)
#define USBPD_IQR_DISABLE()    do {  NVIC->IRER[2] = 0x00000002; __asm volatile ("fence.i");} while (0)
#define USBPD_STATUS(FLAG )   (USBPD->STATUS & (FLAG))
#define USBPD_CLEAR_STATUS(FLAG)   (USBPD->STATUS |= (FLAG))
#define USBPD_SOP0() ((USBPD->STATUS & MASK_PD_STAT)==PD_RX_SOP0)
#define USBPD_BMC_CNT() (USBPD->BMC_BYTE_CNT)
#define USBPD_LVE_ENABLE() do { \
volatile uint16_t *port = (USBPD->CONFIG & CC_SEL) ? &USBPD->PORT_CC2 : &USBPD->PORT_CC1; \
*port |= (uint16_t)CC_LVE; \
} while (0)

#define USBPD_LVE_DISABLE() do { \
volatile uint16_t *port = (USBPD->CONFIG & CC_SEL) ? &USBPD->PORT_CC2 : &USBPD->PORT_CC1; \
*port &= (uint16_t)~CC_LVE; \
} while (0)

static const Message_Header kGoodCrcBase = {
    .Message_Header = {
        .MsgType = DEF_TYPE_GOODCRC,
        .NumDO = 0,
        .PDRole = 0,
        .Ext = 0,
    }
};

void USBPD_PDO_Analyse(const uint8_t* message);
uint8_t USBPD_FIND_5V_PDO(const uint8_t* message);

#endif //HELPER_H
