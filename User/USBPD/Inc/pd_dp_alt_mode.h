#ifndef PD_DP_ALT_MODE_H
#define PD_DP_ALT_MODE_H

#include <stdint.h>

/*
 * VESA DisplayPort Alt Mode 2.0 协议定义。
 * 主要依据：
 * - Table 5-4 Structured VDM Header
 * - Table 5-5 DP Capabilities
 * - Table 5-6 DisplayPort Status Update
 * - Table 5-8 DisplayPort Configurations
 */

/* DisplayPort 标准 SVID，用于 Discover SVIDs / Discover Modes / DP 专用 VDM 命令。 */
#define USBPD_DP_SVID                         0xFF01u

/* DP_SID 下的 DP 专用 Structured VDM 命令号：DisplayPort Status Update。 */
#define USBPD_DP_CMD_STATUS_UPDATE            0x10u
/* DP_SID 下的 DP 专用 Structured VDM 命令号：DisplayPort Configure。 */
#define USBPD_DP_CMD_CONFIGURE                0x11u

/* 当前只暴露一个 DP Mode VDO，因此后续 Enter/Status/Configure 使用 Object Position 1。 */
#define USBPD_DP_OBJECT_POSITION_1            1u

/* Discover SVIDs ACK 中每个 VDO 打包两个 16-bit SVID，高 16 位为第一个 SVID。 */
#define USBPD_PACK_SVIDS(svid0, svid1) \
    ((((uint32_t)(svid0)) << 16) | ((uint32_t)(svid1) & 0xFFFFu))

/*
 * Table 5-5: DP Capabilities VDO bit[1:0]，发送该 Mode VDO 的 Type-C/PD Port Partner
 * 在 DP Alt Mode 中支持的 DP 角色。
 * 这里的“端口”不是 MCU GPIO 端口，也不是 PD 电源 Source/Sink 角色。
 * 在当前项目里，它指本设备这个 USB-C 口对外声明的 DisplayPort 方向能力。
 */
typedef enum
{
    USBPD_DP_PORT_RESERVED = 0u, /* 00b：保留，不应作为有效能力上报。 */
    USBPD_DP_PORT_UFP_D = 1u, /* 01b：本端可作为 DP Sink 设备（UFP_D）。 */
    USBPD_DP_PORT_DFP_D = 2u, /* 10b：本端可作为 DP Source 设备（DFP_D）。 */
    USBPD_DP_PORT_BOTH = 3u, /* 11b：本端同时支持 DP Source 与 DP Sink。 */
} USBPD_DPPortCapability;

/* Table 5-6: DP Status Update VDO bit[1:0]，当前连接的 DP 设备状态。 */
typedef enum
{
    USBPD_DP_CONNECTED_NONE = 0u, /* 00b：未连接 DP Source/Sink，或适配器被禁用。 */
    USBPD_DP_CONNECTED_SOURCE = 1u, /* 01b：DP Source 设备已连接。 */
    USBPD_DP_CONNECTED_SINK = 2u, /* 10b：DP Sink 设备已连接。 */
    USBPD_DP_CONNECTED_BOTH = 3u, /* 11b：DP Source 与 DP Sink 都已连接。 */
} USBPD_DPConnectedStatus;

/* Table 5-8: DP Configure VDO bit[1:0]，DFP_U 请求 UFP_U 进入的配置。 */
typedef enum
{
    USBPD_DP_SELECT_USB = 0u, /* 00b：切回 USB Configuration，PinAssignment 应为 0。 */
    USBPD_DP_SELECT_UFP_D_SOURCE = 1u, /* 01b：配置 UFP_U 为 DP Source 设备。 */
    USBPD_DP_SELECT_UFP_D_SINK = 2u, /* 10b：配置 UFP_U 为 DP Sink 设备。 */
    USBPD_DP_SELECT_RESERVED = 3u, /* 11b：保留值，应拒绝。 */
} USBPD_DPSelectConfiguration;

/* Table 5-5 / Table 5-8: DisplayPort 协议传输信号类型。 */
typedef enum
{
    USBPD_DP_SIGNAL_UNSPECIFIED = 0u, /* 0h：未指定速率/电气设置，仅用于 USB Configuration。 */
    USBPD_DP_SIGNAL_DP = 1u, /* 1h：使用 DP bit rate 和 DP 电气设置。 */
} USBPD_DPSignaling;

