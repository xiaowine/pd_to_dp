# PD_DP 代码地图

这份地图按当前代码生成，用来快速建立项目全貌。它不是协议规范替代品，重点是回答：

- 程序从哪里启动。
- USB PD Sink 协商、DP Alt Mode、HPD 上报分别由哪些文件负责。
- 关键状态和副作用在哪里发生。
- 想改某类行为时应该先看哪几个文件。

## 项目定位

这是运行在 CH32L103 上的 USB-C PD Sink + DisplayPort Alt Mode 固件。

主要目标：

- 作为 USB PD Sink，等待 Source_Capabilities，选择 5V PDO 并发送 Request。
- 在显式合约建立后，响应 DFP_U 发起的 Structured VDM / DisplayPort Alt Mode 流程。
- 根据 DP Configure 切换 VL171，使 Type-C 高速线进入 USB、2-lane DP + USB3、或 4-lane DP。
- 采集 PB14 上的 HPD，并通过 DP Status ACK / Attention 上报 HPD High、Low、IRQ_HPD。

## 先读什么

建议按这个顺序读：

1. `User/App/main.c`
   - 看初始化顺序、主循环、attach 回调里怎么设置 VL171 方向。

2. `User/USBPD/Src/usbpd_phy.c`
   - 看 CC attach/detach 检测、USBPD 外设收发、GoodCRC 等待和重试。

3. `User/USBPD/Src/usbpd_pe.c`
   - 看 Sink Policy Engine：Source_Cap、Request、Accept、PS_RDY、Soft Reset、Data Reset。

4. `User/USBPD/Src/usbpd_vdm_handler.c`
   - 看 VDM / DP Alt Mode 命令处理和 Attention 发送。

5. `User/USBPD/Src/usbpd_hpd.c`
   - 看 HPD 事件如何从 PB14 边沿变成 DP Status / Attention。

6. `User/USBPD/Src/usbpd_vdm.c`
   - 看本设备 Identity、DP Mode VDO、支持的 Configure VDO 白名单。

## 目录职责

```text
Core/
  CH32L103 外设库、寄存器定义、USBPD 外设基础定义。

Core/cmake/
  core 静态库源码列表和 RISC-V 交叉编译工具链配置。

Platform/
  启动文件、链接脚本、芯片手册、USB PD / DP Alt Mode 规范 PDF。

User/App/
  应用入口、系统时钟配置、上电 lane 模式选择、PD attach/detach 回调。

User/Board/
  板级 GPIO、HPD EXTI、LED PWM、TIM4 时间基准、串口日志。

User/Drivers/
  板上外设驱动。目前主要是 VL171 高速线切换控制。

User/USBPD/
  USB PD 协议层、Policy Engine、VDM/DP Alt Mode、HPD 控制器、PDO/RDO/VDO 位域定义。
```

## 构建入口

顶层入口是 `CMakeLists.txt`。

关键点：

- 默认项目名：`pd_dp`。
- 语言：C99 + ASM。
- 工具链：`Core/cmake/toolchain.cmake`。
- 芯片宏：`CH32L103`。
- 启动文件：`Platform/startup_ch32l103.S`。
- 链接脚本：`Platform/Link.ld`。
- 用户源码通过 `file(GLOB USER_SOURCES CONFIGURE_DEPENDS ...)` 收集：
  - `User/App/*.c`
  - `User/Board/Src/*.c`
  - `User/Drivers/Src/*.c`
  - `User/USBPD/Src/*.c`
- 输出：
  - `pd_dp.elf`
  - `pd_dp.hex`
  - `pd_dp.bin`
  - `pd_dp.map`

常用构建：

```powershell
cmake --build cmake-build-debug-wch-gcc15
```

## 启动和主循环

入口：`User/App/main.c`

