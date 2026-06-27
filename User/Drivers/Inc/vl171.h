#ifndef VL171_H
#define VL171_H

#include <stdint.h>

typedef enum
{
    VL171_ORIENTATION_NORMAL = 0u,
    VL171_ORIENTATION_FLIPPED = 1u,
} VL171_Orientation;

typedef enum
{
    VL171_MODE_USB = 0u,
    VL171_MODE_USB_DP_2LANE = 1u,
    VL171_MODE_DP_4LANE = 2u,
} VL171_Mode;

void VL171_Init(void);
void VL171_SetOrientation(VL171_Orientation orientation);
void VL171_ApplyMode(VL171_Mode mode);
void VL171_ApplyDPPinAssignment(uint32_t config_vdo);

#endif
