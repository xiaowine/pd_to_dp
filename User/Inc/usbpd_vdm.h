#ifndef USBPD_VDM_HANDLER_H
#define USBPD_VDM_HANDLER_H

#include <stdint.h>
#include "ch32l103_usbpd.h"

void USBPD_VDM_Handle(const uint8_t* rx_buf, uint8_t* tx_buf, const Message_Header* last_rx_header);

#endif /* USBPD_VDM_HANDLER_H */
