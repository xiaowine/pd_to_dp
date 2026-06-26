#include "usbpd_phy.h"
#include <string.h>
#include "usbpd_helper.h"
#include "tim.h"
#include "usbpd_pe.h"

uint8_t currentDeltaTimer = 0; // 当前系统计时器毫秒计时的增量值
uint8_t totalDeltaTime = 0; // 系统计时器毫秒计时的总递增值
uint8_t lastDeltaTime = 0; // 系统计时器毫秒计时的上一次的值

volatile PD_CONTROL USBPD_Control = {0};

uint8_t* s_rx_buf;

void USBPD_Phy_TxPacket(const uint8_t* pbuf, const uint8_t len, const uint8_t sop, const uint8_t sync_mode)
{
    USBPD_CC_LVE_ENABLE_SELECTED();
    USBPD->CONFIG |= PD_ALL_CLR;
    USBPD->CONFIG &= ~PD_ALL_CLR;

    if (sync_mode)
    {
        /* Synchronous send uses polling to avoid racing with TX_END ISR clear. */
        USBPD->CONFIG &= ~IE_TX_END;
    }
    else
    {
        USBPD->CONFIG |= IE_TX_END;
    }
    USBPD->CONFIG &= ~(IE_RX_ACT | IE_RX_RESET);
    USBPD->BMC_CLK_CNT = UPD_TMR_TX_96M;
    USBPD->DMA = (uint32_t)pbuf;
    USBPD->CONTROL |= PD_TX_EN;
    USBPD->STATUS &= BMC_AUX_INVALID;
    USBPD->CONTROL |= BMC_START;
    USBPD->TX_SEL = sop;
    USBPD->BMC_TX_SZ = len;
    if (sync_mode)
    {
        NVIC_DisableIRQ(USBPD_IRQn);
        uint32_t timeout = 2000000u;
        while (!USBPD_STATUS_HAS_FLAG(IF_TX_END))
        {
            if (--timeout == 0u)
            {
                break;
            }
        }
        USBPD_STATUS_CLEAR_FLAG(IF_TX_END);
        USBPD_CC_LVE_DISABLE_SELECTED();
        USBPD_Phy_EnterRxMode();
    }
}

void USBPD_Phy_EnterRxMode(void)
{
    USBPD_CC_LVE_ENABLE_SELECTED();
    USBPD->CONFIG |= PD_ALL_CLR;
    USBPD->CONFIG &= ~PD_ALL_CLR;
    USBPD->CONFIG |= IE_RX_ACT | IE_RX_RESET;
    USBPD->CONFIG &= ~IE_TX_END;
    USBPD->BMC_CLK_CNT = UPD_TMR_RX_96M;
    USBPD->DMA = (uint32_t)s_rx_buf;
    USBPD->CONTROL &= ~PD_TX_EN;
    USBPD->STATUS &= BMC_AUX_INVALID;
    USBPD->CONTROL |= BMC_START;

    NVIC_EnableIRQ(USBPD_IRQn);
}

void USBPD_Phy_SetRxBuffer(uint8_t* buf)
{
    s_rx_buf = buf;
}

void USBPD_Phy_Init(void)
{
    USBPD_PE_Init();

    RCC_HBPeriphClockCmd(RCC_HBPeriph_USBPD, ENABLE);
    RCC_PB2PeriphClockCmd(RCC_PB2Periph_AFIO, ENABLE);
    RCC_PB2PeriphClockCmd(RCC_PB2Periph_GPIOB, ENABLE);

    GPIO_InitTypeDef GPIO_InitStructure = {0};
    GPIO_InitStructure.GPIO_Pin = USBPD_CC1_GPIO_PIN | USBPD_CC2_GPIO_PIN;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(USBPD_CC_GPIO_PORT, &GPIO_InitStructure);

    AFIO->CR |= USBPD_IN_HVT;
    USBPD->CONFIG |= PD_DMA_EN;
    USBPD->CONFIG &= ~CC_SEL;
    USBPD->STATUS &= BMC_AUX_INVALID;
    USBPD->PORT_CC1 |= CC_PD;
    USBPD->PORT_CC2 |= CC_PD;

    NVIC_InitTypeDef NVIC_InitStructure = {0};
    NVIC_InitStructure.NVIC_IRQChannel = USBPD_IRQn;
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Init(&NVIC_InitStructure);

    NVIC_DisableIRQ(USBPD_IRQn);
}