```text
main()
  RCC_DeInit()
  SystemClock_Config()
  NVIC_PriorityGroupConfig()
  Delay_Init()
  USART_Printf_Init(2000000)
  USBPD_Tim_Init()
  BoardIO_Init()
  App_SetStartupLaneMode()
  USBPD_Phy_Init()
  while (1)
    USBPD_Phy_Run()
```

上电 lane 模式：

- `BoardIO_IsKeyPressed()` 读取 PA0。
- PA0 按下：`USBPD_DP_LANE_MODE_4LANE`。
- PA0 未按下：`USBPD_DP_LANE_MODE_2LANE`。
- LED2 指示当前选择：
  - 亮：4-lane。
  - 灭：2-lane。

主循环只调用 `USBPD_Phy_Run()`。后续 attach 检测、PE 状态机、VDM、HPD Attention 都从这里被驱动。

## 中断入口

本项目几个关键中断：

- `USBPD_IRQHandler()` in `User/USBPD/Src/usbpd_pe.c`
  - 处理 USBPD RX/TX/Reset/Buffer Error。
  - 收到非 GoodCRC 报文时立即发送 GoodCRC。
  - 做 MessageID 去重，然后置 `USBPD_Control.Flag.Msg_Recvd` 交给主循环 PE 处理。

- `TIM4_IRQHandler()` in `User/Board/Src/tim.c`
  - 维护 `USBPD_Tim_Ms_Cnt` 毫秒计数。
  - 维护 16-bit 微秒时间基准 `s_usbpd_tim_us16`。

- `EXTI15_10_IRQHandler()` in `User/Board/Src/board_io.c`
  - 只处理 PB14 / EXTI14。
  - 调用弱符号 `DP_HPD_EdgeCallback()`。
  - 实际 HPD 逻辑由 `User/USBPD/Src/usbpd_hpd.c` 覆盖这个回调。

## 共享状态

核心全局状态在 `Core/Inc/ch32l103_usbpd.h` 和 `User/USBPD/Src/usbpd_phy.c`。

`USBPD_Control` 是全局 PD 控制块：

- `PD_State` / `PD_State_Last`：当前和上一个 PE 状态。
- `Msg_ID`：本端发送 MessageID，发送成功后递增。
- `Tx_GoodCRC_MsgID` / `Flag.Tx_GoodCRC_Received`：发送端等待 GoodCRC 用。
- `Rx_Last_MsgID` / `Flag.Rx_MsgID_Valid`：接收端去重用。
- `Flag.Msg_Recvd`：ISR 已收包，主循环待处理。
- `Flag.Connected`：CC 检测层认为已 attach。
- `Flag.Explicit_Contract`：Sink 已经收到 PS_RDY，电源合约完成。
- `Flag.DP_Modes_Discovered`：已经成功 ACK 过 DP Discover Modes。
- `Mode_Try_Cnt & 0x80`：当前被当作 DP Mode active 标志。
- `PE_Timer`：PE 等待状态计时。
- `HardResetCounter`：等待 Source_Cap 超时后发送 Hard Reset 的次数。
- `SVDM_MajorVersion` / `SVDM_MinorVersion`：当前连接协商出的 SVDM 版本。

PE 缓冲区在 `User/USBPD/Src/usbpd_pe.c`：

- `pe_rx_buf[PD_BUF_SIZE]`：USBPD DMA RX buffer。
- `pe_tx_buf[PD_BUF_SIZE]`：发送 buffer。
- `last_rx_header`：最近收到的 SOP Header。

DP 能力在 `User/USBPD/Src/usbpd_vdm.c`：

- `USBPD_VDM_IDENTITY`：Discover Identity 使用的 VID/PID/UFP VDO 配置。
- `USBPD_DP_ALT_MODE`：DP SVID、Object Position、Mode VDO、Configure 白名单。
- `s_dp_lane_mode`：上电按键决定的 2-lane 或 4-lane 偏好。

HPD 状态在 `User/USBPD/Src/usbpd_hpd.c`：

