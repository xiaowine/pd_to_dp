#include "usbpd_vdm.h"
#include "pd_vdm.h"

/*
 * 本设备的 Discover Identity 定义。
 * 这些值会在处理 Discover Identity Request 时被打包成：
 * - ID Header VDO
 * - Cert Stat VDO
 * - Product VDO
 * - UFP VDO
 *
 * 当前 VID/PID/bcdDevice 是项目占位值；如果后续有正式 USB-IF 分配值，
 * 只需要改这里，不需要改 VDM 应答逻辑。
 */
const USBPD_VDMIdentityDefinition USBPD_VDM_IDENTITY = {
    .usb_vendor_id = 0x1209u, /* 占位 VID，写入 ID Header VDO。 */
    .usb_product_id = 0x0001u, /* 占位 PID，写入 Product VDO。 */
    .bcd_device = 0x0001u, /* 占位设备版本号，写入 Product VDO。 */
    .connector_type = USBPD_IDH_CONN_TYPEC_RECEPTACLE, /* 本设备对外是 Type-C 母座。 */
    .product_type_ufp = USBPD_IDH_UFP_PDUSB_PERIPHERAL, /* 本端作为 UFP 时声明为 PD USB 外设。 */
    .usb_highest_speed = USBPD_USB_HIGHEST_SPEED_GEN2, /* UFP VDO: 最高 USB 速率声明为 Gen2。 */
    .usb2_device_capability = USBPD_USB2_CAP_FULL, /* UFP VDO: 支持完整 USB2.0 Device 能力。 */
    .usb32_device_capable = 1u, /* UFP VDO: 支持 USB 3.2 Device。 */
    .ufp_vdo_version = USBPD_UFP_VDO_VER_1P3, /* UFP VDO 使用 1.3 版本格式。 */
};

/*
 * 本设备的 DisplayPort Alt Mode 能力定义。
 * 该结构只描述“我们能接受/声明什么”，不做任何硬件动作。
 * 实际收到 Configure 后是否切 VL171、是否打开 HPD 检测，由 usbpd_vdm_handler.c 决定。
 */
USBPD_DPAltModeDefinition USBPD_DP_ALT_MODE = {
    .svid = USBPD_DP_SVID, /* Discover SVIDs ACK 返回的 DP SVID: 0xFF01。 */
    .object_position = USBPD_DP_OBJECT_POSITION_1, /* 当前只返回一个 DP Mode，因此 Object Position 固定为 1。 */
    .mode_vdo.Bit = {
        .PortCapability = USBPD_DP_PORT_UFP_D, /* 声明本设备 USB-C 口可作为 DP Sink/UFP_D。 */
        .Signaling = USBPD_DP_SIGNAL_DP, /* 声明支持 DP bit rate 和 DP 电气设置。 */
        .ReceptacleIndication = 1u, /* 声明 DP 接口呈现在 Type-C receptacle 上。 */
        .UFP_DPinAssignments = USBPD_DP_PIN_ASSIGN_C | USBPD_DP_PIN_ASSIGN_E, /* Type-C receptacle DP Sink 必须支持 C/E。 */
    },
    .supported_configurations = {
        {
            .Bit = {
                .SelectConfiguration = USBPD_DP_SELECT_USB, /* 允许对端要求切回 USB Configuration。 */
                .Signaling = USBPD_DP_SIGNAL_UNSPECIFIED, /* USB Configuration 下 signaling 必须未指定。 */
                .PinAssignment = USBPD_DP_PIN_ASSIGN_NONE, /* USB Configuration 下不选择 DP pin assignment。 */
            },
        },
        {
            .Bit = {
                .SelectConfiguration = USBPD_DP_SELECT_UFP_D_SINK, /* 允许对端把本设备配置为 DP Sink。 */
                .Signaling = USBPD_DP_SIGNAL_DP, /* DP Configuration 下使用 DP signaling。 */
                .PinAssignment = USBPD_DP_PIN_ASSIGN_C, /* 默认接受 Pin C，也就是 4-lane DP。 */
            },
        },
        {
            .Bit = {
                .SelectConfiguration = USBPD_DP_SELECT_UFP_D_SINK, /* USB-C-to-DP 路径要求接受 Pin E。 */
                .Signaling = USBPD_DP_SIGNAL_DP,
                .PinAssignment = USBPD_DP_PIN_ASSIGN_E,
            },
        },
    },
    .supported_configuration_count = 3u, /* 上面配置白名单的有效条目数量。 */
};

static USBPD_DPLaneMode s_dp_lane_mode = USBPD_DP_LANE_MODE_4LANE;

void USBPD_DP_SetLaneMode(USBPD_DPLaneMode mode)
{
    s_dp_lane_mode = (mode == USBPD_DP_LANE_MODE_2LANE) ? USBPD_DP_LANE_MODE_2LANE : USBPD_DP_LANE_MODE_4LANE;
    USBPD_DP_ALT_MODE.mode_vdo.Bit.UFP_DPinAssignments = USBPD_DP_PIN_ASSIGN_C | USBPD_DP_PIN_ASSIGN_E;
    USBPD_DP_ALT_MODE.supported_configurations[1].Bit.PinAssignment = USBPD_DP_PIN_ASSIGN_C;
    USBPD_DP_ALT_MODE.supported_configurations[2].Bit.PinAssignment = USBPD_DP_PIN_ASSIGN_E;
    USBPD_DP_ALT_MODE.supported_configuration_count = 3u;
    if (s_dp_lane_mode == USBPD_DP_LANE_MODE_2LANE)
    {
        USBPD_DP_ALT_MODE.mode_vdo.Bit.UFP_DPinAssignments |= USBPD_DP_PIN_ASSIGN_D;
        USBPD_DP_ALT_MODE.supported_configurations[3].Bit.SelectConfiguration = USBPD_DP_SELECT_UFP_D_SINK;
        USBPD_DP_ALT_MODE.supported_configurations[3].Bit.Signaling = USBPD_DP_SIGNAL_DP;
        USBPD_DP_ALT_MODE.supported_configurations[3].Bit.PinAssignment = USBPD_DP_PIN_ASSIGN_D;
        USBPD_DP_ALT_MODE.supported_configuration_count = 4u;
    }
}

USBPD_DPLaneMode USBPD_DP_GetLaneMode(void)
{
    return s_dp_lane_mode;
}

USBPD_DPLaneMode USBPD_DP_ToggleLaneMode(void)
{
    const USBPD_DPLaneMode next_mode =
        (s_dp_lane_mode == USBPD_DP_LANE_MODE_2LANE) ? USBPD_DP_LANE_MODE_4LANE : USBPD_DP_LANE_MODE_2LANE;

    USBPD_DP_SetLaneMode(next_mode);
    return next_mode;
}
