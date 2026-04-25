#ifndef USBPD_VDM_H
#define USBPD_VDM_H

#include <stdint.h>

/*
 * USB PD r3.2 v1.2 (2026-03) Vendor Defined Message (VDM) 结构定义
 * 主要依据：
 * - Table 6.32  Unstructured VDM Header
 * - Table 6.33  Structured VDM Header
 * - Table 6.34  ID Header VDO
 * - Table 6.38  Cert Stat VDO
 * - Table 6.39  Product VDO
 * - Table 6.40  UFP VDO
 * - Table 6.41  DFP VDO
 */

/* VDM 类型定义 */
typedef enum
{
    USBPD_VDM_TYPE_UNSTRUCTURED = 0u, /* 非结构化 VDM */
    USBPD_VDM_TYPE_STRUCTURED = 1u, /* 结构化 VDM */
} USBPD_VDMType;

/* Structured VDM 主版本 */
typedef enum
{
    USBPD_SVDM_MAJOR_1P0 = 0u, /* 1.0（已弃用） */
    USBPD_SVDM_MAJOR_2PX = 1u, /* 2.x（当前主流） */
} USBPD_SVDMMajorVersion;

/* Structured VDM 次版本 */
typedef enum
{
    USBPD_SVDM_MINOR_2P0 = 0u, /* 2.0 */
    USBPD_SVDM_MINOR_2P1 = 1u, /* 2.1 */
} USBPD_SVDMMinorVersion;

/* Structured VDM 命令类型 */
typedef enum
{
    USBPD_SVDM_CMDTYPE_REQ = 0u, /* 发起端请求 */
    USBPD_SVDM_CMDTYPE_ACK = 1u, /* 正常应答 */
    USBPD_SVDM_CMDTYPE_NAK = 2u, /* 拒绝/不可处理 */
    USBPD_SVDM_CMDTYPE_BUSY = 3u, /* 忙，应稍后重试 */
} USBPD_SVDMCommandType;

/* Structured VDM 标准命令号 */
typedef enum
{
    USBPD_SVDM_CMD_INVALID = 0u, /* 无效命令 */
    USBPD_SVDM_CMD_DISCOVER_IDENTITY = 1u, /* 发现身份 */
    USBPD_SVDM_CMD_DISCOVER_SVIDS = 2u, /* 发现支持的 SVID */
    USBPD_SVDM_CMD_DISCOVER_MODES = 3u, /* 发现某个 SVID 的模式 */
    USBPD_SVDM_CMD_ENTER_MODE = 4u, /* 进入模式 */
    USBPD_SVDM_CMD_EXIT_MODE = 5u, /* 退出模式 */
    USBPD_SVDM_CMD_ATTENTION = 6u, /* 注意力/状态变更通知 */
} USBPD_SVDMCommand;

/* ID Header VDO: Product Type (UFP/Cable Plug/VPD) */
typedef enum
{
    USBPD_IDH_UFP_NOT_UFP = 0u, /* 非 UFP / 非线缆设备 */
    USBPD_IDH_UFP_PDUSB_HUB = 1u, /* PD USB Hub（SOP/UFP 语义） */
    USBPD_IDH_UFP_PDUSB_PERIPHERAL = 2u, /* PD USB 外设（SOP/UFP 语义） */
    USBPD_IDH_UFP_PSD = 3u, /* PSD（SOP/UFP 语义） */
    USBPD_IDH_UFP_AMA_DEPRECATED = 5u, /* AMA（已弃用） */
    USBPD_IDH_UFP_PASSIVE_CABLE = 3u, /* 被动线缆（SOP' 语义） */
    USBPD_IDH_UFP_ACTIVE_CABLE = 4u, /* 主动线缆（SOP' 语义） */
    USBPD_IDH_UFP_VPD = 6u, /* VCONN Powered Device（SOP' 语义） */
} USBPD_IDHeaderProductTypeUFPOrCable;