- `s_enabled`：HPD 控制器是否启用。
- `s_logical_high`：滤波后的逻辑 HPD。
- `s_high_pending` / `s_low_pending`：High 防抖和 Low 脉宽检测。
- `s_pending_high` / `s_pending_low` / `s_pending_irq_count`：待上报事件。
- `s_reported_valid` / `s_reported_high`：是否已经通过 Status/Attention 建立过 HPD baseline。

## Board IO

主要文件：

- `User/Board/Inc/board_io.h`
- `User/Board/Src/board_io.c`

关键引脚：

```text
PA0   KEY，上拉输入，上电采样 lane 模式。
PA8   LED1，TIM1 PWM，用于 CC attach 方向/连接提示。
PB15  LED2，当前 lane 模式指示。
PB14  HPD，下拉输入，EXTI14 双边沿。
PB0   VL171 AMSEL。
PA7   VL171 EN。
PA5   VL171 POL。
PB6   USBPD CC1。
PB7   USBPD CC2。
```

HPD EXTI 默认关闭。只有进入 DP Mode 后，`USBPD_HPD_EnterMode()` 才会打开 PB14 EXTI。

## 时间基准

主要文件：

- `User/Board/Inc/tim.h`
- `User/Board/Src/tim.c`

`TIM4` 提供两种时间：

- `USBPD_Tim_Ms_Cnt`
  - 8-bit 毫秒节拍。
  - PE 用差值处理溢出。

- `USBPD_Tim_GetUs16()`
  - 16-bit 微秒时间戳。
  - HPD 脉宽测量使用。

HPD 时间阈值：

```text
< 250us        忽略/不构成有效 HPD 事件
250us..2000us  IRQ_HPD
>= 2000us      HPD Low / Hot Unplug
```

## Attach / Detach 流程

入口：`USBPD_Phy_Run()` in `User/USBPD/Src/usbpd_phy.c`

```text
USBPD_Phy_Run()
  计算毫秒增量
  每约 5ms 调 USBPD_Phy_Detect_Check()
  每轮调 USBPD_PE_Run()
```

Attach 检测：

```text
USBPD_Phy_Detect_Check()
  关闭 CC_LVE
  分别读取 CC1/CC2 比较器
  找到 0.22V..2.20V 且另一侧未达到 0.22V 的 CC
  连续 5 次稳定后认为 attach
  设置 CC_SEL
  USBPD_Phy_Detect_EventCallback(PD_EVENT_ATTACH, cc)
  USBPD_PE_Reset()
  SWITCH_PD_STATE(STA_RX_SRC_CAP_WAIT)
  USBPD_Phy_EnterRxMode()
```

App 层 attach 回调：

```text
USBPD_Phy_Detect_EventCallback(PD_EVENT_ATTACH, cc)
  CC1 -> VL171_ORIENTATION_NORMAL
  CC2 -> VL171_ORIENTATION_FLIPPED
  默认先 VL171_ApplyMode(VL171_MODE_USB_DP_2LANE)
  LED1 PWM 指示方向
```

Detach 检测：

```text
已连接时，如果当前选中 CC 连续 5 次不匹配
  Flag.Connected = 0
  USBPD_Phy_Detect_EventCallback(PD_EVENT_DETACH, ret)
  USBPD_PE_Reset()
  SWITCH_PD_STATE(STA_DISCONNECT)
```

`USBPD_PE_Reset()` 会清显式合约、DP Mode active、DP discovered、HPD 状态，并把 VL171 切回 USB。

## PHY 收发层

主要文件：

- `User/USBPD/Src/usbpd_phy.c`
- `User/USBPD/Src/usbpd_pe.c` 的 `USBPD_IRQHandler()`

发送入口：

- `USBPD_Phy_TxPacket()`
  - 原始 PD packet 发送。
  - 统一等待 `tInterFrameGap = 25us`。
  - `sync_mode=1` 时轮询 `IF_TX_END`，发送完成后回 RX。

