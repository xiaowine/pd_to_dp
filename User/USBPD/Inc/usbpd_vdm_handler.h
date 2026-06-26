#ifndef USBPD_VDM_HANDLER_H
#define USBPD_VDM_HANDLER_H

#include <stdint.h>
#include "ch32l103_usbpd.h"

/*
 * VDM 处理入口。
 * rx_buf 指向完整 PD 报文（前 2 字节为 Message Header，随后是 Data Objects）。
 * tx_buf 用于组装需要回复的 PD 报文。
 * last_rx_header 是上层已解析出的接收 Message Header，用于读取 NumDO/MsgID 等信息。
 */
void USBPD_VDM_Handle(const uint8_t* rx_buf, uint8_t* tx_buf, const Message_Header* last_rx_header);

/*
 * DP Alt Mode 主动 Attention 发送轮询。
 * 当 Configure 后 HPD 仍为低时，处理逻辑会置 DP_Attention_Pending。
 * 状态机空闲后调用此函数；如果 HPD 已拉高，则主动发送 Attention 通知 DFP_U。
 */
void USBPD_VDM_TrySendAttention(uint8_t* tx_buf);

#endif /* USBPD_VDM_HANDLER_H */
