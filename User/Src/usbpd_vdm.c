#include "usbpd_vdm.h"

#include <string.h>

#include "pd_vdm.h"
#include "usbpd_helper.h"
#include "usbpd_phy.h"
#include "usbpd_vdm_debug.h"

/* 本文件实现 USB PD Structured VDM 处理，以及 DisplayPort Alt Mode 的最小应答流程。 */

/* DisplayPort 标准 SVID，用于识别 DP Alt Mode。 */
#define USBPD_SVID_DISPLAYPORT         0xFF01u
/* Discover Identity 返回的 USB Vendor ID 占位值。 */
#define USBPD_USB_VID_PLACEHOLDER      0x1209u
/* Discover Identity 返回的 Product ID 占位值。 */
#define USBPD_PRODUCT_ID_PLACEHOLDER   0x0001u
/* Discover Identity 返回的 BCD Device 版本号占位值。 */
#define USBPD_BCD_DEVICE_PLACEHOLDER   0x0001u
/* 将两个 16-bit SVID 打包成一个 32-bit VDO，符合 Discover SVIDs 返回格式。 */
#define USBPD_PACK_SVIDS(svid0, svid1) ((((uint32_t)(svid0)) << 16) | ((uint32_t)(svid1) & 0xFFFFu))

/* Mode VDO bit[1:0]：声明本端具备 DP Sink(UFP_D) 角色。 */
#define USBPD_DP_CAP_PORT_UFP_D        0x00000001u
/* Mode VDO bit[5:2]：声明支持原生 DisplayPort signaling。 */
#define USBPD_DP_CAP_SIGNALING_DP      0x00000004u
/* Mode VDO bit[6]：声明本端是 Type-C 母座(receptacle)。 */
#define USBPD_DP_CAP_RECEPTACLE        0x00000040u
/* Mode VDO bit[7]：声明 USB2.0 通道不可复用。当前未启用，仅保留定义。 */
#define USBPD_DP_CAP_USB2_NOT_USED     0x00000080u
/* Mode VDO bit[15:8]：声明作为 DP Source 时支持 pin assignment C。 */
#define USBPD_DP_CAP_SRC_PIN_ASSIGN_C  0x00000400u
/* Mode VDO bit[15:8]：声明作为 DP Source 时支持 pin assignment D。 */
#define USBPD_DP_CAP_SRC_PIN_ASSIGN_D  0x00000800u
/* Mode VDO bit[15:8]：声明作为 DP Source 时支持 pin assignment E。 */
#define USBPD_DP_CAP_SRC_PIN_ASSIGN_E  0x00001000u
/* Mode VDO bit[23:16]：声明作为 DP Sink 时支持 pin assignment C。 */
#define USBPD_DP_CAP_SNK_PIN_ASSIGN_C  0x00040000u
/* Mode VDO bit[23:16]：声明作为 DP Sink 时支持 pin assignment D。 */
#define USBPD_DP_CAP_SNK_PIN_ASSIGN_D  0x00080000u
/* Mode VDO bit[23:16]：声明作为 DP Sink 时支持 pin assignment E。 */
#define USBPD_DP_CAP_SNK_PIN_ASSIGN_E  0x00100000u

/* 声明本端为 DP Sink(UFP_D)，支持 C/D/E 三组 Sink pin assignment。 */
#define USBPD_DP_CAP_MODE_VDO \
    (USBPD_DP_CAP_PORT_UFP_D | USBPD_DP_CAP_SIGNALING_DP | USBPD_DP_CAP_RECEPTACLE | \
     USBPD_DP_CAP_SNK_PIN_ASSIGN_C | USBPD_DP_CAP_SNK_PIN_ASSIGN_D | USBPD_DP_CAP_SNK_PIN_ASSIGN_E)

