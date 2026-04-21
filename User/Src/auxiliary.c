#include "auxiliary.h"
#include "ch32l103.h"
#include "pd.h"

void AUXILIARY_init(void)
{
    RCC_PB2PeriphClockCmd(RCC_PB2Periph_GPIOA | RCC_PB2Periph_GPIOB, ENABLE);

    GPIO_InitTypeDef GPIO_InitStructure = {0};
    GPIO_InitStructure.GPIO_Pin = KEY_PIN;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(KEY_PORT, &GPIO_InitStructure);

    GPIO_InitStructure.GPIO_Pin = LED1_PIN;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_OD;
    GPIO_Init(LED1_PORT, &GPIO_InitStructure);
    GPIO_SetBits(LED1_PORT, LED1_PIN);

    GPIO_InitStructure.GPIO_Pin = LED2_PIN;
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
}


void U2D2_Normal(void)
{
    GPIO_SetBits(EN_PORT, EN_PIN);
    GPIO_ResetBits(POL_PORT, POL_PIN);

    GPIO_InitTypeDef GPIO_InitStructure = {0};
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_OD;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitStructure.GPIO_Pin = AMSEL_PIN;
    GPIO_Init(AMSEL_PORT, &GPIO_InitStructure);
    GPIO_ResetBits(AMSEL_PORT, AMSEL_PIN);
    PRINT("U2D2 Normal\r\n");
}

void U2D2_Flipped(void)
{
    GPIO_SetBits(EN_PORT, EN_PIN);
    GPIO_SetBits(POL_PORT, POL_PIN);

    GPIO_InitTypeDef GPIO_InitStructure = {0};
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_OD;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitStructure.GPIO_Pin = AMSEL_PIN;
    GPIO_Init(AMSEL_PORT, &GPIO_InitStructure);
    GPIO_ResetBits(AMSEL_PORT, AMSEL_PIN);
    PRINT("U2D2 Flipped\r\n");
}

void U0D4_Normal(void)
{
    GPIO_SetBits(EN_PORT, EN_PIN);
    GPIO_ResetBits(POL_PORT, POL_PIN);

    GPIO_InitTypeDef GPIO_InitStructure = {0};
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitStructure.GPIO_Pin = AMSEL_PIN;
    GPIO_Init(AMSEL_PORT, &GPIO_InitStructure);
    GPIO_SetBits(AMSEL_PORT, AMSEL_PIN);
    PRINT("U0D4 Normal\r\n");
}

void U0D4_Flipped(void)
{
    GPIO_SetBits(EN_PORT, EN_PIN);
    GPIO_SetBits(POL_PORT, POL_PIN);

    GPIO_InitTypeDef GPIO_InitStructure = {0};
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitStructure.GPIO_Pin = AMSEL_PIN;
    GPIO_Init(AMSEL_PORT, &GPIO_InitStructure);
    GPIO_SetBits(AMSEL_PORT, AMSEL_PIN);
    PRINT("U0D4 Flipped\r\n");
}


__attribute__((interrupt("WCH-Interrupt-fast"))) void EXTI0_IRQHandler(void)
{
    if (EXTI_GetITStatus(EXTI_Line0) != RESET)
    {
        EXTI_ClearITPendingBit(EXTI_Line0);
        USBPD_DisConnect();
        PRINT("KEY Pressed\r\n");
    }
}
