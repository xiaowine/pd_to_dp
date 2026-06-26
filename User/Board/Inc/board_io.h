#ifndef BOARD_IO_H
#define BOARD_IO_H

#include <stdint.h>

#include "ch32l103.h"

#define KEY_PIN GPIO_Pin_0
#define KEY_PORT GPIOA

#define LED1_PIN GPIO_Pin_8
#define LED1_PORT GPIOA
#define LED2_PIN GPIO_Pin_15
#define LED2_PORT GPIOB

#define AMSEL_PIN GPIO_Pin_0
#define AMSEL_PORT GPIOB
#define EN_PIN GPIO_Pin_7
#define EN_PORT GPIOA
#define POL_PIN GPIO_Pin_5
#define POL_PORT GPIOA
#define HPD_PIN GPIO_Pin_14
#define HPD_PORT GPIOB

void BoardIO_Init(void);
uint8_t DP_HPD_IsHigh(void);

#endif
