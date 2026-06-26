//
// Created by xiaow on 2026/4/16.
//

#ifndef PD_DP_TIM_H
#define PD_DP_TIM_H

#include "ch32l103.h"
extern volatile uint8_t USBPD_Tim_Ms_Cnt;

void USBPD_Tim_Init(void);
uint16_t USBPD_Tim_GetUs16(void);

#endif //PD_DP_TIM_H