- `USBPD_Phy_TxMessageWaitGoodCRC()`
  - 发送普通 PD message 并等待 GoodCRC。
  - 发送前要求 100us 内没有 RX 活动。
  - GoodCRC 超时：1200us。
  - 重试次数：2，也就是最多 3 次发送。
  - 只有收到匹配 MessageID 的 GoodCRC 才返回 OK。

接收路径：

```text
USBPD_IRQHandler()
  IF_RX_ACT
    if SOP0
      解析 last_rx_header
      if GoodCRC
        记录 Tx_GoodCRC_MsgID
      else
        根据对端 Header 更新 PD2.0/PD3.0
        立即发送 GoodCRC
        如果 MessageID 重复，只 GoodCRC 不投递给 PE
        否则置 Flag.Msg_Recvd
  IF_RX_RESET
    USBPD_PE_Reset()
    如果还 connected -> STA_RX_SRC_CAP_WAIT
    重新进入 RX
```

发送失败的上层策略：

- PE 发送 Request 失败：走 `USBPD_PE_StartProtocolRecovery()`，发 Soft Reset 并回 Source_Cap 等待。
- VDM 发送失败：`USBPD_SendDataMessage()` 会触发 `USBPD_PE_ProtocolErrorRecovery()`。
- Exit Mode / Configure 的 ACK 丢失会在 VDM 层回滚本地 DP/HPD/VL171 状态。

## PE 状态机

主要文件：`User/USBPD/Src/usbpd_pe.c`

当前实际使用的状态：

```text
STA_DISCONNECT
STA_RX_SRC_CAP_WAIT
STA_RX_ACCEPT_WAIT
STA_RX_PS_RDY_WAIT
STA_TX_REQ
STA_TX_GOODCRC
STA_VDM
STA_IDLE
```

基本 Sink 协商：

```text
Attach
  -> STA_RX_SRC_CAP_WAIT

收到 Source_Capabilities
  -> USBPD_PDO_Analyse()
  -> USBPD_FIND_5V_PDO()
  -> STA_Req()
  -> 发送 Request
  -> STA_RX_ACCEPT_WAIT

收到 Accept
  -> STA_RX_PS_RDY_WAIT

收到 PS_RDY
  -> Explicit_Contract = 1
  -> STA_IDLE

STA_IDLE 且 Explicit_Contract
  -> 可以处理 VDM
  -> 可以尝试发送 HPD Attention
```

PE 定时器：

```text
USBPD_T_SINK_WAIT_CAP_MS      500ms
USBPD_T_SENDER_RESPONSE_MS     30ms
USBPD_T_PS_TRANSITION_MS      500ms
USBPD_T_SINK_REQUEST_MS       100ms
USBPD_N_HARD_RESET_COUNT        2
```

收到 `Wait` 后启动 `SinkRequestTimer`，在 100ms 内即使再次收到 Source_Cap，也不会立刻重复 Request。

控制消息处理摘要：

```text
Soft_Reset       -> reset protocol layer, Accept, 回 STA_RX_SRC_CAP_WAIT
Accept           -> 只在 STA_RX_ACCEPT_WAIT 有效，否则协议恢复
Reject           -> 只在 STA_RX_ACCEPT_WAIT 有效，否则协议恢复
Wait             -> 只在 STA_RX_ACCEPT_WAIT 有效，启动 SinkRequestTimer
PS_RDY           -> 只在 STA_RX_PS_RDY_WAIT 有效，建立 Explicit Contract
Get_Sink_Cap     -> 回 Sink_Capabilities，当前只有 5V/1A Sink PDO
Get_Status       -> 回 Status Extended Message，当前 payload 全 0
Get_Revision     -> 回 Revision Data Message，当前 revision_vdo = 0x03020000
Get_Sink_Cap_Ext -> Not_Supported
DR_Swap          -> DP Mode active 时 Hard Reset，否则 Reject
PR_Swap          -> Reject
VCONN_Swap       -> Reject
Data_Reset       -> Accept，清 DP/HPD/VL171，然后 Data_Reset_Complete
其他             -> Not_Supported
```

