#ifndef AUXILIARY_H
#define AUXILIARY_H

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

void AUXILIARY_init(void);
void U2D2_Normal(void);
void U2D2_Flipped(void);
void U0D4_Normal(void);
void U0D4_Flipped(void);

#endif //AUXILIARY_H
