#ifndef USBPD_HELPER_H
#define USBPD_HELPER_H

#include "ch32l103.h"

#define USBPD_CC_CHECK_AND_EXEC(PORT_REG, CMP_SEL, ...)  /* 配置 CC 比较器阈值并检测，命中后执行传入代码 */ \
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

#define USBPD_CC_IS_GE_0P22V(v)         ((((v) & bCC_CMP_22) != 0u)) /* 电压达到 0.22V 门限 */
#define USBPD_CC_IS_0P22_TO_2P20V(v)    ((((v) & bCC_CMP_22) != 0u) && (((v) & bCC_CMP_220) == 0u)) /* 电压位于 0.22V~2.20V */



#define USBPD_CC_IS_GE_2P20V(v)         (((v) & bCC_CMP_220) != 0u) /* 电压达到 2.20V 门限 */

#define USBPD_CC1_GPIO_PIN GPIO_Pin_6 /* CC1 对应引脚 */
#define USBPD_CC2_GPIO_PIN GPIO_Pin_7 /* CC2 对应引脚 */
#define USBPD_CC_GPIO_PORT GPIOB      /* CC 所在 GPIO 端口 */

#define USBPD_MSG_TYPE_FROM_HEADER(HEADER) ((HEADER)[0] & 0x1Fu) /* 提取 PD 报文类型（低 5 位） */

#define USBPD_READ_LE16(PTR) /* 按小端序读取 16 位值 */ \
    ((uint16_t)((uint16_t)((const uint8_t*)(PTR))[0] \
                | ((uint16_t)((const uint8_t*)(PTR))[1] << 8)))

#define USBPD_READ_LE32(PTR) /* 按小端序读取 32 位值 */ \
    ((uint32_t)((uint32_t)((const uint8_t*)(PTR))[0] \
                | ((uint32_t)((const uint8_t*)(PTR))[1] << 8) \
                | ((uint32_t)((const uint8_t*)(PTR))[2] << 16) \
                | ((uint32_t)((const uint8_t*)(PTR))[3] << 24)))

#define USBPD_STATUS_HAS_FLAG(FLAG)   (USBPD->STATUS & (FLAG)) /* 读取状态寄存器指定标志 */
#define USBPD_STATUS_CLEAR_FLAG(FLAG) (USBPD->STATUS |= (FLAG)) /* 写 1 清除状态标志 */
#define USBPD_STATUS_IS_SOP0()        ((USBPD->STATUS & MASK_PD_STAT) == PD_RX_SOP0) /* 判断是否收到 SOP0 */

#define USBPD_CC_LVE_ENABLE_SELECTED() do { /* 按当前 CC 选择使能 LVE */ \
volatile uint16_t *port = (USBPD->CONFIG & CC_SEL) ? &USBPD->PORT_CC2 : &USBPD->PORT_CC1; \
*port |= (uint16_t)CC_LVE; \
} while (0)

#define USBPD_CC_LVE_DISABLE_SELECTED() do { /* 按当前 CC 选择关闭 LVE */ \
volatile uint16_t *port = (USBPD->CONFIG & CC_SEL) ? &USBPD->PORT_CC2 : &USBPD->PORT_CC1; \
*port &= (uint16_t)~CC_LVE; \
} while (0)

#define SWITCH_PD_STATE(state) do { \
USBPD_Control.PD_State_Last = USBPD_Control.PD_State; \
USBPD_Control.PD_State = (state); \
} while (0)

void USBPD_PDO_Analyse(const uint8_t* message);
uint8_t USBPD_FIND_5V_PDO(const uint8_t* message);
uint8_t USBPD_GetCcCmpFlags(volatile uint16_t* port_reg, GPIO_TypeDef* gpio, uint16_t gpio_pin);

#endif //USBPD_HELPER_H
