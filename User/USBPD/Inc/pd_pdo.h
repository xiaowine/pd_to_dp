#ifndef USBPD_PDO_H
#define USBPD_PDO_H

#include <stdint.h>

/*
 * USB PD r3.2 v1.2 (2026-03) PDO/APDO 位定义
 * 依据：
 * - Table 6.7  增强型 PDO（APDO）通用格式
 * - Table 6.13 SPR PPS Source APDO
 * - Table 6.14 SPR PPS Sink APDO
 * - Table 6.15 SPR AVS APDO
 * - Table 6.16 EPR AVS Source APDO
 * - Table 6.17 EPR AVS Sink APDO
 */

typedef enum
{
    USBPD_PDO_TYPE_FIXED = 0u,
    USBPD_PDO_TYPE_BATTERY = 1u,
    USBPD_PDO_TYPE_VARIABLE = 2u,
    USBPD_PDO_TYPE_APDO = 3u,
} USBPD_PDOType;

typedef enum
{
    USBPD_APDO_TYPE_PPS = 0u,
    USBPD_APDO_TYPE_EPR_AVS = 1u,
    USBPD_APDO_TYPE_SPR_AVS = 2u,
    USBPD_APDO_TYPE_INVALID = 3u,
} USBPD_APDOType;

/* 单位换算辅助宏 */
#define USBPD_PDO_VOLT_50MV_TO_MV(v)         ((uint16_t)((v) * 50u))
#define USBPD_PDO_CURR_10MA_TO_MA(c)         ((uint16_t)((c) * 10u))
#define USBPD_PDO_POWER_250MW_TO_MW(p)       ((uint32_t)((p) * 250u))
#define USBPD_APDO_PPS_VOLT_100MV_TO_MV(v)   ((uint16_t)((v) * 100u))
#define USBPD_APDO_PPS_CURR_50MA_TO_MA(c)    ((uint16_t)((c) * 50u))
#define USBPD_APDO_AVS_VOLT_100MV_TO_MV(v)   ((uint16_t)((v) * 100u))
#define USBPD_APDO_AVS_CURR_10MA_TO_MA(c)    ((uint16_t)((c) * 10u))

/* Table 6.6：PDO 通用头 */
typedef union
{
    uint32_t Raw;

    struct
    {
        uint32_t PDOSpecific : 30; /* bit29..0：具体 PDO 内容 */
        uint32_t PDOType : 2; /* bit31..30：PDO 类型 */
    } Bit;
} USBPD_PDO_Generic;

/* Table 6.8：固定 5V Source PDO */
typedef union
{
    uint32_t Raw;

    struct
    {
        uint32_t MaxCurrentIn10mA : 10; /* bit9..0：最大电流，单位 10mA */
        uint32_t VoltageIn50mV : 10; /* bit19..10：电压，单位 50mV（固定应为 100=5V） */
        uint32_t PeakCurrent : 2; /* bit21..20：峰值电流能力 */
        uint32_t Reserved22 : 1; /* bit22：保留 */
        uint32_t EPRCapable : 1; /* bit23：EPR 能力 */
        uint32_t UnchunkedExtMsgSupported : 1; /* bit24：支持 Unchunked Extended Message */
        uint32_t DualRoleData : 1; /* bit25：支持 DR_Swap */
        uint32_t USBCommCapable : 1; /* bit26：支持 USB 数据通信 */
        uint32_t UnconstrainedPower : 1; /* bit27：不受本机内部功耗约束 */
        uint32_t USBSuspendSupported : 1; /* bit28：支持 USB Suspend 规则 */
        uint32_t DualRolePower : 1; /* bit29：支持 PR_Swap */
        uint32_t PDOType : 2; /* bit31..30：00b = Fixed */
    } Bit;
} USBPD_PDO_Fixed5V_Source;

/* Table 6.9：固定 5V Sink PDO */
typedef union
{
    uint32_t Raw;

    struct
    {
        uint32_t OperationalCurrentIn10mA : 10; /* bit9..0：工作电流，单位 10mA */
        uint32_t VoltageIn50mV : 10; /* bit19..10：电压，单位 50mV（固定应为 100=5V） */
        uint32_t Reserved22_20 : 3; /* bit22..20：保留 */
        uint32_t DualRoleData : 1; /* bit25：支持 DR_Swap */
        uint32_t USBCommCapable : 1; /* bit26：支持 USB 数据通信 */
        uint32_t UnconstrainedPower : 1; /* bit27：可由其他电源满足本机需求 */
        uint32_t HigherCapability : 1; /* bit28：满功能需要高于 vSafe5V */
        uint32_t DualRolePower : 1; /* bit29：支持 PR_Swap */
        uint32_t PDOType : 2; /* bit31..30：00b = Fixed */
    } Bit;
} USBPD_PDO_Fixed5V_Sink;

/* Table 6.10：固定 PDO（>5V，Source/Sink 通用） */
typedef union
{
    uint32_t Raw;

    struct
    {
        uint32_t MaxOrOperationalCurrentIn10mA : 10; /* bit9..0：最大/工作电流，单位 10mA */
        uint32_t VoltageIn50mV : 10; /* bit19..10：电压，单位 50mV */
        uint32_t PeakCurrentOrReserved : 2; /* bit21..20：Source 为 PeakCurrent，Sink 保留 */
        uint32_t DeviceFlags29_22 : 8; /* bit29..22：非 5V 固定 PDO 下应忽略 */
        uint32_t PDOType : 2; /* bit31..30：00b = Fixed */
    } Bit;
} USBPD_PDO_FixedGt5V;

