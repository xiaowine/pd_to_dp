#include "auxiliary.h"
#include "ch32l103.h"
#include "debug.h"
#include "tim.h"
#include "../Inc/usbpd_phy.h"

uint8_t Tmr_Ms_Dlt = 0; // 系统计时器毫秒计时这次的增量值
uint8_t Tmr_Ms_Cnt_Last = 0; // 系统计时器毫秒计时上一次的值
uint8_t Det_Timer = 0; // PD连接状态检测计时器总递增值


void SystemClock_Config(void);

void USBPD_Phy_Detect_EventCallback(const PD_DetectEventType event, const uint8_t cc)
{
    if (event == PD_EVENT_ATTACH)
    {
        if (cc == DEF_PD_CC1)
        {
            U2D2_Normal();
            PRINT("CC1 Attached\r\n");
            TIM_SetCompare1(TIM1, 6000);
            // GPIO_SetBits(LED2_PORT, LED2_PIN);
        }
        else
        {
            U2D2_Flipped();
            PRINT("CC2 Attached\r\n");
            TIM_SetCompare1(TIM1, 9000);
            // GPIO_ResetBits(LED2_PORT, LED2_PIN);
        }
    }
    else
    {
        TIM_SetCompare1(TIM1, 0);
        // GPIO_SetBits(LED2_PORT, LED2_PIN);
        PRINT("Detached\r\n");
    }
}

/*********************************************************************
 * @fn      main
 *
 * @brief   Main program.
 *
 * @return  none
 */
int main(void)
{
    RCC_DeInit();
    SystemClock_Config();
    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_1);
    Delay_Init();
    USART_Printf_Init(2000000);
    PRINT("SystemClk:%ld\r\n", SystemCoreClock);
    PRINT("PD SNK TEST\r\n");
    USBPD_Tim_Init();
    // USBPD_Init();
    AUXILIARY_Init();
    USBPD_Phy_Init();

    while (1)
    {
        USBPD_Phy_Run();
    }
}

/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void)
{
    FLASH->ACTLR = (uint32_t)FLASH_ACTLR_LATENCY_2;
    EXTEN->EXTEN_CTR |= EXTEN_PLL_HSI_PRE;
    RCC_HSICmd(ENABLE);
    while (RCC_GetFlagStatus(RCC_FLAG_HSIRDY) == RESET)
    {
    }
    RCC_HCLKConfig(RCC_SYSCLK_Div1);
    RCC_PCLK2Config(RCC_HCLK_Div1);
    RCC_PCLK1Config(RCC_HCLK_Div1);

    RCC_PLLConfig(RCC_PLLSource_HSI_Div2, RCC_PLLMul_12);
    RCC_PLLCmd(ENABLE);
    while (RCC_GetFlagStatus(RCC_FLAG_PLLRDY) == RESET)
    {
    }

    RCC_SYSCLKConfig(RCC_SYSCLKSource_PLLCLK);
    while (RCC_GetSYSCLKSource() != 0x08)
    {
    }
    SystemCoreClockUpdate();
}
