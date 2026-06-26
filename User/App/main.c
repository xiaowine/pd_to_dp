#include "board_io.h"
#include "ch32l103.h"
#include "debug.h"
#include "tim.h"
#include "vl171.h"
#include "usbpd_phy.h"
#include "usbpd_vdm.h"

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
            VL171_SetOrientation(VL171_ORIENTATION_NORMAL);
            VL171_ApplyMode(VL171_MODE_USB_DP_2LANE);
            PRINT("CC1 Attached\r\n");
            TIM_SetCompare1(TIM1, 6000);
        }
        else
        {
            VL171_SetOrientation(VL171_ORIENTATION_FLIPPED);
            VL171_ApplyMode(VL171_MODE_USB_DP_2LANE);
            PRINT("CC2 Attached\r\n");
            TIM_SetCompare1(TIM1, 9000);
        }
    }
    else
    {
        TIM_SetCompare1(TIM1, 0);
        PRINT("Detached\r\n");
    }
}

static void App_SetStartupLaneMode(void)
{
    const USBPD_DPLaneMode mode = BoardIO_IsKeyPressed() ?
        USBPD_DP_LANE_MODE_4LANE : USBPD_DP_LANE_MODE_2LANE;

    USBPD_DP_SetLaneMode(mode);
    BoardIO_SetLaneIndicator(mode == USBPD_DP_LANE_MODE_4LANE);
    PRINT("DP lane mode: %u-lane\r\n", (unsigned)mode);
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
    BoardIO_Init();
    App_SetStartupLaneMode();
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
