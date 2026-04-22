#ifndef USBPD_RDO_H
#define USBPD_RDO_H

#include <stdint.h>

/*
 * USB PD r3.2 v1.2 (2026-03) RDO 位定义
 * 依据：
 * - Table 6.19 Fixed/Variable RDO
 * - Table 6.20 Battery RDO
 * - Table 6.21 PPS RDO
 * - Table 6.22 AVS RDO
 */

/* 单位换算辅助宏 */
#define USBPD_RDO_CURR_10MA_TO_MA(c)         ((uint16_t)((c) * 10u))
#define USBPD_RDO_CURR_50MA_TO_MA(c)         ((uint16_t)((c) * 50u))
#define USBPD_RDO_POWER_250MW_TO_MW(p)       ((uint32_t)((p) * 250u))
#define USBPD_RDO_PPS_VOLT_20MV_TO_MV(v)     ((uint16_t)((v) * 20u))
#define USBPD_RDO_AVS_VOLT_25MV_TO_MV(v)     ((uint16_t)((v) * 25u))

/* Table 6.19~6.22：RDO 通用头 */
typedef union
{
    uint32_t Raw;

    struct
    {
        uint32_t Data : 22; /* bit21..0：具体 RDO 数据区 */
        uint32_t EPRCapable : 1; /* bit22：EPR capable */
        uint32_t UnchunkedExtMsgSupported : 1; /* bit23：支持 Unchunked Extended Messages */
        uint32_t NoUSBSuspend : 1; /* bit24：No USB Suspend */
        uint32_t USBCommCapable : 1; /* bit25：USB Communications Capable */
        uint32_t CapabilityMismatch : 1; /* bit26：Capability Mismatch */
        uint32_t GiveBack : 1; /* bit27：GiveBack（Deprecated） */
        uint32_t ObjectPosition : 4; /* bit31..28：请求的 PDO/APDO 位置 */
    } Bit;
} USBPD_RDO_Generic;

/* Table 6.19：Fixed/Variable RDO */
typedef union
{
    uint32_t Raw;

    struct
    {
        uint32_t MaxOperatingCurrentIn10mA : 10; /* bit9..0：最大工作电流（已废弃，发送端应等于 OperatingCurrent） */
        uint32_t OperatingCurrentIn10mA : 10; /* bit19..10：工作电流，单位 10mA */
        uint32_t Reserved21_20 : 2; /* bit21..20：保留 */
        uint32_t EPRCapable : 1; /* bit22：EPR capable */
        uint32_t UnchunkedExtMsgSupported : 1; /* bit23：支持 Unchunked Extended Messages */
        uint32_t NoUSBSuspend : 1; /* bit24：No USB Suspend */
        uint32_t USBCommCapable : 1; /* bit25：USB Communications Capable */
        uint32_t CapabilityMismatch : 1; /* bit26：Capability Mismatch */
        uint32_t GiveBack : 1; /* bit27：GiveBack（Deprecated） */
        uint32_t ObjectPosition : 4; /* bit31..28：请求的 PDO/APDO 位置 */
    } Bit;
} USBPD_RDO_FixedVariable;

/* Table 6.20：Battery RDO */
typedef union
{
    uint32_t Raw;

    struct
    {
        uint32_t MaxOperatingPowerIn250mW : 10; /* bit9..0：最大工作功率（已废弃，发送端应等于 OperatingPower） */
        uint32_t OperatingPowerIn250mW : 10; /* bit19..10：工作功率，单位 250mW */
        uint32_t Reserved21_20 : 2; /* bit21..20：保留 */
        uint32_t EPRCapable : 1; /* bit22：EPR capable */
        uint32_t UnchunkedExtMsgSupported : 1; /* bit23：支持 Unchunked Extended Messages */
        uint32_t NoUSBSuspend : 1; /* bit24：No USB Suspend */
        uint32_t USBCommCapable : 1; /* bit25：USB Communications Capable */
        uint32_t CapabilityMismatch : 1; /* bit26：Capability Mismatch */
        uint32_t GiveBack : 1; /* bit27：GiveBack（Deprecated） */
        uint32_t ObjectPosition : 4; /* bit31..28：请求的 PDO/APDO 位置 */
    } Bit;
} USBPD_RDO_Battery;

/* Table 6.21：PPS RDO */
typedef union
{
    uint32_t Raw;

    struct
    {
        uint32_t OperatingCurrentIn50mA : 7; /* bit6..0：工作电流，单位 50mA */
        uint32_t Reserved8_7 : 2; /* bit8..7：保留 */
        uint32_t OutputVoltageIn20mV : 12; /* bit20..9：请求输出电压，单位 20mV */
        uint32_t Reserved21 : 1; /* bit21：保留 */
        uint32_t EPRCapable : 1; /* bit22：EPR capable */
        uint32_t UnchunkedExtMsgSupported : 1; /* bit23：支持 Unchunked Extended Messages */
        uint32_t NoUSBSuspend : 1; /* bit24：No USB Suspend */
        uint32_t USBCommCapable : 1; /* bit25：USB Communications Capable */
        uint32_t CapabilityMismatch : 1; /* bit26：Capability Mismatch */
        uint32_t GiveBack : 1; /* bit27：GiveBack（Deprecated） */
        uint32_t ObjectPosition : 4; /* bit31..28：请求的 PDO/APDO 位置 */
    } Bit;
} USBPD_RDO_PPS;

/* Table 6.22：AVS RDO */
typedef union
{
    uint32_t Raw;

    struct
    {
        uint32_t OperatingCurrentIn50mA : 7; /* bit6..0：工作电流，单位 50mA */
        uint32_t Reserved8_7 : 2; /* bit8..7：保留 */
        uint32_t OutputVoltageIn25mV : 12; /* bit20..9：请求输出电压，单位 25mV（bit10..9 应为 00b） */
        uint32_t Reserved21 : 1; /* bit21：保留 */
        uint32_t EPRCapable : 1; /* bit22：EPR capable */
        uint32_t UnchunkedExtMsgSupported : 1; /* bit23：支持 Unchunked Extended Messages */
        uint32_t NoUSBSuspend : 1; /* bit24：No USB Suspend */
        uint32_t USBCommCapable : 1; /* bit25：USB Communications Capable */
        uint32_t CapabilityMismatch : 1; /* bit26：Capability Mismatch */
        uint32_t GiveBack : 1; /* bit27：GiveBack（Deprecated） */
        uint32_t ObjectPosition : 4; /* bit31..28：请求的 PDO/APDO 位置 */
    } Bit;
} USBPD_RDO_AVS;

#endif /* USBPD_RDO_H */
