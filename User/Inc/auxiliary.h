#ifndef AUXILIARY_H
#define AUXILIARY_H

#include <stdint.h>

#define KEY_PIN GPIO_Pin_0
#define KEY_PORT GPIOA

#define LED1_PIN GPIO_Pin_8
#define LED1_PORT GPIOA
#define LED2_PIN GPIO_Pin_15
#define LED2_PORT GPIOB

#define AMSEL_PIN GPIO_Pin_0
#define AMSEL_PORT GPIOB
#define EN_PIN GPIO_Pin_7
#define EN_PORT GPIOA
#define POL_PIN GPIO_Pin_5
#define POL_PORT GPIOA
#define HPD_PIN GPIO_Pin_14
#define HPD_PORT GPIOB

typedef enum
{
    VL171_ORIENTATION_NORMAL = 0u,
    VL171_ORIENTATION_FLIPPED = 1u,
} VL171_Orientation;

typedef enum
{
    VL171_MODE_USB_DP_2LANE = 0u,
    VL171_MODE_DP_4LANE = 1u,
} VL171_Mode;

void AUXILIARY_Init(void);
void VL171_SetOrientation(VL171_Orientation orientation);
void VL171_ApplyMode(VL171_Mode mode);
void VL171_ApplyDPPinAssignment(uint32_t config_vdo);
uint8_t DP_HPD_IsHigh(void);

#endif //AUXILIARY_H