/* ID Header VDO: Product Type (DFP) */
typedef enum
{
    USBPD_IDH_DFP_NOT_DFP = 0u, /* 非 DFP */
    USBPD_IDH_DFP_PDUSB_HUB = 1u, /* PD USB Hub */
    USBPD_IDH_DFP_PDUSB_HOST = 2u, /* PD USB Host */
    USBPD_IDH_DFP_POWER_BRICK = 3u, /* 电源砖 */
    USBPD_IDH_DFP_AMC_DEPRECATED = 4u, /* AMC（已弃用） */
} USBPD_IDHeaderProductTypeDFP;

/* ID Header VDO: Connector Type */
typedef enum
{
    USBPD_IDH_CONN_DEPRECATED_UNKNOWN = 0u, /* 已弃用：未知连接器类型 */
    USBPD_IDH_CONN_TYPEC_RECEPTACLE = 2u, /* Type-C 母座 */
    USBPD_IDH_CONN_TYPEC_PLUG = 3u, /* Type-C 公头 */
} USBPD_IDHeaderConnectorType;

/* UFP VDO 版本 */
typedef enum
{
    USBPD_UFP_VDO_VER_INVALID = 0u, /* 非法/无效 */
    USBPD_UFP_VDO_VER_1P1_DEPRECATED = 1u, /* 1.1（已弃用） */
    USBPD_UFP_VDO_VER_1P2_DEPRECATED = 2u, /* 1.2（已弃用） */
    USBPD_UFP_VDO_VER_1P3 = 3u, /* 1.3 */
} USBPD_UFPVDOVersion;

/* DFP VDO 版本 */
typedef enum
{
    USBPD_DFP_VDO_VER_INVALID = 0u, /* 非法/无效 */
    USBPD_DFP_VDO_VER_1P1_DEPRECATED = 1u, /* 1.1（已弃用） */
    USBPD_DFP_VDO_VER_1P2 = 2u, /* 1.2 */
} USBPD_DFPVDOVersion;

/* UFP VDO 中 USB2 设备能力编码 */
typedef enum
{
    USBPD_USB2_CAP_NONE = 0u, /* 不支持 USB2.0 设备能力 */
    USBPD_USB2_CAP_BILLBOARD_ONLY = 1u, /* 仅支持 Billboard 设备 */
    USBPD_USB2_CAP_FULL = 2u, /* 支持完整 USB2.0 设备 */
} USBPD_USB2DeviceCapability;

/* UFP/线缆 VDO 中最高速率编码 */
typedef enum
{
    USBPD_USB_HIGHEST_SPEED_USB2_ONLY = 0u, /* 仅 USB2.0 */
    USBPD_USB_HIGHEST_SPEED_GEN1 = 1u, /* USB3 Gen1 */
    USBPD_USB_HIGHEST_SPEED_GEN2 = 2u, /* USB3/USB4 Gen2 */
    USBPD_USB_HIGHEST_SPEED_GEN3 = 3u, /* USB4 Gen3 */
    USBPD_USB_HIGHEST_SPEED_GEN4 = 4u, /* USB4 Gen4 */
} USBPD_USBHighestSpeed;

/* Table 6.32: Unstructured VDM Header（非结构化 VDM 头） */
typedef union
{
    uint32_t Raw; /* 32-bit 原始值 */

    struct
    {
        uint32_t VendorDefined15_0 : 15; /* bit14..0：厂商自定义字段 */
        uint32_t VDMType : 1; /* bit15：VDM 类型，0=Unstructured */
        uint32_t VendorID : 16; /* bit31..16：厂商 VID */
    } Bit;
} USBPD_VDMHeaderUnstructured;

/* Table 6.33: Structured VDM Header（结构化 VDM 头） */
typedef union
{
    uint32_t Raw; /* 32-bit 原始值 */

    struct
    {
        uint32_t Command : 5; /* bit4..0：命令号（Discover/Enter/Exit 等） */
        uint32_t Reserved5 : 1; /* bit5：保留位 */
        uint32_t CommandType : 2; /* bit7..6：REQ/ACK/NAK/BUSY */
        uint32_t ObjectPosition : 3; /* bit10..8：对象位置（模式索引等） */
        uint32_t StructuredVDMVersionMinor : 2; /* bit12..11：SVDM 次版本 */
        uint32_t StructuredVDMVersionMajor : 2; /* bit14..13：SVDM 主版本 */
        uint32_t VDMType : 1; /* bit15：VDM 类型，1=Structured */
        uint32_t SVID : 16; /* bit31..16：标准/厂商 ID（SVID） */
    } Bit;
} USBPD_VDMHeaderStructured;