/* Status VDO bit[1:0]：当前连接状态为对端已连接到本端的 DP Sink。 */
#define USBPD_DP_STATUS_CONNECT_DP_SINK    0x00000002u
/* Status VDO bit[3]：DP 功能已经启用。 */
#define USBPD_DP_STATUS_ENABLED            0x00000008u
/* Status VDO bit[4]：倾向保留 USB 与 DP 同时工作。 */
#define USBPD_DP_STATUS_MULTI_FUNCTION     0x00000010u
/* Status VDO bit[7]：HPD 为高电平，表示显示链路可用。 */
#define USBPD_DP_STATUS_HPD_HIGH           0x00000080u
/* Status VDO bit[8]：HPD IRQ 事件。当前代码未主动上报，仅保留定义。 */
#define USBPD_DP_STATUS_IRQ_HPD            0x00000100u

/* Configure VDO 中 Select Configuration=USB，表示退出 DP 复用，回到纯 USB。 */
#define USBPD_DP_CONFIG_SELECT_USB         0x00000000u
/* Configure VDO 中 Select Configuration=UFP_D，表示本端作为 DP Sink。 */
#define USBPD_DP_CONFIG_SELECT_UFP_D       0x00000002u
/* Configure VDO 中 Signaling=DisplayPort。 */
#define USBPD_DP_CONFIG_SIGNAL_DP          0x00000004u
/* Configure VDO 中选择 pin assignment C。 */
#define USBPD_DP_CONFIG_PIN_ASSIGN_C       0x00000400u
/* Configure VDO 中选择 pin assignment D。 */
#define USBPD_DP_CONFIG_PIN_ASSIGN_D       0x00000800u
/* Configure VDO 中选择 pin assignment E。 */
#define USBPD_DP_CONFIG_PIN_ASSIGN_E       0x00001000u

/* 根据当前控制状态拼出本端要回传的 DP Status VDO。 */
static uint32_t USBPD_BuildDPStatusVDO(void)
{
    /* 按当前状态构造本端回复的 DP Status VDO。 */
    uint32_t status_vdo = USBPD_DP_STATUS_CONNECT_DP_SINK | USBPD_DP_STATUS_ENABLED |
            USBPD_DP_STATUS_MULTI_FUNCTION;

    if (USBPD_Control.Flag.HPD_Connected)
    {
        status_vdo |= USBPD_DP_STATUS_HPD_HIGH;
    }

    return status_vdo;
}

/* 判断对端给出的 Configure VDO 是否在本端支持范围内。 */
static uint8_t USBPD_IsSupportedDPConfigure(uint32_t config_vdo)
{
    /* 仅接受 USB 配置或 DP Sink 模式下的 C/D/E pin assignment。 */
    const uint32_t config_mask = 0x0000FC3Fu;
    const uint32_t usb_cfg = USBPD_DP_CONFIG_SELECT_USB;
    const uint32_t dp_cfg_c = USBPD_DP_CONFIG_SELECT_UFP_D | USBPD_DP_CONFIG_SIGNAL_DP |
            USBPD_DP_CONFIG_PIN_ASSIGN_C;
    const uint32_t dp_cfg_d = USBPD_DP_CONFIG_SELECT_UFP_D | USBPD_DP_CONFIG_SIGNAL_DP |
            USBPD_DP_CONFIG_PIN_ASSIGN_D;
    const uint32_t dp_cfg_e = USBPD_DP_CONFIG_SELECT_UFP_D | USBPD_DP_CONFIG_SIGNAL_DP |
            USBPD_DP_CONFIG_PIN_ASSIGN_E;

    config_vdo &= config_mask;

    return (uint8_t)((config_vdo == usb_cfg) || (config_vdo == dp_cfg_c) || (config_vdo == dp_cfg_d) ||
        (config_vdo == dp_cfg_e));
}

/* 构造一个标准 USB PD Data Message Header，供 VDM 发送路径复用。 */
static Message_Header USBPD_BuildDataHeader(uint8_t msg_type, uint8_t num_do)
{
    /* 组装标准 Data Message 头，用于发送 VDM 应答。 */
    const Message_Header header = {
        .Message_Header = {
            .MsgType = msg_type,
            .NumDO = num_do,
            .PDRole = USBPD_Control.Flag.PD_Role,
            .SpecRev = USBPD_Control.Flag.PD_Version ? 0b10 : 0b01,
            .PRRole = USBPD_Control.Flag.PR_Role,
            .MsgID = USBPD_Control.Msg_ID & 0x07u,
            .Ext = 0,
        }
    };

    return header;
}

