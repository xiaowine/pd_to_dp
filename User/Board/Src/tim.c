#include "tim.h"
#include "ch32l103_tim.h"

volatile uint8_t USBPD_Tim_Ms_Cnt = 0u;
static volatile uint16_t s_usbpd_tim_us16 = 0u;

/**
 *  @fn Tim_Init
 *  @brief Tim Init
 *  @return none
 */
void USBPD_Tim_Init(void)
{
    RCC_PB1PeriphClockCmd(RCC_PB1Periph_TIM4, ENABLE);

    TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStructure;
    TIM_TimeBaseInitStructure.TIM_Prescaler = 95; // 96MHz/(1+1)=48MHz
    TIM_TimeBaseInitStructure.TIM_CounterMode = TIM_CounterMode_Up;
    TIM_TimeBaseInitStructure.TIM_Period = 999; // 48MHz/(47999+1)=1kHz
    TIM_TimeBaseInitStructure.TIM_ClockDivision = TIM_CKD_DIV1;
    TIM_TimeBaseInitStructure.TIM_RepetitionCounter = 0;
    TIM_TimeBaseInit(TIM4, &TIM_TimeBaseInitStructure);
    TIM_ClearITPendingBit(TIM4, TIM_IT_Update);

    NVIC_InitTypeDef NVIC_InitStructure = {0};
    NVIC_InitStructure.NVIC_IRQChannel = TIM4_IRQn;
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Init(&NVIC_InitStructure);

    TIM_ITConfig(TIM4, TIM_IT_Update, ENABLE);
    TIM_Cmd(TIM4, ENABLE);
}

uint16_t USBPD_Tim_GetUs16(void)
{
    uint16_t base_before = 0u;
    uint16_t base_after = 0u;
    uint16_t us = 0u;

    do
    {
        base_before = s_usbpd_tim_us16;
        us = (uint16_t)TIM_GetCounter(TIM4);
        base_after = s_usbpd_tim_us16;
    } while (base_before != base_after);

    return (uint16_t)(base_before + us);
}

/**
 * @fn      TIM4_IRQHandler
 * @brief   TIM4 interrupt handler
 * @return  none
 */
__attribute__((interrupt("WCH-Interrupt-fast"))) void TIM4_IRQHandler(void)
{
    if (TIM_GetITStatus(TIM4, TIM_IT_Update) != RESET)
    {
        TIM_ClearITPendingBit(TIM4, TIM_IT_Update);
        USBPD_Tim_Ms_Cnt++;
        s_usbpd_tim_us16 = (uint16_t)(s_usbpd_tim_us16 + 1000u);
        // PRINT("Timer interrupt\r\n" );
    }
}
