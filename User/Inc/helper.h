#ifndef HELPER_H
#define HELPER_H


#define USBPD_HEADER_MESSAGE_TYPE(HEADER) (HEADER[ 0 ] & 0b11111 )
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

#endif //HELPER_H