/* Table 6.11：Battery PDO */
typedef union
{
    uint32_t Raw;

    struct
    {
        uint32_t MaxPowerIn250mW : 10; /* bit9..0：最大功率，单位 250mW */
        uint32_t MinVoltageIn50mV : 10; /* bit19..10：最小电压，单位 50mV */
        uint32_t MaxVoltageIn50mV : 10; /* bit29..20：最大电压，单位 50mV */
        uint32_t PDOType : 2; /* bit31..30：01b = Battery */
    } Bit;
} USBPD_PDO_Battery;

/* Table 6.12：Variable PDO（非电池） */
typedef union
{
    uint32_t Raw;

    struct
    {
        uint32_t MaxCurrentIn10mA : 10; /* bit9..0：最大电流，单位 10mA */
        uint32_t MinVoltageIn50mV : 10; /* bit19..10：最小电压，单位 50mV */
        uint32_t MaxVoltageIn50mV : 10; /* bit29..20：最大电压，单位 50mV */
        uint32_t PDOType : 2; /* bit31..30：10b = Variable */
    } Bit;
} USBPD_PDO_Variable;

/* Table 6.7：APDO 通用头 */
typedef union
{
    uint32_t Raw;

    struct
    {
        uint32_t APDOData : 28; /* bit27..0：APDO 数据区 */
        uint32_t APDOType : 2; /* bit29..28：APDO 类型 */
        uint32_t PDOType : 2; /* bit31..30：PDO 类型，APDO 必须为 11b */
    } Bit;
} USBPD_APDO_Generic;

/* Table 6.13：SPR PPS Source APDO */
typedef union
{
    uint32_t Raw;

    struct
    {
        uint32_t MaxCurrentIn50mA : 7; /* bit6..0：最大电流，单位 50mA */
        uint32_t Reserved7 : 1; /* bit7：保留 */
        uint32_t MinVoltageIn100mV : 8; /* bit15..8：最小电压，单位 100mV */
        uint32_t Reserved16 : 1; /* bit16：保留 */
        uint32_t MaxVoltageIn100mV : 8; /* bit24..17：最大电压，单位 100mV */
        uint32_t Reserved26_25 : 2; /* bit26..25：保留 */
        uint32_t PPSPowerLimited : 1; /* bit27：PPS Power Limited 标志 */
        uint32_t APDOType : 2; /* bit29..28：APDO 类型，00b = PPS */
        uint32_t PDOType : 2; /* bit31..30：PDO 类型，11b = APDO */
    } Bit;
} USBPD_APDO_PPS_Source;

/* Table 6.14：SPR PPS Sink APDO */
typedef union
{
    uint32_t Raw;

    struct
    {
        uint32_t MaxCurrentIn50mA : 7; /* bit6..0：最大电流，单位 50mA */
        uint32_t Reserved7 : 1; /* bit7：保留 */
        uint32_t MinVoltageIn100mV : 8; /* bit15..8：最小电压，单位 100mV */
        uint32_t Reserved16 : 1; /* bit16：保留 */
        uint32_t MaxVoltageIn100mV : 8; /* bit24..17：最大电压，单位 100mV */
        uint32_t Reserved27_25 : 3; /* bit27..25：保留 */
        uint32_t APDOType : 2; /* bit29..28：APDO 类型，00b = PPS */
        uint32_t PDOType : 2; /* bit31..30：PDO 类型，11b = APDO */
    } Bit;
} USBPD_APDO_PPS_Sink;

/* Table 6.15：SPR AVS APDO */
typedef union
{
    uint32_t Raw;

    struct
    {
        uint32_t MaxCurrent20VIn10mA : 10; /* bit9..0：15~20V 区间最大电流，单位 10mA */
        uint32_t MaxCurrent15VIn10mA : 10; /* bit19..10：9~15V 区间最大电流，单位 10mA */
        uint32_t Reserved25_20 : 6; /* bit25..20：保留 */
        uint32_t PeakCurrent : 2; /* bit27..26：峰值电流能力 */
        uint32_t APDOType : 2; /* bit29..28：APDO 类型，10b = SPR AVS */
        uint32_t PDOType : 2; /* bit31..30：PDO 类型，11b = APDO */
    } Bit;
} USBPD_APDO_SPR_AVS;

/* Table 6.16：EPR AVS Source APDO */
typedef union
{
    uint32_t Raw;

    struct
    {
        uint32_t PDPIn1W : 8; /* bit7..0：PDP，单位 1W */
        uint32_t MinVoltageIn100mV : 8; /* bit15..8：最小电压，单位 100mV */
        uint32_t Reserved16 : 1; /* bit16：保留 */
        uint32_t MaxVoltageIn100mV : 9; /* bit25..17：最大电压，单位 100mV */
        uint32_t PeakCurrent : 2; /* bit27..26：峰值电流能力 */
        uint32_t APDOType : 2; /* bit29..28：APDO 类型，01b = EPR AVS */
        uint32_t PDOType : 2; /* bit31..30：PDO 类型，11b = APDO */
    } Bit;
} USBPD_APDO_EPR_AVS_Source;

/* Table 6.17：EPR AVS Sink APDO */
typedef union
{
    uint32_t Raw;

    struct
    {
        uint32_t PDPIn1W : 8; /* bit7..0：PDP，单位 1W */
        uint32_t MinVoltageIn100mV : 8; /* bit15..8：最小电压，单位 100mV */
        uint32_t Reserved16 : 1; /* bit16：保留 */
        uint32_t MaxVoltageIn100mV : 9; /* bit25..17：最大电压，单位 100mV */
        uint32_t Reserved27_26 : 2; /* bit27..26：保留 */
        uint32_t APDOType : 2; /* bit29..28：APDO 类型，01b = EPR AVS */
        uint32_t PDOType : 2; /* bit31..30：PDO 类型，11b = APDO */
    } Bit;
} USBPD_APDO_EPR_AVS_Sink;

#endif /* USBPD_PDO_H */
