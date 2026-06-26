#ifndef USBPD_VDM_DEBUG_H
#define USBPD_VDM_DEBUG_H

#include <stdint.h>

/* 打印并解码 DP Mode VDO，便于查看 Discover Modes 协商结果。 */
void USBPD_LogDPModeVDO(uint32_t mode_vdo);

/* 打印并解码 DP Status VDO，便于跟踪连接状态和 HPD 状态。 */
void USBPD_LogDPStatusVDO(const char* prefix, uint32_t status_vdo);

/* 打印并解码 DP Configure VDO，便于确认对端下发的配置。 */
void USBPD_LogDPConfigVDO(uint32_t config_vdo);

/* 打印收到的 Structured VDM 应答类型。 */
void USBPD_LogVDMCommandType(uint8_t command_type);

#endif /* USBPD_VDM_DEBUG_H */
