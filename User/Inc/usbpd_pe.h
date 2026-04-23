#ifndef USBPD_PE_H
#define USBPD_PE_H

#define  PD_BUF_SIZE 34 // PD 报文最大长度（2 字节 PD 头 + 7 个数据对象 * 4 字节/对象）

void USBPD_PE_Init(void);
void USBPD_PE_Run(void);

#endif //USBPD_PE_H