__attribute__((weak)) void USBPD_Phy_Detect_EventCallback(const PD_DetectEventType event, const uint8_t cc)
{
    (void)event;
    (void)cc;
}

void USBPD_Phy_Detect_Check(void)
{
    USBPD->PORT_CC1 &= ~CC_LVE;
    USBPD->PORT_CC2 &= ~CC_LVE;

    uint8_t ret = CC_INVALID;
    const uint8_t cc1 = USBPD_GetCcCmpFlags(&USBPD->PORT_CC1, USBPD_CC_GPIO_PORT, USBPD_CC1_GPIO_PIN);
    const uint8_t cc2 = USBPD_GetCcCmpFlags(&USBPD->PORT_CC2, USBPD_CC_GPIO_PORT, USBPD_CC2_GPIO_PIN);
    if (USBPD_CC_IS_0P22_TO_2P20V(cc1) && !USBPD_CC_IS_GE_0P22V(cc2))
    {
        ret = DEF_PD_CC1;
    }

    if (USBPD_CC_IS_0P22_TO_2P20V(cc2) && !USBPD_CC_IS_GE_0P22V(cc1))
    {
        ret = DEF_PD_CC2;
    }
    if (USBPD_Control.Flag.Connected)
    {
        const uint8_t sel_cc = USBPD->CONFIG & CC_SEL;
        /* 已连接时，ret 需要与当前选中的 CC 通道一致，否则判定为异常/疑似断开 */
        if ((!sel_cc && ret == DEF_PD_CC1) ||
            (sel_cc & CC_SEL && ret == DEF_PD_CC2))
        {
            USBPD_Control.Det_Cnt = 0;
        }
        else
        {
            USBPD_Control.Det_Cnt++;
            if (USBPD_Control.Det_Cnt >= 5u)
            {
                USBPD_Control.Flag.Connected = 0;
                USBPD_Phy_Detect_EventCallback(PD_EVENT_DETACH, ret);
                if (!USBPD_Control.Flag.Stop_Det_Chk)
                {
                    SWITCH_PD_STATE(STA_DISCONNECT);
                }
            }
        }
    }
    else
    {
        if (ret == CC_INVALID)
        {
            USBPD_Control.Det_Cnt = 0;
        }
        else
        {
            USBPD_Control.Det_Cnt++;
        }
        // PRINT("ret %d Det_cnt :%d\r\n", ret, PD_Ctl.Det_Cnt);
        if (USBPD_Control.Det_Cnt >= 5)
        {
            USBPD_Control.Det_Cnt = 0;
            USBPD_Control.Flag.Connected = 1;
            if (ret == DEF_PD_CC1)
            {
                USBPD->CONFIG &= ~CC_SEL;
            }
            else
            {
                USBPD->CONFIG |= CC_SEL;
            }
            USBPD_Phy_Detect_EventCallback(PD_EVENT_ATTACH, ret);
            if (!USBPD_Control.Flag.Stop_Det_Chk)
            {
                SWITCH_PD_STATE(STA_SRC_CONNECT);
            }
            USBPD_Phy_TxPacket(NULL, 0, UPD_HARD_RESET, 1); /* 发送 Hard Reset 并等待发送完成 */
            // USBPD_Phy_TxPacket(NULL, 0, UPD_SOP0, 0);
            USBPD_Phy_EnterRxMode();
        }
    }
}

void USBPD_Phy_Run(void)
{
    TIM_ITConfig(TIM1, TIM_IT_Update, DISABLE);
    currentDeltaTimer = USBPD_Tim_Ms_Cnt - lastDeltaTime;
    lastDeltaTime = USBPD_Tim_Ms_Cnt;
    TIM_ITConfig(TIM1, TIM_IT_Update, ENABLE);
    totalDeltaTime += currentDeltaTimer;
    if (totalDeltaTime > 4)
    {
        totalDeltaTime = 0;
        USBPD_Phy_Detect_Check();
    }
    USBPD_PE_Run();
}
