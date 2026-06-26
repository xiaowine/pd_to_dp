#include "vl171.h"

#include "board_io.h"
#include "debug.h"
#include "pd_dp_alt_mode.h"

static VL171_Orientation s_vl171_orientation = VL171_ORIENTATION_NORMAL;

static void VL171_SetAMSEL(uint8_t high)
{
    GPIO_InitTypeDef gpio = {0};

    gpio.GPIO_Speed = GPIO_Speed_50MHz;
    gpio.GPIO_Pin = AMSEL_PIN;
    if (high)
    {
        gpio.GPIO_Mode = GPIO_Mode_Out_PP;
        GPIO_Init(AMSEL_PORT, &gpio);
        GPIO_SetBits(AMSEL_PORT, AMSEL_PIN);
    }
    else
    {
        gpio.GPIO_Mode = GPIO_Mode_Out_OD;
        GPIO_Init(AMSEL_PORT, &gpio);
        GPIO_ResetBits(AMSEL_PORT, AMSEL_PIN);
    }
}

static void VL171_SetControl(uint8_t amsel_high, VL171_Orientation orientation)
{
    GPIO_SetBits(EN_PORT, EN_PIN);
    if (orientation == VL171_ORIENTATION_FLIPPED)
    {
        GPIO_SetBits(POL_PORT, POL_PIN);
    }
    else
    {
        GPIO_ResetBits(POL_PORT, POL_PIN);
    }
    VL171_SetAMSEL(amsel_high);
}

void VL171_Init(void)
{
    GPIO_InitTypeDef gpio = {0};

    gpio.GPIO_Mode = GPIO_Mode_Out_OD;
    gpio.GPIO_Speed = GPIO_Speed_50MHz;
    gpio.GPIO_Pin = AMSEL_PIN;
    GPIO_Init(AMSEL_PORT, &gpio);
    GPIO_ResetBits(AMSEL_PORT, AMSEL_PIN);

    gpio.GPIO_Pin = EN_PIN;
    gpio.GPIO_Mode = GPIO_Mode_Out_PP;
    GPIO_Init(EN_PORT, &gpio);
    GPIO_SetBits(EN_PORT, EN_PIN);

    gpio.GPIO_Pin = POL_PIN;
    GPIO_Init(POL_PORT, &gpio);
    GPIO_ResetBits(POL_PORT, POL_PIN);
}

void VL171_SetOrientation(VL171_Orientation orientation)
{
    s_vl171_orientation = orientation;
}

void VL171_ApplyMode(VL171_Mode mode)
{
    switch (mode)
    {
    case VL171_MODE_USB_DP_2LANE:
        VL171_SetControl(0u, s_vl171_orientation);
        PRINT("VL171 2-lane DP + USB3 %s\r\n",
              (s_vl171_orientation == VL171_ORIENTATION_FLIPPED) ? "Flipped" : "Normal");
        break;

    case VL171_MODE_DP_4LANE:
        VL171_SetControl(1u, s_vl171_orientation);
        PRINT("VL171 4-lane DP %s\r\n",
              (s_vl171_orientation == VL171_ORIENTATION_FLIPPED) ? "Flipped" : "Normal");
        break;

    default:
        break;
    }
}

void VL171_ApplyDPPinAssignment(uint32_t config_vdo)
{
    USBPD_DPConfigureVDO config = {0};

    config.Raw = config_vdo;
    switch (config.Bit.PinAssignment)
    {
    case USBPD_DP_PIN_ASSIGN_C:
    case USBPD_DP_PIN_ASSIGN_E:
        VL171_ApplyMode(VL171_MODE_DP_4LANE);
        break;

    case USBPD_DP_PIN_ASSIGN_D:
        VL171_ApplyMode(VL171_MODE_USB_DP_2LANE);
        break;

    default:
        break;
    }
}