Data Message 处理摘要：

```text
Source_Capabilities
  只在 STA_RX_SRC_CAP_WAIT，或已有显式合约且 STA_IDLE 时接受。
  其他状态视为协议错误恢复。

Vendor Defined Message
  只在 Explicit_Contract 且 STA_IDLE 时进入 STA_VDM。
  其他状态视为协议错误恢复。

Alert
  只打印日志。

Enter_USB / BIST / 其他
  Not_Supported。
```

入站 Header 限制：

- `PDRole` 必须是 1，也就是对端是 DFP/Source 侧数据角色。
- `Ext` 置位的入站 Extended Message 当前统一回 `Not_Supported`。

## PDO / RDO

主要文件：

- `User/USBPD/Inc/pd_pdo.h`
- `User/USBPD/Inc/pd_rdo.h`
- `User/USBPD/Src/usbpd_helper.c`

PDO 解析：

- `USBPD_PDO_Analyse()`：打印收到的 Source PDO，支持 Fixed、Battery、Variable、APDO 日志。
- `USBPD_FIND_5V_PDO()`：从 Source_Capabilities 中找第一个 Fixed 5V PDO。

Request 构造：

- 只请求 Fixed 5V PDO。
- `OperatingCurrent` 和 `MaxOperatingCurrent` 都取 Source 5V PDO 的最大电流。
- 如果 Source PDO 没有 USBCommCapable，则 RDO 设置 `CapabilityMismatch=1`，仍然请求 5V。

## VDM / DP Alt Mode 数据定义

主要文件：

- `User/USBPD/Inc/pd_vdm.h`
  - Structured VDM Header、ID Header VDO、Cert Stat、Product VDO、UFP/DFP VDO 位域。

- `User/USBPD/Inc/pd_dp_alt_mode.h`
  - DP Capabilities VDO、DP Status VDO、DP Configure VDO 位域。

- `User/USBPD/Inc/usbpd_vdm.h`
  - 本项目自己的 Identity 和 DP Alt Mode 配置结构。

- `User/USBPD/Src/usbpd_vdm.c`
  - 本设备的 Identity 和 DP 能力实例。

当前 Identity：

```text
VID         0x1209，占位值
PID         0x0001，占位值
bcdDevice   0x0001
Connector   Type-C receptacle
UFP type    PD USB peripheral
USB speed   Gen2
UFP VDO     version 1.3
```

当前 DP Alt Mode：

```text
SVID              0xFF01
Object Position   1
Port Capability   UFP_D / DP Sink
Signaling         DP
Receptacle        yes
```

lane 模式影响：

- 4-lane 模式：
  - Advertise Pin C | Pin E。
  - Configure 白名单：USB、Pin C、Pin E。

- 2-lane 模式：
  - Advertise Pin C | Pin E | Pin D。
  - Configure 白名单：USB、Pin C、Pin E、Pin D。
  - DP Status 中 `MultiFunctionPreferred=1`。

## VDM 处理流程

主要文件：`User/USBPD/Src/usbpd_vdm_handler.c`

入口：

```text
USBPD_VDM_Handle(rx_buf, tx_buf, last_rx_header)
  解析 Data Object 0 为 VDM Header
  Unstructured VDM -> Not_Supported
  Structured VDM REQ -> USBPD_HandleStructuredVDMRequest()
  Structured VDM ACK/NAK/BUSY -> 记录日志并触发协议恢复
```

SVDM 版本策略：

- 支持 Major 1.0 和 2.x。
- 对端 Major 2.x 且 Minor > 2.1 会被拒绝。
- 本端响应使用协商出的 common 版本。
- 如果对端用 2.1 发起，当前固件响应会 clamp 到本地实现的 2.0。

VDM shape 校验：

