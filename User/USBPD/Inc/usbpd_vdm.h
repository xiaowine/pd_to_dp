#ifndef USBPD_VDM_DEFINITIONS_H
#define USBPD_VDM_DEFINITIONS_H

#include <stdint.h>
#include "pd_dp_alt_mode.h"

typedef enum
{
    USBPD_DP_LANE_MODE_2LANE = 2u, /* Pin Assignment D，2-lane DP + USB3。 */
    USBPD_DP_LANE_MODE_4LANE = 4u, /* Pin Assignment C，4-lane DP，不保留 USB3。 */
} USBPD_DPLaneMode;

/*
 * Discover Identity ACK 中需要用到的本设备身份信息。
 * 这里保存的是“定义值”，实际打包成 ID Header VDO / Product VDO / UFP VDO
 * 的逻辑在 usbpd_vdm_handler.c 中完成。
 */
typedef struct
{
    uint16_t usb_vendor_id; /* USB-IF 分配的 VID，写入 ID Header VDO bit15..0。 */
    uint16_t usb_product_id; /* USB 产品 PID，写入 Product VDO bit31..16。 */
    uint16_t bcd_device; /* 设备版本号 bcdDevice，写入 Product VDO bit15..0。 */
    uint8_t connector_type; /* Type-C 插座/插头类型，写入 ID Header VDO Connector Type。 */
    uint8_t product_type_ufp; /* 本端作为 UFP/SOP 时声明的产品类型。 */
    uint8_t usb_highest_speed; /* UFP VDO 中声明的 USB 最高速率能力。 */
    uint8_t usb2_device_capability; /* UFP VDO 中声明的 USB2.0 Device 能力。 */
    uint8_t usb32_device_capable; /* UFP VDO 中声明是否支持 USB 3.2 Device。 */
    uint8_t ufp_vdo_version; /* UFP VDO 版本字段。 */
} USBPD_VDMIdentityDefinition;

/*
 * DisplayPort Alt Mode 的本端能力定义。
 * Discover SVIDs / Discover Modes / Enter Mode / Status Update / Configure
 * 都围绕这里的 SVID、Object Position、Mode VDO 和可接受配置表工作。
 */
typedef struct
{
    uint16_t svid; /* DP Alt Mode 固定使用的 SVID，Discover SVIDs ACK 中返回。 */
    uint8_t object_position; /* 本端 DP Mode 在 Discover Modes 返回列表中的 1-based 位置。 */
    USBPD_DPModeVDO mode_vdo; /* Discover Modes ACK 返回的 DP Capabilities VDO。 */
    USBPD_DPConfigureVDO supported_configurations[4]; /* 本端接受的 Configure VDO 白名单。 */
    uint8_t supported_configuration_count; /* supported_configurations 中有效条目数量。 */
} USBPD_DPAltModeDefinition;

/* 本设备 Discover Identity ACK 使用的静态身份定义。 */
extern const USBPD_VDMIdentityDefinition USBPD_VDM_IDENTITY;
/* 本设备 DisplayPort Alt Mode 使用的能力和配置定义，会随当前 lane 模式更新。 */
extern USBPD_DPAltModeDefinition USBPD_DP_ALT_MODE;

void USBPD_DP_SetLaneMode(USBPD_DPLaneMode mode);
USBPD_DPLaneMode USBPD_DP_GetLaneMode(void);
USBPD_DPLaneMode USBPD_DP_ToggleLaneMode(void);

#endif /* USBPD_VDM_DEFINITIONS_H */
