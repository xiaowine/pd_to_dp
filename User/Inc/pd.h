#ifndef PD_DP_PD_H
#define PD_DP_PD_H

#include "ch32l103.h"

#define PD_CC_CHECK_AND_RUN(PORT_REG, CMP_SEL, ...)      \
do                                                    \
{                                                     \
(PORT_REG) &= ~(CC_CE);                          \
(PORT_REG) |= (CMP_SEL);                         \
Delay_Us(2);                                      \
if ((PORT_REG) & PA_CC_AI)                        \
{                                                 \
__VA_ARGS__;                                  \
}                                                 \
} while (0)

#define PD_CC_IN_022(v)         ((((v) & bCC_CMP_22) != 0u))
#define PD_CC_IN_022_066(v)     ((((v) & bCC_CMP_22) != 0u) && (((v) & bCC_CMP_66) == 0u))
#define PD_CC_IN_066_220(v)     ((((v) & bCC_CMP_66) != 0u) && (((v) & bCC_CMP_220) == 0u))
#define PD_CC_IN_220_330(v)     (((v) & bCC_CMP_220) != 0u)

#define CC1_PIN GPIO_Pin_6
#define CC2_PIN GPIO_Pin_7
#define CC_PORT GPIOB

extern PD_CONTROL USBPD_Ctl;

void USBPD_Init(void);
void USBPD_Main_Proc(void);
void USBPD_DisConnect(void);
void USBPD_Detect_Process(void);


typedef enum
{
    PD_EVENT_DETACH = 0u,
    PD_EVENT_ATTACH = 1u,
} PD_DetectEventType;

/* Weak callback in pd.c, can be overridden in main.c */
void PD_Detect_EventCallback(PD_DetectEventType event, uint8_t cc);

#endif //PD_DP_PD_H