- `Reserved5` 必须为 0。
- Discover Identity / Discover SVIDs：
  - `NumDO == 1`
  - `ObjectPosition == 0`
  - `SVID == USBPD_PD_SID`

- Discover Modes：
  - `NumDO == 1`
  - `ObjectPosition == 0`

- Enter Mode / Exit Mode：
  - `NumDO == 1`
  - `ObjectPosition != 0`

- DP Status / DP Configure：
  - `NumDO == 2`
  - `SVID == DP SVID`
  - `ObjectPosition == USBPD_DP_ALT_MODE.object_position`
  - DP Mode 必须 active

支持的 Structured VDM：

```text
Discover Identity
  ACK ID Header + Cert Stat + Product + UFP VDO。
  同时记录 common SVDM version。

Discover SVIDs
  ACK 0xFF01 + 0x0000。

Discover Modes
  只对 DP SVID ACK。
  ACK 后置 DP_Modes_Discovered=1。

Enter Mode
  要求 DP SVID、Object Position=1、已 Discover Modes、当前未 active。
  ACK 成功后置 Mode_Try_Cnt bit7，进入 HPD mode。

Exit Mode
  要求 DP Mode active 且 SVID/Object Position 正确。
  先切 USB、关 HPD，再发 ACK。
  如果 ACK 失败，恢复之前 DP active/HPD/VL171 状态。

Attention
  入站 Attention 只打印日志，不响应。

DP Status Update
  读取对端 Status 日志。
  读取本端 HPD 状态，ACK DP Status VDO。
  记录 HPD baseline，允许后续主动 Attention。

DP Configure
  校验 Configure VDO 必须在白名单中。
  USB Configuration -> 关 HPD，VL171 切 USB。
  DP Configuration -> 按 Pin Assignment 切 VL171，确保 HPD enabled，必要时排队 HPD High。
  ACK 成功后提交 active config。
  ACK 失败则恢复之前 config / HPD 状态。
```

主动 Attention：

```text
USBPD_PE_Run()
  if STA_IDLE && Explicit_Contract && 没有待处理消息
    USBPD_VDM_TrySendAttention()
```

发送条件：

- `Flag.Connected == 1`。
- HPD enabled。
- 已经有有效 HPD baseline，即至少通过 DP Status ACK 或 Attention 记录过一次状态。
- HPD 控制器里有 pending event。
- 10ms 内最多连续发送 2 个 Attention，第三个要等时间间隔。
- Attention 发送成功后才 `USBPD_HPD_CommitEvent()` 出队。

## HPD 控制器

主要文件：

- `User/USBPD/Inc/usbpd_hpd.h`
- `User/USBPD/Src/usbpd_hpd.c`

职责：

- 把 PB14 原始边沿转换为 DP Alt Mode HPD 语义。
- 对 HPD High 做 250us 防抖。
- 区分 IRQ_HPD 和 HPD Low。
- 保存最多两个待发送 IRQ_HPD。
- 只在 USB PD Attention 发送成功后提交/移除事件，避免 TX 失败丢事件。

入口和接口：

```text
USBPD_HPD_EnterMode()
  关闭 EXTI
  enabled = 1
  logical_high = 0
  如果 PB14 当前为 High，启动 high debounce
  清 pending event / baseline
  打开 EXTI

USBPD_HPD_Disable() / USBPD_HPD_Reset()
  关闭 EXTI
  清所有 HPD 状态、pending event、baseline

USBPD_HPD_ReadStatus()
  给 DP Status Update ACK 使用。
  会先检查长 Low，再弹出一个 pending event，否则返回当前状态。

USBPD_HPD_PeekEvent()
  给主动 Attention 使用。
  只窥探事件，不立即出队。
  对长 Low 使用 s_tx_pending_event 暂存，直到 Commit。

USBPD_HPD_CommitEvent()
  Attention 发送成功后调用，真正移除事件。

USBPD_HPD_RecordReported()
  记录已经对 DFP_U 上报过的 HPD baseline。
```