/* 将若干个 32-bit Data Object 封装进发送缓冲区，并发出一帧 Data Message。 */
static void USBPD_SendDataMessage(uint8_t* tx_buf, uint8_t msg_type, uint8_t num_do, const uint32_t* vdo_list)
{
    const Message_Header header = USBPD_BuildDataHeader(msg_type, num_do);
    uint8_t tx_len = 2u;

    /* 先写 16-bit Message Header，再按 32-bit Data Object 顺序写入负载。 */
    memcpy(&tx_buf[0], &header.raw, sizeof(header.raw));
    for (uint8_t i = 0u; i < num_do; i++)
    {
        memcpy(&tx_buf[tx_len], &vdo_list[i], sizeof(vdo_list[i]));
        tx_len = (uint8_t)(tx_len + 4u);
    }

    USBPD_Phy_TxPacket(tx_buf, tx_len, UPD_SOP0, 1);
    USBPD_Control.Msg_ID = (uint8_t)((USBPD_Control.Msg_ID + 1u) & 0x07u);
}

/* 发送 Structured VDM 响应，其中第 0 个 Data Object 固定为 VDM Header。 */
static void USBPD_SendStructuredVDMResponse(uint8_t* tx_buf, const USBPD_VDMHeaderStructured* vdm_header,
                                            const uint8_t num_vdos,
                                            const uint32_t* vdo_list)
{
    uint32_t payload[7] = {0};

    /* Data Object 0 固定放 Structured VDM Header，后续依次拼接 VDO。 */
    payload[0] = vdm_header->Raw;
    if (num_vdos > 1u && vdo_list != NULL)
    {
        memcpy(&payload[1], vdo_list, (num_vdos - 1u) * sizeof(uint32_t));
    }

    USBPD_SendDataMessage(tx_buf, DEF_TYPE_VENDOR_DEFINED, num_vdos, payload);
}

/* 设置响应类型和 SVDM 版本后，统一回发 Structured VDM 响应报文。 */
static void USBPD_ReplyStructuredVDM(uint8_t* tx_buf, USBPD_VDMHeaderStructured* vdm_header, uint8_t command_type,
                                     const uint8_t num_vdos, const uint32_t* vdo_list)
{
    /* DP Alt Mode v2.0 要求 Structured VDM Version 使用 2.0。 */
    vdm_header->Bit.CommandType = command_type;
    vdm_header->Bit.StructuredVDMVersionMajor = USBPD_SVDM_MAJOR_2PX;
    vdm_header->Bit.StructuredVDMVersionMinor = USBPD_SVDM_MINOR_2P0;
    USBPD_SendStructuredVDMResponse(tx_buf, vdm_header, num_vdos, vdo_list);
}


