#include "usbpd_vdm_debug.h"

#include "debug.h"

/* 将 Configure VDO 里的 pin assignment 字段转换成日志可读字符。 */
static char USBPD_PinAssignmentToChar(uint32_t pin_assign_field)
{
    switch (pin_assign_field)
    {
    case 0x00000400u: return 'C';
    case 0x00000800u: return 'D';
    case 0x00001000u: return 'E';
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
    const uint8_t port_cap = (uint8_t)(mode_vdo & 0x3u);
    const uint8_t signaling = (uint8_t)((mode_vdo >> 2) & 0xFu);
    const uint8_t receptacle = (uint8_t)((mode_vdo >> 6) & 0x1u);
    const uint8_t usb2_not_used = (uint8_t)((mode_vdo >> 7) & 0x1u);
    const uint8_t src_pin = (uint8_t)((mode_vdo >> 8) & 0xFFu);
    const uint8_t snk_pin = (uint8_t)((mode_vdo >> 16) & 0xFFu);

    PRINT("DP Mode VDO: 0x%08lx PortCap=%s(%u) Signaling=%s(0x%x) Receptacle=%s USB2=%s SrcPins=0x%02x SnkPins=0x%02x\r\n",
        (unsigned long)mode_vdo, USBPD_PortCapabilityToString(port_cap), port_cap,
        (signaling & 0x1u) ? "DP" : "Reserved", signaling, receptacle ? "Type-C receptacle" : "Type-C plug",
        usb2_not_used ? "NotUsed" : "MayBeUsed", src_pin, snk_pin);
}

void USBPD_LogDPStatusVDO(const char* prefix, uint32_t status_vdo)
{
    const uint8_t connected = (uint8_t)(status_vdo & 0x3u);
    const uint8_t power_low = (uint8_t)((status_vdo >> 2) & 0x1u);
    const uint8_t enabled = (uint8_t)((status_vdo >> 3) & 0x1u);
    const uint8_t multi_function_preferred = (uint8_t)((status_vdo >> 4) & 0x1u);
    const uint8_t usb_cfg_request = (uint8_t)((status_vdo >> 5) & 0x1u);
    const uint8_t exit_dp_request = (uint8_t)((status_vdo >> 6) & 0x1u);
    const uint8_t hpd = (uint8_t)((status_vdo >> 7) & 0x1u);
    const uint8_t irq_hpd = (uint8_t)((status_vdo >> 8) & 0x1u);

    PRINT("%sDP Status VDO: 0x%08lx Connect=%s(%u) PowerLow=%u Enabled=%u MFPreferred=%u CfgReq=%s ExitReq=%u HPD=%s IRQ_HPD=%u\r\n",
        prefix, (unsigned long)status_vdo, USBPD_ConnectedToString(connected), connected, power_low, enabled,
        multi_function_preferred, usb_cfg_request ? "USB" : "DP", exit_dp_request, hpd ? "High" : "Low",
        irq_hpd);
}

void USBPD_LogDPConfigVDO(uint32_t config_vdo)
{
    const uint8_t select_cfg = (uint8_t)(config_vdo & 0x3u);
    const uint8_t signaling = (uint8_t)((config_vdo >> 2) & 0xFu);
    const uint32_t pin_assign = config_vdo & 0x0000FF00u;

    PRINT("DP Config VDO: 0x%08lx Select=%s(%u) Signaling=%s(0x%x) PinAssign=%c\r\n", (unsigned long)config_vdo,
        USBPD_SelectConfigToString(select_cfg), select_cfg, (signaling == 0x1u) ? "DP" : "Unspecified/Reserved", signaling,
        USBPD_PinAssignmentToChar(pin_assign));
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