事件优先级：

```text
Low > High > IRQ
```

边沿处理：

```text
下降沿：
  如果 logical_high，开始 low_pending 计时。
  取消 high debounce。

上升沿：
  如果 low_pending：
    250us <= low < 2000us -> IRQ_HPD，最多队列 2 个。
    low >= 2000us        -> HPD Low，清 stale High/IRQ。
  如果当前 logical_high 为 0：
    启动 High debounce。
```

## VL171 控制

主要文件：

- `User/Drivers/Inc/vl171.h`
- `User/Drivers/Src/vl171.c`

职责：

- 记录 Type-C 正反插方向。
- 控制 VL171 `AMSEL / EN / POL`。
- 根据 DP Configure 的 Pin Assignment 切硬件模式。

方向：

- CC1 attach -> `VL171_ORIENTATION_NORMAL`。
- CC2 attach -> `VL171_ORIENTATION_FLIPPED`。
- `POL` 根据方向设置。

模式：

```text
VL171_MODE_USB
  AMSEL low
  USB operation

VL171_MODE_USB_DP_2LANE
  AMSEL low
  2-lane DP + USB3

VL171_MODE_DP_4LANE
  AMSEL high
  4-lane DP
```

Pin Assignment 映射：

```text
Pin C -> VL171_MODE_DP_4LANE
Pin E -> VL171_MODE_DP_4LANE
Pin D -> VL171_MODE_USB_DP_2LANE
```

注意：attach 后默认先切 `VL171_MODE_USB_DP_2LANE`。最终硬件配置以后续 DFP_U 下发的 DP Configure 为准。

## 协议数据结构文件

```text
Core/Inc/ch32l103_usbpd.h
  USBPD 外设寄存器 bit、PD message type、PD state enum、Message_Header、PD_CONTROL。

User/USBPD/Inc/pd_pdo.h
  Source/Sink PDO 和 APDO 位域。

User/USBPD/Inc/pd_rdo.h
  Fixed/Variable、Battery、PPS、AVS RDO 位域。

User/USBPD/Inc/pd_vdm.h
  Structured VDM Header、Identity VDO、Product VDO、UFP/DFP VDO。

User/USBPD/Inc/pd_dp_alt_mode.h
  DP Mode VDO、DP Status VDO、DP Configure VDO。

User/USBPD/Inc/usbpd_helper.h
  小端读取、CC 比较器辅助、状态切换宏、PDO helper 声明。
```

## 常见修改入口

想改 Sink 请求电流：

- 看 `USBPD_PE_SendSinkCapabilities()` in `User/USBPD/Src/usbpd_pe.c`。
- 看 `STA_Req()` 里 RDO 当前如何镜像 Source 5V PDO 电流。

想改支持的 DP pin assignment：

- 看 `USBPD_DP_SetLaneMode()` 和 `USBPD_DP_ALT_MODE` in `User/USBPD/Src/usbpd_vdm.c`。
- 同步确认 `VL171_ApplyDPPinAssignment()` in `User/Drivers/Src/vl171.c`。

想改上电 2-lane / 4-lane 策略：

- 看 `App_SetStartupLaneMode()` in `User/App/main.c`。
- 看 `BoardIO_IsKeyPressed()` in `User/Board/Src/board_io.c`。

想改 HPD 滤波或事件队列：

- 看 `USBPD_HPD_IRQ_MIN_US` / `USBPD_HPD_UNPLUG_MIN_US` in `User/USBPD/Src/usbpd_hpd.c`。
- 看 `USBPD_HPD_CheckHighDebounce()`、`DP_HPD_EdgeCallback()`、`USBPD_HPD_PeekEvent()`。

想改 DP Status VDO：

- 看 `USBPD_BuildDPStatusVDO()` in `User/USBPD/Src/usbpd_vdm_handler.c`。