/* Table 5-5 / Table 5-8: Pin Assignment 位图编码，字段本身是 8-bit。 */
typedef enum
{
    USBPD_DP_PIN_ASSIGN_NONE = 0x00u, /* 00h：不选择 Pin Assignment，USB 配置时使用。 */
    USBPD_DP_PIN_ASSIGN_C = 0x04u, /* 04h：Pin Assignment C。 */
    USBPD_DP_PIN_ASSIGN_D = 0x08u, /* 08h：Pin Assignment D。 */
    USBPD_DP_PIN_ASSIGN_E = 0x10u, /* 10h：Pin Assignment E。 */
} USBPD_DPPinAssignment;

/* Table 5-5: DP Capabilities VDO，Discover Modes ACK 中返回的 DP Mode 能力对象。 */
typedef union
{
    uint32_t Raw; /* 32-bit 原始 VDO，用于直接放入 PD Data Object。 */

    struct
    {
        uint32_t PortCapability : 2; /* bit1..0：本端 DP Source/Sink 角色能力，见 USBPD_DPPortCapability。 */
        uint32_t Signaling : 4; /* bit5..2：支持的 DP signaling，bit0=DP，其他位保留。 */
        uint32_t ReceptacleIndication : 1; /* bit6：0=USB-C plug，1=USB-C receptacle。 */
        uint32_t USB2SignalingNotUsed : 1; /* bit7：1=DP 配置下不需要 USB2 A6/A7/B6/B7。 */
        uint32_t DFP_DPinAssignments : 8; /* bit15..8：作为 DP Source/DFP_D 时支持的 pin assignment 位图。 */
        uint32_t UFP_DPinAssignments : 8; /* bit23..16：作为 DP Sink/UFP_D 时支持的 pin assignment 位图。 */
        uint32_t Reserved31_24 : 8; /* bit31..24：保留，应为 0。 */
    } Bit;
} USBPD_DPModeVDO;

/* Table 5-6: DisplayPort Status Update VDO，用于 Status Update ACK 或 Attention VDO。 */
typedef union
{
    uint32_t Raw; /* 32-bit 原始 VDO，用于发送或解析收到的 DP Status。 */

    struct
    {
        uint32_t Connected : 2; /* bit1..0：当前 DP Source/Sink 连接状态，见 USBPD_DPConnectedStatus。 */
        uint32_t PowerLow : 1; /* bit2：1=适配器低功耗，DP 支持被禁用；UFP_U->DFP_U 有效。 */
        uint32_t Enabled : 1; /* bit3：1=DP 功能已启用且可工作。 */
        uint32_t MultiFunctionPreferred : 1; /* bit4：1=倾向 USB SuperSpeed 与 DP 同时工作。 */
        uint32_t USBConfigRequest : 1; /* bit5：1=请求切回 USB Configuration，0=请求/保持 DP Configuration。 */
        uint32_t ExitDPAltModeRequest : 1; /* bit6：1=请求退出 DP Alt Mode。 */
        uint32_t HPDState : 1; /* bit7：HPD 状态，0=HPD_Low，1=HPD_High。 */
        uint32_t IRQ_HPD : 1; /* bit8：1=自上次 status message 后产生过 IRQ_HPD。 */
        uint32_t Reserved31_9 : 23; /* bit31..9：保留，应为 0。 */
    } Bit;
} USBPD_DPStatusVDO;

/* Table 5-8: DisplayPort Configure VDO，DFP_U 通过 Configure 命令下发的配置对象。 */
typedef union
{
    uint32_t Raw; /* 32-bit 原始 VDO，用于解析 Configure 命令或构造支持配置表。 */

    struct
    {
        uint32_t SelectConfiguration : 2; /* bit1..0：选择 USB/DP Source/DP Sink 配置。 */
        uint32_t Signaling : 4; /* bit5..2：DP signaling，USB 配置时为 0，DP 配置时为 1。 */
        uint32_t Reserved7_6 : 2; /* bit7..6：保留，应为 0。 */
        uint32_t PinAssignment : 8; /* bit15..8：选择的 UFP_U Pin Assignment，见 USBPD_DPPinAssignment。 */
        uint32_t Reserved31_16 : 16; /* bit31..16：保留，应为 0。 */
    } Bit;
} USBPD_DPConfigureVDO;

#endif /* PD_DP_ALT_MODE_H */
