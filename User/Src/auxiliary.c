#include "auxiliary.h"
#include "ch32l103.h"

static VL171_Orientation s_vl171_orientation = VL171_ORIENTATION_NORMAL;

static void VL171_SetAMSEL(uint8_t high)
{
    GPIO_InitTypeDef GPIO_InitStructure = {0};

    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitStructure.GPIO_Pin = AMSEL_PIN;
    if (high)
    {
        GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
        GPIO_Init(AMSEL_PORT, &GPIO_InitStructure);
        GPIO_SetBits(AMSEL_PORT, AMSEL_PIN);
    }
    else
    {
        GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_OD;
        GPIO_Init(AMSEL_PORT, &GPIO_InitStructure);
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

void VL171_SetOrientation(VL171_Orientation orientation)
{
    s_vl171_orientation = orientation;
}

void AUXILIARY_Init(void)
{
    RCC_PB2PeriphClockCmd(RCC_PB2Periph_GPIOA | RCC_PB2Periph_GPIOB | RCC_PB2Periph_AFIO | RCC_PB2Periph_TIM1, ENABLE);

    GPIO_InitTypeDef GPIO_InitStructure = {0};
    GPIO_InitStructure.GPIO_Pin = KEY_PIN;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(KEY_PORT, &GPIO_InitStructure);

    GPIO_InitStructure.GPIO_Pin = LED1_PIN;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_OD;
    GPIO_Init(LED1_PORT, &GPIO_InitStructure);

    GPIO_InitStructure.GPIO_Pin = LED2_PIN;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_OD;
    GPIO_Init(LED2_PORT, &GPIO_InitStructure);
    GPIO_SetBits(LED2_PORT, LED2_PIN);

    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_OD;
    GPIO_InitStructure.GPIO_Pin = AMSEL_PIN;
    GPIO_Init(AMSEL_PORT, &GPIO_InitStructure);
    GPIO_ResetBits(AMSEL_PORT, AMSEL_PIN);

    GPIO_InitStructure.GPIO_Pin = EN_PIN;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
    GPIO_Init(EN_PORT, &GPIO_InitStructure);
    GPIO_SetBits(EN_PORT, EN_PIN);

    GPIO_InitStructure.GPIO_Pin = POL_PIN;
    GPIO_Init(POL_PORT, &GPIO_InitStructure);
    GPIO_ResetBits(POL_PORT, POL_PIN);

    GPIO_InitStructure.GPIO_Pin = HPD_PIN;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
    GPIO_Init(HPD_PORT, &GPIO_InitStructure);


    NVIC_InitTypeDef NVIC_InitStructure = {0};
    NVIC_InitStructure.NVIC_IRQChannel = EXTI0_IRQn;
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 2;
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Init(&NVIC_InitStructure);

    GPIO_EXTILineConfig(GPIO_PortSourceGPIOA, GPIO_PinSource0);
    EXTI_InitTypeDef EXTI_InitStructure = {0};
    EXTI_InitStructure.EXTI_Line = EXTI_Line0;
    EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;
    EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Falling;
    EXTI_InitStructure.EXTI_LineCmd = ENABLE;
    EXTI_Init(&EXTI_InitStructure);


    TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStructure = {0};
    TIM_TimeBaseInitStructure.TIM_Prescaler = 9499; // 96MHz/(9499+1)=10kHz
    TIM_TimeBaseInitStructure.TIM_CounterMode = TIM_CounterMode_Up;
    TIM_TimeBaseInitStructure.TIM_Period = 9999; // 10KHz/(9999+1)=1Hz
    TIM_TimeBaseInitStructure.TIM_ClockDivision = TIM_CKD_DIV1;
    TIM_TimeBaseInitStructure.TIM_RepetitionCounter = 0;
    TIM_TimeBaseInit(TIM1, &TIM_TimeBaseInitStructure);

    TIM_OCInitTypeDef TIM_OCInitStructure = {0};
    TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;
    TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
    TIM_OCInitStructure.TIM_Pulse = 0;
    TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_Low; // 开漏输出低电平导通，驱动外部 LED
    TIM_OC1Init(TIM1, &TIM_OCInitStructure);
    TIM_OC1PreloadConfig(TIM1, TIM_OCPreload_Enable);
    TIM_ARRPreloadConfig(TIM1, ENABLE);
    TIM_CtrlPWMOutputs(TIM1, ENABLE);
    TIM_Cmd(TIM1, ENABLE);
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
    const uint32_t pin_assign = config_vdo & 0x0000FF00u;

    switch (pin_assign)
    {
    case 0x00000400u:
        VL171_ApplyMode(VL171_MODE_DP_4LANE);
        break;

    case 0x00000800u:
        VL171_ApplyMode(VL171_MODE_USB_DP_2LANE);
        break;

    case 0x00001000u:
        VL171_ApplyMode(VL171_MODE_DP_4LANE);
        break;

    default:
        break;
    }
}

uint8_t DP_HPD_IsHigh(void)
{
    return (GPIO_ReadInputDataBit(HPD_PORT, HPD_PIN) != Bit_RESET) ? 1u : 0u;
}


__attribute__((interrupt("WCH-Interrupt-fast"))) void EXTI0_IRQHandler(void)
{
    if (EXTI_GetITStatus(EXTI_Line0) != RESET)
    {
        EXTI_ClearITPendingBit(EXTI_Line0);
        // USBPD_DisConnect();
        PRINT("KEY Pressed\r\n");
    }
}