想改 VDM 合法性限制：

- 看 `USBPD_SVDMRequestHasValidShape()` in `User/USBPD/Src/usbpd_vdm_handler.c`。

想改收到某种 PD 消息后的响应：

- 看 `USBPD_PE_Run()` in `User/USBPD/Src/usbpd_pe.c` 中 `NumDO==0` 和 `NumDO>0` 两个 switch。

想改 attach/detach 判定：

- 看 `USBPD_Phy_Detect_Check()` in `User/USBPD/Src/usbpd_phy.c`。
- CC 判定 helper 在 `USBPD_GetCcCmpFlags()` in `User/USBPD/Src/usbpd_helper.c`。

## 日志定位

上电：

```text
SystemClk:...
PD SNK TEST
DP lane mode: 2-lane
DP lane mode: 4-lane
```

Attach：

```text
CC1 Attached
CC2 Attached
VL171 2-lane DP + USB3 Normal/Flipped
Detached
```

电源协商：

```text
SRC_CAP received
[PDO1] Fixed5V: ...
ACCEPT received
PS_RDY received
```

DP Alt Mode：

```text
Vendor Defined Message received
DP Mode VDO: ...
RX DP Status VDO: ...
TX DP Status VDO: ...
DP Config VDO: ...
```

HPD：

```text
HPD Status: Logical=... GPIO PB14=... IRQ=...
HPD high, send Attention
HPD low, send Attention: low_us=...
HPD IRQ, send Attention: low_us=...
ATTN DP Status VDO: ...
```

恢复/异常：

```text
IF_RX_RESET
PD data role mismatch, enter Error Recovery
NOT_SUPPORTED received
ALERT received
```

## 规范和修复追踪文档

仓库中还有两份协议审查相关文档：

- `USB_PD_R3_2_COMPLIANCE_REVIEW.md`
  - 针对 USB PD R3.2 的合规审查记录。

- `USB_PD_R3_2_FIX_MAP.md`
  - 将审查项整理成修复清单。
  - `[x]` 表示已修复验证。
  - `[~]` 表示部分修复或需复测。
  - `[-]` 表示当前 Type-C to DP 产品不适用、延期，或依赖外部硬件/产品数据。

规范 PDF 在 `Platform/`：

- `Platform/USB_PD_R3.2_V1.2_2026_03_17.pdf`
- `Platform/DisplayPort-Alt-Mode-v2.0_revised_2020.pdf`

## 当前设计边界

这些不是“代码遗漏”，而是当前产品/硬件边界：

- 没有 VBUS-present 输入/API，所以没有真正用 VBUS gate Sink discovery。
- BIST/test mode 没有完整实现，当前运行路径返回 Not_Supported。
- `Get_Sink_Cap_Extended` 没有完整 Sink_Capabilities_Extended payload。
- Identity 中 VID/PID 仍是占位值，需要正式 USB-IF 产品信息后再替换。
- 没有 USB Billboard device 支持。
- 本端是 UFP_U / DP Sink，主要响应 DFP_U 发起的 discovery/configure，不主动发起 DP Configure。
- 运行中切换 2-lane/4-lane 不能由 UFP_U 直接 Configure，只能通过 HPD Attention/Status 让 DFP_U 决定是否重配。

## 一句话总览

```text
main.c
  -> USBPD_Phy_Run()
      -> USBPD_Phy_Detect_Check() 处理 attach/detach
      -> USBPD_PE_Run() 处理 Sink 协商、PD 消息、VDM、HPD Attention

USBPD_IRQHandler()
  -> 立即 GoodCRC
  -> 去重
  -> Flag.Msg_Recvd 交给 PE

usbpd_vdm_handler.c
  -> Discover/Enter/Status/Configure
  -> VL171/HPD 副作用
  -> Attention 发送

usbpd_hpd.c
  -> PB14 边沿
  -> HPD High/Low/IRQ 队列
  -> Status/Attention 事件源
```
