#include "pd_helper.h"
#include "debug.h"

static uint32_t USBPD_ReadU32LE(const uint8_t* p)
{
    return (uint32_t)p[0]
            | (uint32_t)p[1] << 8
            | (uint32_t)p[2] << 16
            | (uint32_t)p[3] << 24;
}

static void USBPD_PrintFixedPDO(const uint8_t index, const uint32_t raw)
{
    if (index == 1u)
    {
        USBPD_PDO_Fixed5V_Source pdo;
        pdo.Raw = raw;
        PRINT("[PDO%u] Fixed5V: V=%umV I=%umA DRP=%u DRD=%u USBComm=%u EPR=%u\r\n",
              index,
              (unsigned)USBPD_PDO_VOLT_50MV_TO_MV(pdo.Bit.VoltageIn50mV),
              (unsigned)USBPD_PDO_CURR_10MA_TO_MA(pdo.Bit.MaxCurrentIn10mA),
              (unsigned)pdo.Bit.DualRolePower,
              (unsigned)pdo.Bit.DualRoleData,
              (unsigned)pdo.Bit.USBCommCapable,
              (unsigned)pdo.Bit.EPRCapable);
        return;
    }

    USBPD_PDO_FixedGt5V pdo;
    pdo.Raw = raw;
    PRINT("[PDO%u] Fixed: V=%umV I=%umA Peak=%u\r\n",
          index,
          (unsigned)USBPD_PDO_VOLT_50MV_TO_MV(pdo.Bit.VoltageIn50mV),
          (unsigned)USBPD_PDO_CURR_10MA_TO_MA(pdo.Bit.MaxOrOperationalCurrentIn10mA),
          (unsigned)pdo.Bit.PeakCurrentOrReserved);
}

static void USBPD_PrintBatteryPDO(const uint8_t index, const uint32_t raw)
{
    USBPD_PDO_Battery pdo;
    pdo.Raw = raw;
    PRINT("[PDO%u] Battery: %u-%umV Pmax=%umW\r\n",
          index,
          (unsigned)USBPD_PDO_VOLT_50MV_TO_MV(pdo.Bit.MinVoltageIn50mV),
          (unsigned)USBPD_PDO_VOLT_50MV_TO_MV(pdo.Bit.MaxVoltageIn50mV),
          (unsigned)USBPD_PDO_POWER_250MW_TO_MW(pdo.Bit.MaxPowerIn250mW));
}

static void USBPD_PrintVariablePDO(const uint8_t index, const uint32_t raw)
{
    USBPD_PDO_Variable pdo;
    pdo.Raw = raw;
    PRINT("[PDO%u] Variable: %u-%umV Imax=%umA\r\n",
          index,
          (unsigned)USBPD_PDO_VOLT_50MV_TO_MV(pdo.Bit.MinVoltageIn50mV),
          (unsigned)USBPD_PDO_VOLT_50MV_TO_MV(pdo.Bit.MaxVoltageIn50mV),
          (unsigned)USBPD_PDO_CURR_10MA_TO_MA(pdo.Bit.MaxCurrentIn10mA));
}

