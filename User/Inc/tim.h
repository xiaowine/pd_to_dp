//
// Created by xiaow on 2026/4/16.
//

#ifndef PD_DP_TIM_H
#define PD_DP_TIM_H

#include "ch32l103.h"
extern volatile uint8_t Tim_Ms_Cunt;

void PD_Tim_Init(void);
uint32_t Tim_GetIrqCount(void);

#endif //PD_DP_TIM_H
