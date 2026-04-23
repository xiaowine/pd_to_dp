#include "tim.h"
#include "ch32l103_tim.h"

volatile uint8_t USBPD_Tim_Ms_Cnt = 0u;

/**
 *  @fn Tim_Init
 *  @brief Tim Init
 *  @return none
 */
void USBPD_Tim_Init(void)
{
    RCC_PB1PeriphClockCmd(RCC_PB1Periph_TIM4, ENABLE);

    TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStructure;
    TIM_TimeBaseInitStructure.TIM_Prescaler = 1;
    TIM_TimeBaseInitStructure.TIM_CounterMode = TIM_CounterMode_Up;
    TIM_TimeBaseInitStructure.TIM_Period = 47999;
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
        // PRINT("Timer interrupt\r\n" );
    }
}
