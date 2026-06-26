#include "usbpd_vdm_debug.h"

#include "debug.h"
#include "pd_dp_alt_mode.h"

/* 将 Configure VDO 里的 pin assignment 字段转换成日志可读字符。 */
static char USBPD_PinAssignmentToChar(uint8_t pin_assign)
{
    switch (pin_assign)
    {
    case USBPD_DP_PIN_ASSIGN_C: return 'C';
    case USBPD_DP_PIN_ASSIGN_D: return 'D';
    case USBPD_DP_PIN_ASSIGN_E: return 'E';
    default: return '-';
    }
}

/* 将 DP Mode VDO 的端口能力枚举值转成字符串，便于日志打印。 */
static const char* USBPD_PortCapabilityToString(uint8_t port_cap)
{
    switch (port_cap)
    {
    case 0u: return "Reserved";
    case 1u: return "DP Sink(UFP_D)";
    case 2u: return "DP Source(DFP_D)";
    case 3u: return "DP Source+Sink";
    default: return "Unknown";
    }
}

/* 将 DP Status VDO 的 connected 字段转成字符串。 */
static const char* USBPD_ConnectedToString(uint8_t connected)
{
    switch (connected)
    {
    case 0u: return "Disconnected";
    case 1u: return "DP Source connected";
    case 2u: return "DP Sink connected";
    case 3u: return "DP Source+Sink connected";
    default: return "Unknown";
    }
}

/* 将 DP Configure VDO 的 select configuration 字段转成字符串。 */
static const char* USBPD_SelectConfigToString(uint8_t select_cfg)
{
    switch (select_cfg)
    {
    case 0u: return "USB";
    case 1u: return "UFP_U as DP Source";
    case 2u: return "UFP_U as DP Sink";
    case 3u: return "Reserved";
    default: return "Unknown";
    }
}

void USBPD_LogDPModeVDO(uint32_t mode_vdo)
{
    USBPD_DPModeVDO mode = {0};

    mode.Raw = mode_vdo;

    PRINT("DP Mode VDO: 0x%08lx PortCap=%s(%u) Signaling=%s(0x%x) Receptacle=%s USB2=%s SrcPins=0x%02x SnkPins=0x%02x\r\n",
        (unsigned long)mode_vdo, USBPD_PortCapabilityToString((uint8_t)mode.Bit.PortCapability),
        (unsigned)mode.Bit.PortCapability,
        (mode.Bit.Signaling & USBPD_DP_SIGNAL_DP) ? "DP" : "Reserved", (unsigned)mode.Bit.Signaling,
        mode.Bit.ReceptacleIndication ? "Type-C receptacle" : "Type-C plug",
        mode.Bit.USB2SignalingNotUsed ? "NotUsed" : "MayBeUsed",
        (unsigned)mode.Bit.DFP_DPinAssignments, (unsigned)mode.Bit.UFP_DPinAssignments);
}

void USBPD_LogDPStatusVDO(const char* prefix, uint32_t status_vdo)
{
    USBPD_DPStatusVDO status = {0};

    status.Raw = status_vdo;

    PRINT("%sDP Status VDO: 0x%08lx Connect=%s(%u) PowerLow=%u Enabled=%u MFPreferred=%u CfgReq=%s ExitReq=%u HPD=%s IRQ_HPD=%u\r\n",
        prefix, (unsigned long)status_vdo, USBPD_ConnectedToString((uint8_t)status.Bit.Connected),
        (unsigned)status.Bit.Connected, (unsigned)status.Bit.PowerLow, (unsigned)status.Bit.Enabled,
        (unsigned)status.Bit.MultiFunctionPreferred, status.Bit.USBConfigRequest ? "USB" : "DP",
        (unsigned)status.Bit.ExitDPAltModeRequest, status.Bit.HPDState ? "High" : "Low",
        (unsigned)status.Bit.IRQ_HPD);
}

void USBPD_LogDPConfigVDO(uint32_t config_vdo)
{
    USBPD_DPConfigureVDO config = {0};

    config.Raw = config_vdo;

    PRINT("DP Config VDO: 0x%08lx Select=%s(%u) Signaling=%s(0x%x) PinAssign=%c\r\n", (unsigned long)config_vdo,
        USBPD_SelectConfigToString((uint8_t)config.Bit.SelectConfiguration), (unsigned)config.Bit.SelectConfiguration,
        (config.Bit.Signaling == USBPD_DP_SIGNAL_DP) ? "DP" : "Unspecified/Reserved",
        (unsigned)config.Bit.Signaling, USBPD_PinAssignmentToChar((uint8_t)config.Bit.PinAssignment));
}

void USBPD_LogVDMCommandType(uint8_t command_type)
{
    switch (command_type)
    {
    case 1u:
        {
            PRINT("VDM ACK received\r\n");
            break;
        }
    case 2u:
        {
            PRINT("VDM NAK received\r\n");
            break;
        }
    case 3u:
        {
            PRINT("VDM BUSY received\r\n");
            break;
        }
    default:
        {
            break;
        }
    }
}