static void USBPD_PrintAPDO(const uint8_t index, const uint32_t raw)
{
    USBPD_APDO_Generic apdo;
    apdo.Raw = raw;

    switch (apdo.Bit.APDOType)
    {
    case USBPD_APDO_TYPE_PPS:
        {
            USBPD_APDO_PPS_Source pps;
            pps.Raw = raw;
            PRINT("[PDO%u] APDO-PPS: %u-%umV Imax=%umA PowerLimited=%u\r\n",
                  index,
                  (unsigned)USBPD_APDO_PPS_VOLT_100MV_TO_MV(pps.Bit.MinVoltageIn100mV),
                  (unsigned)USBPD_APDO_PPS_VOLT_100MV_TO_MV(pps.Bit.MaxVoltageIn100mV),
                  (unsigned)USBPD_APDO_PPS_CURR_50MA_TO_MA(pps.Bit.MaxCurrentIn50mA),
                  (unsigned)pps.Bit.PPSPowerLimited);
            break;
        }
    case USBPD_APDO_TYPE_EPR_AVS:
        {
            USBPD_APDO_EPR_AVS_Source avs;
            avs.Raw = raw;
            PRINT("[PDO%u] APDO-EPR-AVS: %u-%umV PDP=%uW Peak=%u\r\n",
                  index,
                  (unsigned)USBPD_APDO_AVS_VOLT_100MV_TO_MV(avs.Bit.MinVoltageIn100mV),
                  (unsigned)USBPD_APDO_AVS_VOLT_100MV_TO_MV(avs.Bit.MaxVoltageIn100mV),
                  (unsigned)avs.Bit.PDPIn1W,
                  (unsigned)avs.Bit.PeakCurrent);
            break;
        }
    case USBPD_APDO_TYPE_SPR_AVS:
        {
            USBPD_APDO_SPR_AVS avs;
            avs.Raw = raw;
            PRINT("[PDO%u] APDO-SPR-AVS: I9-15V=%umA I15-20V=%umA Peak=%u\r\n",
                  index,
                  (unsigned)USBPD_APDO_AVS_CURR_10MA_TO_MA(avs.Bit.MaxCurrent15VIn10mA),
                  (unsigned)USBPD_APDO_AVS_CURR_10MA_TO_MA(avs.Bit.MaxCurrent20VIn10mA),
                  (unsigned)avs.Bit.PeakCurrent);
            break;
        }
    default:
        PRINT("[PDO%u] APDO-Invalid: raw=0x%08lx\r\n", index, (unsigned long)raw);
        break;
    }
}

void USBPD_PDO_Analyse(const uint8_t* message)
{
    if (!message)
    {
        PRINT("PDO analyse: no message\r\n");
        return;
    }

    Message_Header h;
    h.raw = (uint16_t)message[0] | (uint16_t)message[1] << 8;

    if (h.Message_Header.NumDO == 0u)
    {
        PRINT("PDO analyse: NumDO=0\r\n");
        return;
    }

    uint8_t num_do = h.Message_Header.NumDO;
    if (num_do > 7u)
    {
        num_do = 7u;
    }

    /* message[0..1] is PD header, followed by NumDO * 4-byte data objects */
    for (uint8_t i = 0; i < num_do; i++)
    {
        const uint8_t* obj = &message[2u + (uint8_t)(i * 4u)];
        const uint32_t raw = USBPD_ReadU32LE(obj);
        USBPD_PDO_Generic pdo;
        pdo.Raw = raw;

        switch (pdo.Bit.PDOType)
        {
        case USBPD_PDO_TYPE_FIXED:
            USBPD_PrintFixedPDO((uint8_t)(i + 1u), raw);
            break;
        case USBPD_PDO_TYPE_BATTERY:
            USBPD_PrintBatteryPDO((uint8_t)(i + 1u), raw);
            break;
        case USBPD_PDO_TYPE_VARIABLE:
            USBPD_PrintVariablePDO((uint8_t)(i + 1u), raw);
            break;
        case USBPD_PDO_TYPE_APDO:
            USBPD_PrintAPDO((uint8_t)(i + 1u), raw);
            break;
        default:
            PRINT("[PDO%u] Unknown type: raw=0x%08lx\r\n", (unsigned)(i + 1u), (unsigned long)raw);
            break;
        }
    }
}

uint8_t USBPD_FIND_5V_PDO(const uint8_t* message)
{
    if (!message)
    {
        PRINT("PDO analyse: no message\r\n");
        return 0;
    }

    Message_Header h;
    h.raw = (uint16_t)message[0] | (uint16_t)message[1] << 8;

    if (h.Message_Header.NumDO == 0u)
    {
        PRINT("PDO analyse: NumDO=0\r\n");
        return 0;
    }

    const uint8_t num_do = h.Message_Header.NumDO;
    if (num_do > 7u)
    {
        return 0;
    }
    uint8_t index_5v = 0;
    for (uint8_t i = 0; i < num_do; i++)
    {
        const uint8_t* obj = &message[2u + (uint8_t)(i * 4u)];
        const uint32_t raw = USBPD_ReadU32LE(obj);
        USBPD_PDO_Fixed5V_Source pdo;
        pdo.Raw = raw;
        if ((pdo.Bit.PDOType == USBPD_PDO_TYPE_FIXED) && pdo.Bit.VoltageIn50mV == 100u && pdo.Bit.USBCommCapable)
        {
            index_5v = (uint8_t)(i + 1u);
            break;
        }
    }
    return index_5v;
}
