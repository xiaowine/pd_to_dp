#include "board_io.h"

#include "debug.h"
#include "vl171.h"

static void BoardIO_InitKey(void)
{
    GPIO_InitTypeDef gpio = {0};

    gpio.GPIO_Pin = KEY_PIN;
    gpio.GPIO_Mode = GPIO_Mode_IN_FLOATING;
    gpio.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(KEY_PORT, &gpio);
}

static void BoardIO_InitLeds(void)
{
    GPIO_InitTypeDef gpio = {0};

    gpio.GPIO_Pin = LED1_PIN;
    gpio.GPIO_Mode = GPIO_Mode_AF_OD;
    gpio.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(LED1_PORT, &gpio);

    gpio.GPIO_Pin = LED2_PIN;
    gpio.GPIO_Mode = GPIO_Mode_Out_OD;
    GPIO_Init(LED2_PORT, &gpio);
    GPIO_SetBits(LED2_PORT, LED2_PIN);
}

static void BoardIO_InitHPD(void)
{
    GPIO_InitTypeDef gpio = {0};

    gpio.GPIO_Pin = HPD_PIN;
    gpio.GPIO_Mode = GPIO_Mode_IPD;
    gpio.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(HPD_PORT, &gpio);
}

static void BoardIO_ConfigHPDInterrupt(FunctionalState state)
{
    EXTI_InitTypeDef exti = {0};

    exti.EXTI_Line = EXTI_Line14;
    exti.EXTI_Mode = EXTI_Mode_Interrupt;
    exti.EXTI_Trigger = EXTI_Trigger_Rising_Falling;
    exti.EXTI_LineCmd = state;
    EXTI_Init(&exti);
}

static void BoardIO_InitHPDInterrupt(void)
{
    NVIC_InitTypeDef nvic = {0};

    nvic.NVIC_IRQChannel = EXTI15_10_IRQn;
    nvic.NVIC_IRQChannelPreemptionPriority = 0;
    nvic.NVIC_IRQChannelSubPriority = 3;
    nvic.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Init(&nvic);

    GPIO_EXTILineConfig(GPIO_PortSourceGPIOB, GPIO_PinSource14);
    EXTI_ClearITPendingBit(EXTI_Line14);
    BoardIO_ConfigHPDInterrupt(DISABLE);
}

static void BoardIO_InitKeyInterrupt(void)
{
    NVIC_InitTypeDef nvic = {0};
    EXTI_InitTypeDef exti = {0};

    nvic.NVIC_IRQChannel = EXTI0_IRQn;
    nvic.NVIC_IRQChannelPreemptionPriority = 0;
    nvic.NVIC_IRQChannelSubPriority = 2;
    nvic.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Init(&nvic);

    GPIO_EXTILineConfig(GPIO_PortSourceGPIOA, GPIO_PinSource0);

    exti.EXTI_Line = EXTI_Line0;
    exti.EXTI_Mode = EXTI_Mode_Interrupt;
    exti.EXTI_Trigger = EXTI_Trigger_Falling;
    exti.EXTI_LineCmd = ENABLE;
    EXTI_Init(&exti);
}

static void BoardIO_InitLedPwm(void)
{
    TIM_TimeBaseInitTypeDef time_base = {0};
    TIM_OCInitTypeDef oc = {0};

    time_base.TIM_Prescaler = 9499;
    time_base.TIM_CounterMode = TIM_CounterMode_Up;
    time_base.TIM_Period = 9999;
    time_base.TIM_ClockDivision = TIM_CKD_DIV1;
    time_base.TIM_RepetitionCounter = 0;
    TIM_TimeBaseInit(TIM1, &time_base);

    oc.TIM_OCMode = TIM_OCMode_PWM1;
    oc.TIM_OutputState = TIM_OutputState_Enable;
    oc.TIM_Pulse = 0;
    oc.TIM_OCPolarity = TIM_OCPolarity_Low;
    TIM_OC1Init(TIM1, &oc);
    TIM_OC1PreloadConfig(TIM1, TIM_OCPreload_Enable);
    TIM_ARRPreloadConfig(TIM1, ENABLE);
    TIM_CtrlPWMOutputs(TIM1, ENABLE);
    TIM_Cmd(TIM1, ENABLE);
}

void BoardIO_Init(void)
{
    RCC_PB2PeriphClockCmd(RCC_PB2Periph_GPIOA | RCC_PB2Periph_GPIOB | RCC_PB2Periph_AFIO |
                          RCC_PB2Periph_TIM1,
                          ENABLE);

    BoardIO_InitKey();
    BoardIO_InitLeds();
    VL171_Init();
    BoardIO_InitHPD();
    BoardIO_InitHPDInterrupt();
    BoardIO_InitKeyInterrupt();
    BoardIO_InitLedPwm();
}

uint8_t DP_HPD_IsHigh(void)
{
    return (GPIO_ReadInputDataBit(HPD_PORT, HPD_PIN) != Bit_RESET) ? 1u : 0u;
}

void DP_HPD_EnableInterrupt(void)
{
    EXTI_ClearITPendingBit(EXTI_Line14);
    BoardIO_ConfigHPDInterrupt(ENABLE);
}

void DP_HPD_DisableInterrupt(void)
{
    BoardIO_ConfigHPDInterrupt(DISABLE);
    EXTI_ClearITPendingBit(EXTI_Line14);
}

__attribute__((weak)) void DP_HPD_EdgeCallback(void)
{
}

__attribute__((interrupt("WCH-Interrupt-fast"))) void EXTI0_IRQHandler(void)
{
    if (EXTI_GetITStatus(EXTI_Line0) != RESET)
    {
        EXTI_ClearITPendingBit(EXTI_Line0);
        PRINT("KEY Pressed\r\n");
    }
}

__attribute__((interrupt("WCH-Interrupt-fast"))) void EXTI15_10_IRQHandler(void)
{
    if (EXTI_GetITStatus(EXTI_Line14) != RESET)
    {
        EXTI_ClearITPendingBit(EXTI_Line14);
        DP_HPD_EdgeCallback();
    }
}