/* 处理 Structured VDM Request，覆盖 DP Alt Mode 枚举和配置相关命令。 */
static void USBPD_HandleStructuredVDMRequest(const uint8_t* rx_buf, uint8_t* tx_buf, const Message_Header* last_header,
                                             USBPD_VDMHeaderStructured* vdm_header)
{
    /* 仅处理 Structured VDM 请求，覆盖 DP Alt Mode 所需的关键命令。 */
    switch (vdm_header->Bit.Command)
    {
    case USBPD_SVDM_CMD_DISCOVER_IDENTITY:
        {
            /* 返回最小可用的 Identity 信息，使对端继续执行 DP Alt Mode 发现流程。 */
            USBPD_VDO_IDHeader id_header = {0};
            const USBPD_VDO_CertStat cert_stat = {0};
            USBPD_VDO_Product product = {0};
            USBPD_VDO_UFP ufp_vdo = {0};
            uint32_t vdos[4] = {0};

            id_header.Bit.USBVendorID = USBPD_USB_VID_PLACEHOLDER;
            id_header.Bit.ConnectorType = USBPD_IDH_CONN_TYPEC_RECEPTACLE;
            id_header.Bit.ModalOperationSupported = 1u;
            id_header.Bit.ProductTypeUFPOrCable = USBPD_IDH_UFP_PDUSB_PERIPHERAL;
            id_header.Bit.USBDeviceCapable = 1u;

            product.Bit.BcdDevice = USBPD_BCD_DEVICE_PLACEHOLDER;
            product.Bit.USBProductID = USBPD_PRODUCT_ID_PLACEHOLDER;

            ufp_vdo.Bit.USBHighestSpeed = USBPD_USB_HIGHEST_SPEED_GEN2;
            ufp_vdo.Bit.USB2DeviceCapability = USBPD_USB2_CAP_FULL;
            ufp_vdo.Bit.USB32DeviceCapability = 1u;
            ufp_vdo.Bit.UFPVDOVersion = USBPD_UFP_VDO_VER_1P3;

            vdos[0] = id_header.Raw;
            vdos[1] = cert_stat.Raw;
            vdos[2] = product.Raw;
            vdos[3] = ufp_vdo.Raw;
            USBPD_ReplyStructuredVDM(tx_buf, vdm_header, USBPD_SVDM_CMDTYPE_ACK, 5u, vdos);
            break;
        }
    case USBPD_SVDM_CMD_DISCOVER_SVIDS:
        {
            /* Discover SVIDs ACK 中每个 VDO 装两个 16-bit SVID，最后用 0x0000 终止。 */
            const uint32_t vdos[] = {
                USBPD_PACK_SVIDS(USBPD_SVID_DISPLAYPORT, 0x0000u),
            };

            USBPD_ReplyStructuredVDM(tx_buf, vdm_header, USBPD_SVDM_CMDTYPE_ACK, 2u, vdos);
            break;
        }
    case USBPD_SVDM_CMD_DISCOVER_MODES:
        {
            /* 只有 DisplayPort SVID 才返回 DP Mode 能力。 */
            if (vdm_header->Bit.SVID != USBPD_SVID_DISPLAYPORT)
            {
                USBPD_ReplyStructuredVDM(tx_buf, vdm_header, USBPD_SVDM_CMDTYPE_NAK, 1u, NULL);
                break;
            }

            {
                const uint32_t vdos[] = {
                    USBPD_DP_CAP_MODE_VDO,
                };

                USBPD_LogDPModeVDO(vdos[0]);
                USBPD_ReplyStructuredVDM(tx_buf, vdm_header, USBPD_SVDM_CMDTYPE_ACK, 2u, vdos);
            }
            break;
        }
    case USBPD_SVDM_CMD_ENTER_MODE:
        {
            /* 仅接受 DP SVID 的第 1 个 mode entry。 */
            if (vdm_header->Bit.SVID != USBPD_SVID_DISPLAYPORT || vdm_header->Bit.ObjectPosition != 1u)
            {
                USBPD_ReplyStructuredVDM(tx_buf, vdm_header, USBPD_SVDM_CMDTYPE_NAK, 1u, NULL);
                break;
            }

            /* 进入 DP 模式后打开 HPD 检测。 */
            USBPD_Control.Mode_Try_Cnt |= 0x80u;
            USBPD_Control.Flag.HPD_Det_Chk = 1u;
            USBPD_ReplyStructuredVDM(tx_buf, vdm_header, USBPD_SVDM_CMDTYPE_ACK, 1u, NULL);
            break;
        }
    case USBPD_SVDM_CMD_EXIT_MODE:
        {
            /* 退出 DP 模式后清掉进入标志并停止 HPD 检测。 */
            USBPD_Control.Mode_Try_Cnt &= (uint8_t)~0x80u;
            USBPD_Control.Flag.HPD_Det_Chk = 0u;
            USBPD_ReplyStructuredVDM(tx_buf, vdm_header, USBPD_SVDM_CMDTYPE_ACK, 1u, NULL);
            break;
        }
    case USBPD_SVDM_CMD_ATTENTION:
        {
            /* Attention 没有响应报文，只更新本地状态。 */
            if (last_header->Message_Header.NumDO > 1u)
            {
                const uint32_t status_vdo = USBPD_READ_LE32(&rx_buf[6]);
                USBPD_Control.Flag.HPD_Connected = (uint8_t)((status_vdo & 0x1u) ? 1u : 0u);
                USBPD_LogDPStatusVDO("RX ", status_vdo);
            }
            break;
        }
    case DEF_VDM_DP_S_UPDATE:
        {
            /* Status Update: 记录对端状态，并回传本端当前 DP Status。 */
            if (vdm_header->Bit.SVID != USBPD_SVID_DISPLAYPORT)
            {
                USBPD_ReplyStructuredVDM(tx_buf, vdm_header, USBPD_SVDM_CMDTYPE_NAK, 1u, NULL);
                break;
            }

            if (last_header->Message_Header.NumDO > 1u)
            {
                const uint32_t status_vdo = USBPD_READ_LE32(&rx_buf[6]);
                USBPD_Control.Flag.HPD_Connected = (uint8_t)((status_vdo & 0x1u) ? 1u : 0u);
                USBPD_LogDPStatusVDO("RX ", status_vdo);
            }

            {
                const uint32_t vdos[] = {
                    USBPD_BuildDPStatusVDO(),
                };

                USBPD_LogDPStatusVDO("TX ", vdos[0]);
                USBPD_ReplyStructuredVDM(tx_buf, vdm_header, USBPD_SVDM_CMDTYPE_ACK, 2u, vdos);
            }
            break;
        }
    case DEF_VDM_DP_CONFIG:
        {
            /* Configure: 校验配置是否合法，并决定是否维持 HPD 检测。 */
            uint32_t config_vdo = 0u;

            if (vdm_header->Bit.SVID != USBPD_SVID_DISPLAYPORT)
            {
                USBPD_ReplyStructuredVDM(tx_buf, vdm_header, USBPD_SVDM_CMDTYPE_NAK, 1u, NULL);
                break;
            }

            if (last_header->Message_Header.NumDO < 2u)
            {
                USBPD_ReplyStructuredVDM(tx_buf, vdm_header, USBPD_SVDM_CMDTYPE_NAK, 1u, NULL);
                break;
            }

            config_vdo = USBPD_READ_LE32(&rx_buf[6]);
            USBPD_LogDPConfigVDO(config_vdo);
            if (!USBPD_IsSupportedDPConfigure(config_vdo))
            {
                USBPD_ReplyStructuredVDM(tx_buf, vdm_header, USBPD_SVDM_CMDTYPE_NAK, 1u, NULL);
                break;
            }

            if ((config_vdo & 0x03u) == USBPD_DP_CONFIG_SELECT_USB)
            {
                USBPD_Control.Flag.HPD_Det_Chk = 0u;
            }
            else
            {
                USBPD_Control.Flag.HPD_Det_Chk = 1u;
            }
            USBPD_ReplyStructuredVDM(tx_buf, vdm_header, USBPD_SVDM_CMDTYPE_ACK, 1u, NULL);
            break;
        }
    default:
        {
            USBPD_ReplyStructuredVDM(tx_buf, vdm_header, USBPD_SVDM_CMDTYPE_NAK, 1u, NULL);
            break;
        }
    }
}

/* VDM 总入口：解析收到的 VDM Header，并分发到请求/应答处理路径。 */
void USBPD_VDM_Handle(const uint8_t* rx_buf, uint8_t* tx_buf, const Message_Header* last_rx_header)
{
    USBPD_VDMHeaderStructured vdm_header = {0};

    /* Data Object 0 为 VDM Header，从消息头后第 2 字节开始。 */
    memcpy(&vdm_header.Raw, &rx_buf[2], sizeof(vdm_header.Raw));
    if (!vdm_header.Bit.VDMType)
    {
        /* 当前仅处理 Structured VDM，Unstructured VDM 直接忽略。 */
        return;
    }

    switch (vdm_header.Bit.CommandType)
    {
    case USBPD_SVDM_CMDTYPE_REQ:
        {
            USBPD_HandleStructuredVDMRequest(rx_buf, tx_buf, last_rx_header, &vdm_header);
            break;
        }
    case USBPD_SVDM_CMDTYPE_ACK:
    case USBPD_SVDM_CMDTYPE_NAK:
    case USBPD_SVDM_CMDTYPE_BUSY:
        {
            USBPD_LogVDMCommandType(vdm_header.Bit.CommandType);
            break;
        }
    default:
        {
            break;
        }
    }
}