/* Table 6.34: ID Header VDO（发现身份响应中的身份头对象） */
typedef union
{
    uint32_t Raw;

    struct
    {
        uint32_t USBVendorID : 16; /* bit15..0：USB-IF 分配的厂商 ID（VID） */
        uint32_t Reserved20_16 : 5; /* bit20..16：保留位 */
        uint32_t ConnectorType : 2; /* bit22..21：连接器类型（Type-C 插座/插头） */
        uint32_t ProductTypeDFP : 3; /* bit25..23：DFP 侧产品类型（Hub/Host/Power Brick） */
        uint32_t ModalOperationSupported : 1; /* bit26：是否支持模态操作（Alternate Mode） */
        uint32_t ProductTypeUFPOrCable : 3; /* bit29..27：UFP 或线缆/VPD 产品类型 */
        uint32_t USBDeviceCapable : 1; /* bit30：是否可作为 USB 设备被枚举 */
        uint32_t USBHostCapable : 1; /* bit31：是否可作为 USB 主机枚举外设 */
    } Bit;
} USBPD_VDO_IDHeader;

/* Table 6.38: Cert Stat VDO（认证状态对象） */
typedef union
{
    uint32_t Raw;

    struct
    {
        uint32_t XID; /* bit31..0：USB-IF 分配给产品的 XID（无则填 0） */
    } Bit;
} USBPD_VDO_CertStat;

/* Table 6.39: Product VDO（产品信息对象） */
typedef union
{
    uint32_t Raw;

    struct
    {
        uint32_t BcdDevice : 16; /* bit15..0：设备版本号（bcdDevice） */
        uint32_t USBProductID : 16; /* bit31..16：产品 ID（PID） */
    } Bit;
} USBPD_VDO_Product;

/* Table 6.40: UFP VDO（UFP 能力对象） */
typedef union
{
    uint32_t Raw;

    struct
    {
        uint32_t USBHighestSpeed : 3; /* bit2..0：端口支持的最高速率（USB2/Gen1/Gen2/Gen3/Gen4） */
        uint32_t Reserved10_3 : 8; /* bit10..3：保留位 */
        uint32_t Reserved21_11 : 11; /* bit21..11：保留位 */
        uint32_t ConnectorTypeLegacy : 2; /* bit23..22：旧连接器类型字段（已废弃，通常为 00） */
        uint32_t USB2DeviceCapability : 2; /* bit25..24：USB2.0 设备能力 */
        uint32_t USB32DeviceCapability : 1; /* bit26：USB 3.2 设备能力 */
        uint32_t USB4DeviceCapability : 1; /* bit27：USB4 设备能力 */
        uint32_t Reserved28 : 1; /* bit28：保留位 */
        uint32_t UFPVDOVersion : 3; /* bit31..29：UFP VDO 版本号 */
    } Bit;
} USBPD_VDO_UFP;

/* Table 6.41: DFP VDO（DFP 能力对象） */
typedef union
{
    uint32_t Raw;

    struct
    {
        uint32_t PortNumber : 5; /* bit4..0：DFP 端口编号（设备内唯一） */
        uint32_t Reserved21_5 : 17; /* bit21..5：保留位 */
        uint32_t ConnectorTypeLegacy : 2; /* bit23..22：旧连接器类型字段（已废弃，通常为 00） */
        uint32_t USB20HostCapability : 1; /* bit24：USB2.0 Host 能力 */
        uint32_t USB32HostCapability : 1; /* bit25：USB 3.2 Host 能力 */
        uint32_t USB4HostCapability : 1; /* bit26：USB4 Host 能力 */
        uint32_t Reserved28_27 : 2; /* bit28..27：保留位 */
        uint32_t DFPVDOVersion : 3; /* bit31..29：DFP VDO 版本号 */
    } Bit;
} USBPD_VDO_DFP;

#endif /* USBPD_VDM_H */
