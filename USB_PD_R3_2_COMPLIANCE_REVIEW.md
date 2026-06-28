# USB PD R3.2 Compliance Review Log

Spec: `Platform/USB_PD_R3.2_V1.2_2026_03_17.pdf`

Scope:
- Firmware under `User/USBPD`, plus board/timer code when it affects PD behavior.
- Chapter-by-chapter review against USB PD R3.2, skipping physical/electrical analog requirements except where protocol timing depends on them.
- Each confirmed non-compliance is recorded as soon as it is found.

Progress:
- 2026-06-27: Started from Chapter 1/3/6/7/9 protocol and policy-engine behavior relevant to a Sink + UFP_U implementation.
- 2026-06-27: Continued Chapter 7/8/9 review for Data Reset, role-swap behavior during Modal Operation, VDM mode exit, unmanaged Alternate Mode termination, VDM response timers, and BIST behavior.
- 2026-06-27: Continued Chapter 6/8 review for Structured VDM field validation.
- 2026-06-27: Continued Chapter 7/9 review for SinkWaitCapTimer and HardResetCounter behavior.
- 2026-06-27: Continued Chapter 7/9 review for Source_Capabilities-to-Request response timing.
- 2026-06-27: Continued Chapter 6/8 review for Structured VDM request length validation.
- 2026-06-27: Continued Chapter 7/9 review for Protocol Layer message discard behavior.
- 2026-06-27: Continued Chapter 7/9 review for Protocol Layer reset counter behavior.
- 2026-06-27: Continued Chapter 9 review for Not_Supported receive handling.
- 2026-06-27: Continued Chapter 5/9 review for CC bus Idle gating before packet transmission.
- 2026-06-27: Continued Chapter 6/8 review for Structured VDM Header Object Position validation.
- 2026-06-27: Continued Chapter 8/9 review for received Attention handling.
- 2026-06-27: Continued Chapter 6/8 review for Discover Identity UFP VDO consistency with DP Alt Mode support.
- 2026-06-27: Continued Chapter 7/9 review for Wait response and SinkRequestTimer behavior.
- 2026-06-27: Continued Chapter 7/9 review for Soft Reset recovery after transmission failure or protocol error.
- 2026-06-27: Continued Chapter 7/9 review for Source Alert handling by a Sink.
- 2026-06-27: Continued Chapter 6/8 review for Discover Identity SVID validation.
- 2026-06-27: Continued Chapter 8/9 review for managed Exit Mode return to USB operation.
- 2026-06-27: Continued Chapter 6/9 review for SOP Port Data Role validation.
- 2026-06-27: Continued Chapter 6/8 review for Structured VDM reserved-bit sanitization.
- 2026-06-27: Continued Chapter 7/9 review for role-swap request response handling.
- 2026-06-27: Continued Chapter 9 review for Sink VBUS-present gating during discovery.
- 2026-06-27: Continued Chapter 8/9 review for Alternate Mode entry sequencing and USB operation state.
- 2026-06-27: Continued Chapter 8 review for SVID-specific command handling while no Active Mode exists.
- 2026-06-27: Continued Chapter 7/9 review for UFP Enter_USB responder behavior.
- 2026-06-27: Continued Chapter 7/8 review for Soft Reset scope and Alternate Mode state preservation.
- 2026-06-27: Continued Chapter 7/9 review for VCONN Swap responder behavior.
- 2026-06-27: Continued Chapter 6/8 review for Structured VDM invalid-command NAK header sanitization.
- 2026-06-27: Continued Chapter 7/9 review for unexpected recognized control responses during AMS handling.
- 2026-06-27: Continued Chapter 7/8/9 review for unexpected Structured VDM response handling.
- 2026-06-27: Continued Chapter 9 review for Sink Hard Reset transition-to-default behavior.
- 2026-06-27: Continued Chapter 7/8/9 review for Structured VDM discovery initiator requirements.
- 2026-06-27: Continued Chapter 6/8 review, with DP Alt Mode SVID-specific context, for DP Status/Configure Object Position validation.
- 2026-06-27: Continued Chapter 8 review, with DP Alt Mode SVID-specific context, for DisplayPort Configure return-to-USB handling.
- 2026-06-27: Continued Chapter 8 review, with DP Alt Mode SVID-specific context, for Attention pacing.
- 2026-06-27: Continued Chapter 8 review, with DP Alt Mode SVID-specific context, for DP Capabilities pin-assignment advertisement.
- 2026-06-27: Continued Chapter 6 review for Extended Message classification by the Message Header `Ext` bit.
- 2026-06-27: Continued Chapter 8 review, with DP Alt Mode SVID-specific context, for HPD-to-USB PD event queuing.
- 2026-06-27: Continued Chapter 8 review, with DP Alt Mode SVID-specific context, for mandatory receptacle DP Sink pin assignments.
- 2026-06-27: Continued Chapter 8 review, with DP Alt Mode SVID-specific context, for HPD event queue ordering after HPD_Low.
- 2026-06-27: Continued Chapter 8 review, with DP Alt Mode SVID-specific context, for DisplayPort Status `Enabled` reporting.
- 2026-06-27: Continued Chapter 8 review, with DP Alt Mode SVID-specific context, for initial HPD Status exchange ordering.
- 2026-06-27: Continued Chapter 8 review, with DP Alt Mode SVID-specific context, for USB Billboard behavior when DP Alt Mode entry fails.
- 2026-06-27: Continued Chapter 8 review, with DP Alt Mode SVID-specific context, for HPD re-enablement after returning from USB Configuration to DisplayPort Configuration.
- 2026-06-27: Continued Chapter 8 review, with DP Alt Mode SVID-specific context, for HPD_High debounce before USB PD reporting.
- 2026-06-27: Continued Chapter 7/9 review for repeated Sink Requests after a Source Reject response.
- 2026-06-27: Continued DP Alt Mode HPD review for initial Status exchange debounce behavior.
- 2026-06-27: Continued Chapter 7 review for unexpected recognized non-VDM Data Message handling.
- 2026-06-27: Continued Chapter 7/9 review for Get_Status responder behavior.
- 2026-06-27: Continued DP Alt Mode Section 5 review for DP_SID-specific Status/Configure VDO payload validation.
- 2026-06-27: Continued Chapter 6/8 review, with DP Alt Mode SVID-specific context, for Structured VDM version-field request validation.
- 2026-06-27: Continued Chapter 6/8/9 review for Enter Mode sequencing against the prior Discover Modes result.
- 2026-06-27: Continued Chapter 6/7/9 review for Sink Request construction from malformed Source Capabilities.
- 2026-06-27: Continued Chapter 7/9 review for GoodCRC receive-state ordering under interrupt/main-loop races.
- 2026-06-27: Continued Chapter 8/9 review for Modal Operation state changes before Structured VDM response transmission success.
- 2026-06-27: Continued DP Alt Mode HPD review for event queue consumption before USB PD transmission success.
- 2026-06-27: Continued DP Alt Mode Configure review for mandatory associated DP-only pin assignment handling in multi-function mode.
- 2026-06-27: Continued DP Alt Mode Configure/HPD review for required HPD High Attention after DP Sink configuration.
- 2026-06-27: Continued Chapter 8/9 review for repeated Enter Mode requests while a DP Active Mode is already active.
- 2026-06-27: Continued Chapter 7/9 review for stale pending receive/Request state across Detach.
- 2026-06-27: Continued Chapter 7/9 review for AMS interleaving after a Sink Request during Power Negotiation.
- 2026-06-27: Continued Chapter 6/8 review for Structured VDM reserved-field request handling.
- 2026-06-27: Continued Chapter 7/8/9 review for incoming Structured VDM interleaving during unfinished Power Negotiation.
- 2026-06-27: Continued DP Alt Mode Configure review for mandatory Pin Assignment E handling by a USB-C receptacle DP Sink.
- 2026-06-27: Continued Chapter 8/9 review for Exit Mode state changes before Structured VDM response transmission success.
- 2026-06-27: Continued Chapter 8 review, with DP Alt Mode SVID-specific context, for DisplayPort Configure side effects before response transmission success.
- 2026-06-27: Continued Chapter 6/8 review for Structured VDM Discover command Object Position request validation.

Findings:

## PD-R3.2-001 - Sink sends Hard Reset during normal attach

Spec evidence:
- USB PD R3.2 section 9.2.4.1 says `PE_SNK_Startup` resets the Protocol Layer and then transitions to `PE_SNK_Discovery`.
- Section 9.2.4.2 says the Sink waits for VBUS and then enters `PE_SNK_Wait_for_Capabilities`.
- Section 9.2.4.3 says the Sink starts `SinkWaitCapTimer` and waits for `Source_Capabilities`.
- Hard Reset is an error/reset path in sections 7.1.3 and 9.2.4.8, not the normal attach path.

Code evidence:
- `User/USBPD/Src/usbpd_phy.c:190` sends `USBPD_Phy_TxPacket(NULL, 0, UPD_HARD_RESET, 1)` immediately after attach detection.
- The same attach branch also moves to `STA_SRC_CONNECT` before sending this reset.

Why this is non-compliant:
- A Sink should not issue Hard Reset as part of normal attach/discovery. It should wait for VBUS and Source Capabilities, then send a Request. Sending Hard Reset can unnecessarily reset the Source power/protocol state and violates the Sink startup sequence.

## PD-R3.2-002 - Received Soft_Reset is not answered with Accept

Spec evidence:
- Section 7.7 says the receiver of a `Soft_Reset` shall reset `MessageIDCounter` and `RetryCounter` to 0 before sending the `Accept` response.
- Section 9.2.5.2.2 says `PE_SNK_Soft_Reset` is entered from any state when `Soft_Reset` is received on SOP; on entry the Sink shall reset the SOP Protocol Layer and request the Protocol Layer to send `Accept` on SOP, then transition to `PE_SNK_Wait_for_Capabilities` after `Accept` is sent.

Code evidence:
- `User/USBPD/Src/usbpd_pe.c:151` handles `DEF_TYPE_SOFT_RESET` by calling only `USBPD_PE_Reset()`.
- There is no code path that builds or transmits an `Accept` control message for this received `Soft_Reset`.

Why this is non-compliant:
- The Source will wait for an `Accept` to complete the Soft Reset AMS. This firmware silently resets local state and leaves the required response unsent, so the AMS times out and can escalate to Hard Reset.

## PD-R3.2-003 - Transmitter does not wait for matching GoodCRC or retry before incrementing MessageID

Spec evidence:
- Section 7.31.1 says `CRCReceiveTimer` starts after the last bit of the transmitted Message EOP and stops when the GoodCRC EOP is received; timeout requires retry up to `nRetryCount`.
- Section 7.32.1 says the transmitter retries the same Packet with the same MessageID if matching GoodCRC is not received before `CRCReceiveTimer` expires, and increments `MessageIDCounter` only after receiving a GoodCRC with matching MessageID.
- Table 7.12 defines `nRetryCount = 2`.

Code evidence:
- `User/USBPD/Src/usbpd_pe.c:100-101` sends `Request` and immediately increments `USBPD_Control.Msg_ID`.
- `User/USBPD/Src/usbpd_vdm_handler.c:96-97` sends VDM responses/Attention and immediately increments `USBPD_Control.Msg_ID`.
- `User/USBPD/Src/usbpd_phy.c:18-52` waits only for local `IF_TX_END`; it does not start `CRCReceiveTimer`, wait for a GoodCRC, compare GoodCRC MessageID, or retry.

Why this is non-compliant:
- A transmitted message can be lost or NAKed at the protocol level without being retried. The local MessageID also advances even when the Port Partner never acknowledged that MessageID, breaking the required transmitter state machine.

## PD-R3.2-004 - Receiver does not suppress duplicate Messages by stored MessageID

Spec evidence:
- Section 6.1.2 says MessageID is used to ensure duplicate messages are handled properly, and GoodCRC uses the received MessageID being acknowledged.
- Section 7.32.1 says each port shall maintain a copy of the last MessageID received for each supported SOP* and the receiver shall use MessageID to detect duplicate messages.
- Section 9.1.2.3.4 says if the received MessageID equals the stored MessageID, it is a retry and shall be discarded; otherwise store the new MessageID and pass the message to the Policy Engine.

Code evidence:
- `User/USBPD/Src/usbpd_pe.c:213-222` stores the incoming header in `last_rx_header`, schedules GoodCRC for non-GoodCRC packets, and unconditionally sets `USBPD_Control.Flag.Msg_Recvd = 1`.
- There is no stored last-received MessageID per SOP* and no duplicate discard path before `USBPD_PE_Run()` processes Source Capabilities or VDMs.

Why this is non-compliant:
- If the Port Partner retries a message because it missed this firmware's GoodCRC, the duplicate can be delivered to the Policy Engine again and trigger repeated Request/VDM handling instead of being acknowledged and discarded.

## PD-R3.2-005 - Sink power negotiation does not implement the required Select/Transition/Ready flow

Spec evidence:
- Section 9.2.4.5 says `PE_SNK_Select_Capability` shall request the Protocol Layer to send a Request, initialize and run `SenderResponseTimer`, transition to `PE_SNK_Transition_Sink` on `Accept`, to `PE_SNK_Wait_for_Capabilities` on `Reject`/`Wait` when no Explicit Contract exists, to `PE_SNK_Ready` on `Reject`/`Wait` when an Explicit Contract exists, and to `PE_SNK_Hard_Reset` on `SenderResponseTimer` timeout.
- Section 9.2.4.6 says `PE_SNK_Transition_Sink` shall initialize and run `PSTransitionTimer` and transition to `PE_SNK_Ready` only after `PS_RDY`.
- The glossary defines an Explicit Contract as `Accept` in response to a Sink `Request` followed by `PS_RDY`.

Code evidence:
- `User/USBPD/Src/usbpd_pe.c:100-101` sends `Request` and immediately returns to idle.
- `User/USBPD/Src/usbpd_pe.c:156-168` only prints `ACCEPT`, `REJECT`, and `PS_RDY`; it does not start/stop `SenderResponseTimer`, run `PSTransitionTimer`, track an Explicit Contract, or change to a ready/transition state.

Why this is non-compliant:
- The firmware cannot distinguish a completed contract from a partial or failed Power Negotiation AMS. It also never times out a missing `Accept`/`PS_RDY` and never follows the required `Reject`/`Wait` recovery transitions.

## PD-R3.2-006 - Source_Capabilities is accepted in states where it is a Protocol Error

Spec evidence:
- Section 9.2.4 note 1 says Source Capabilities Messages received in states other than `PE_SNK_Wait_for_Capabilities`, `PE_SNK_Ready`, or `PE_SNK_Get_Source_Cap` constitute a Protocol Error.
- Section 9.2.4.8 also lists a `Source_Capabilities` message received without being requested by `Get_Source_Cap` as a Sink hard reset trigger in EPR-related cases.

Code evidence:
- `User/USBPD/Src/usbpd_pe.c:183-188` treats every received `DEF_TYPE_SRC_CAP` as valid, prints it, switches to `STA_TX_REQ`, and analyzes PDOs.
- The implementation has no `PE_SNK_Wait_for_Capabilities` / `PE_SNK_Ready` / `PE_SNK_Get_Source_Cap` state distinction to reject or reset on unexpected Source Capabilities.

Why this is non-compliant:
- A repeated or unexpected `Source_Capabilities` during another AMS can cause this firmware to send a fresh Request instead of handling the Protocol Error path required by the Sink Policy Engine.

## PD-R3.2-007 - Unsupported, unrecognized, and reserved Messages are ignored instead of Not_Supported

Spec evidence:
- Section 6.3.16 says `Not_Supported` shall be sent by a Port or Cable Plug in response to any Message it does not support or is unable to interpret.
- Tables 6.4, 6.5, and 6.47 mark reserved Control/Data/Extended message types as "receiver Shall respond with Not_Supported Message".
- Section 7.1.1 says an Unrecognized or Unsupported Message received in a Policy Engine ready state causes `Not_Supported` to be generated.
- Section 9.2.7.2.1 says `PE_SNK_Send_Not_Supported` shall request the Protocol Layer to send `Not_Supported`.

Code evidence:
- `User/USBPD/Src/usbpd_pe.c:147-176` handles only a few Control messages and uses `default: break`.
- `User/USBPD/Src/usbpd_pe.c:181-196` handles only `Source_Capabilities` and `Vendor_Defined`, then uses `default: break`.
- `last_rx_header.Message_Header.Ext` is never checked, so Extended Messages and reserved Extended message types are neither parsed nor answered.
- `DEF_TYPE_NOT_SUPPORT` is defined in `Core/Inc/ch32l103_usbpd.h:100`, but there is no transmit path for it.

Why this is non-compliant:
- A compliant Port Partner that sends unsupported control/data/extended messages receives no required response, which can force sender timeouts and incorrect AMS recovery instead of the defined `Not_Supported` path.

## PD-R3.2-008 - Get_Sink_Cap is not answered with Sink_Capabilities

Spec evidence:
- Section 6.3.8 defines `Get_Sink_Cap` as a request for the Port Partner's Sink Capabilities.
- Section 7.18 says the Port shall respond by returning a `Sink_Capabilities` Message.
- Section 9.2.4.10 says `PE_SNK_Give_Sink_Cap` shall request current system capabilities from the DPM and send `Sink_Capabilities` when `Get_Sink_Cap` is received.

Code evidence:
- `DEF_TYPE_GET_SNK_CAP` and `DEF_TYPE_SNK_CAP` exist in `Core/Inc/ch32l103_usbpd.h:92` and `Core/Inc/ch32l103_usbpd.h:115`.
- `User/USBPD/Src/usbpd_pe.c:147-176` has no `DEF_TYPE_GET_SNK_CAP` case and falls through to `default: break`.
- There is no Sink PDO list or transmit path for `Sink_Capabilities`.

Why this is non-compliant:
- A Source that queries Sink requirements receives no response, violating the Get Sink Capabilities AMS and preventing the Source from using Sink capabilities for policy decisions such as capability mismatch or FRS-related checks.

## PD-R3.2-009 - SOP VDMs are processed even when no Explicit Contract is established

Spec evidence:
- Section 8.3 says during Default Contract or Implicit Contract, Ports shall not initiate VDMs, and Ports and Cables shall ignore any VDMs received, except Discover Identity on SOP' for cable discovery.
- Port Partner discovery and Alternate Mode discovery in section 8.7.1 are normal Explicit Contract operations.

Code evidence:
- `User/USBPD/Src/usbpd_pe.c:190-193` dispatches every received SOP `Vendor_Defined` Data Message to `USBPD_VDM_Handle()`.
- Because finding PD-R3.2-005 shows no Explicit Contract state is tracked, this path can respond to SOP VDMs before a contract is actually established.

Why this is non-compliant:
- The firmware can participate in SOP VDM/Alternate Mode discovery during Default or Implicit Contract, where the USB PD spec requires the message to be ignored.

## PD-R3.2-010 - Unsupported Unstructured VDMs are ignored instead of Not_Supported

Spec evidence:
- Section 8.4 says that when a DFP or UFP does not support Unstructured VDMs or does not recognize the VID, it shall respond with a `Not_Supported` Message.
- Section 8.3 only allows ignoring received VDMs before an Explicit Contract; after that, the VDM-specific response rules apply.

Code evidence:
- `User/USBPD/Src/usbpd_vdm_handler.c:377-381` detects `VDMType == Unstructured` and returns without sending anything.
- There is no `Not_Supported` transmit helper as already noted in PD-R3.2-007.

Why this is non-compliant:
- After an Explicit Contract, an Unstructured VDM from a DFP will time out instead of receiving the required `Not_Supported` response from this UFP.

## PD-R3.2-011 - Structured VDM version negotiation is not implemented

Spec evidence:
- Section 8.5.1 says products shall support every Structured VDM Version starting from 1.0.
- On receipt of a higher version than supported, a Responder shall respond using the highest version it supports.
- On receipt of a lower version than supported, a Responder shall respond using the same version it received.
- The common Structured VDM Version discovered via Discover Identity shall continue to be used until Detach, Hard Reset, or Error Recovery.

Code evidence:
- `User/USBPD/Src/usbpd_vdm_handler.c:123-124` forces every Structured VDM response to Major 2.x / Minor 2.0.
- `User/USBPD/Src/usbpd_vdm_handler.c:138-139` forces Attention to Major 2.x / Minor 2.0.
- `USBPD_Control.Flag.VDM_Version` is reset in `User/USBPD/Src/usbpd_pe.c:27` but is not used to negotiate or store the common Structured VDM version.

Why this is non-compliant:
- If the Port Partner sends SVDM 1.0 or another lower supported version, this firmware responds with 2.0 instead of matching the received version. It also never records the discovered common SVDM version for later initiated VDMs such as Attention.

## PD-R3.2-012 - Discover Identity uses placeholder VID/PID instead of valid device identity values

Spec evidence:
- Section 6.1.5 says VID and PID are 16-bit values used by USB PD to identify a device; VIDs are assigned by USB-IF and PIDs are assigned by the vendor.
- Section 6.1.5 also says USBPD messages describing the Device Port shall all respond with the same VID/PID values.
- For USB Devices or Hubs supporting USB Communications, the USB Vendor ID field shall match the VID in the USB Device Descriptor.
- If the vendor does not have a VID, VID fields shall be `FFFFh` and the PID field in the same message shall be `0000h`.
- Section 6.4.12.3.1 says the ID Header VDO USB Vendor ID is the VID assigned to the product vendor by USB-IF.

Code evidence:
- `User/USBPD/Src/usbpd_vdm.c:16-18` defines `.usb_vendor_id = 0x1209u`, `.usb_product_id = 0x0001u`, and `.bcd_device = 0x0001u`, with comments explicitly marking them as placeholders.
- `User/USBPD/Src/usbpd_vdm_handler.c:204` and `User/USBPD/Src/usbpd_vdm_handler.c:210-211` place those values into the Discover Identity ID Header/Product VDO.
- The project does not contain a USB device descriptor showing that VID/PID pair, and the comments say these are not final assigned values.

Why this is non-compliant:
- A Discover Identity ACK exposes device identity fields that must be assigned and consistent. Placeholder identity values are not compliant unless `0x1209/0x0001` are the actual assigned USB VID/PID for this product and match its USB descriptors.

## PD-R3.2-013 - Received Hard Reset is not handled by the Sink Policy Engine

Spec evidence:
- The glossary defines Hard Reset as restoring VBUS to USB Default Operation and resetting the PD communications engine in both Port Partners, restoring default Data Roles and VCONN Source.
- Section 9.2.4.9 says when Hard Reset Signaling is received or transmitted, the Sink Policy Engine shall transition from any state to `PE_SNK_Transition_to_default`.
- On entry to `PE_SNK_Transition_to_default`, the Sink shall indicate to the DPM that it shall transition to default, request a reset of local hardware, request the DPM to turn off power draw, request the DPM to reset the Port Data Role to UFP, and then transition to `PE_SNK_Startup` after reaching the default level.

Code evidence:
- `Core/Inc/ch32l103_usbpd.h:54` defines `IF_RX_RESET`, and `Core/Inc/ch32l103_usbpd.h:186` identifies `PD_RX_SOP1_HRST` as SOP' or Hard Reset received.
- `User/USBPD/Src/usbpd_pe.c:225-230` handles `IF_RX_RESET` only by printing, clearing the flag, and calling `USBPD_Phy_EnterRxMode()`.
- No code resets the PD protocol state, clears the explicit/alternate-mode state, disables HPD/VDM mode as part of Hard Reset, restores default data role, or transitions through a Sink hard-reset/default state.

Why this is non-compliant:
- A Source-issued Hard Reset will not reset the Sink policy/protocol state as required. The firmware can continue with stale MessageID, VDM/HPD, and contract assumptions after the Port Partner has reset the PD relationship.

## PD-R3.2-014 - Sink-initiated Attention does not obey SinkTxOK collision avoidance

Spec evidence:
- Section 9.1.2.2.3.1 says the Sink Protocol Layer enters `PRL_Tx_Snk_Start_of_AMS` when the next Sink message is the start of an AMS.
- Section 9.1.2.2.3.2 says the Sink has the first message in a Sink-initiated AMS ready and waits for Rp to transition to `SinkTxOK` before sending; it may construct the message only when Rp is `SinkTxOK` (except Soft_Reset layer-reset path).
- Section 5.2.2 says the Sink Protocol Layer shall request the PHY Layer's observed Rp value to determine whether it may initiate a transmission, and the PHY shall check CC bus Idle immediately before transmission.

Code evidence:
- `User/USBPD/Src/usbpd_pe.c:202-204` calls `USBPD_VDM_TrySendAttention()` whenever `PD_State == STA_IDLE`.
- `User/USBPD/Src/usbpd_vdm_handler.c:147-184` sends Attention as soon as an HPD event is available.
- `User/USBPD/Src/usbpd_vdm_handler.c:96` and `User/USBPD/Src/usbpd_phy.c:18-52` transmit immediately after a fixed `tInterFrameGap` delay; they do not check current Rp for `SinkTxOK`, do not wait in `PRL_Tx_Snk_Pending`, and do not verify CC bus Idle immediately before transmission.

Why this is non-compliant:
- HPD Attention is a Sink/UFP initiated AMS. If the Source is holding the bus with `SinkTxNG` or CC is not Idle, this firmware can transmit anyway, creating a collision and violating the Sink transmit state machine.

## PD-R3.2-015 - SOP Specification Revision detection is missing

Spec evidence:
- Section 6.1.3 says after Attach a Port discovers the lowest common Specification Revision and shall use it until Detach, Hard Reset, or Error Recovery.
- Section 6.1.3.1 says the Source sends `Source_Capabilities` with its highest supported revision; the Sink's `Request` shall set SpecRev to the highest Sink-supported revision that is equal to or lower than the revision received from the Source; both Ports shall then use the Request's SpecRev for subsequent communications.
- Section 6.1.3 says a GoodCRC sent in response to a Message with SpecRev `01b` shall set its SpecRev field to `01b`.

Code evidence:
- `User/USBPD/Src/usbpd_pe.c:18` unconditionally sets `USBPD_Control.Flag.PD_Version = 1`, meaning PD3.x.
- `User/USBPD/Src/usbpd_pe.c:58-61`, `User/USBPD/Src/usbpd_pe.c:79-82`, and `User/USBPD/Src/usbpd_vdm_handler.c:72-75` derive outgoing SpecRev only from that fixed flag.
- `User/USBPD/Src/usbpd_pe.c:213-222` stores the incoming header but never uses `last_rx_header.Message_Header.SpecRev` to select the negotiated revision.

Why this is non-compliant:
- When attached to a PD2.0 Source, the Sink should send its Request and PD2.0 GoodCRC responses with SpecRev `01b`. This firmware continues to send Rev3.x headers, so it does not perform the required revision negotiation.

## PD-R3.2-016 - Extended/Chunked message handling and ChunkingNotSupportedTimer are absent

Spec evidence:
- Section 6.1.4 introduces Extended Messages and Chunking for PD3.0.
- Section 9.1.2.1 says if a PD Device has no requirement to handle messages requiring more than one chunk, it may omit the Chunking Layer, but shall implement `ChunkingNotSupportedTimer` for compatible operation with partners that support Chunking.
- Section 9.2.7.2.3 says a Sink that receives an unsupported multi-chunk message in `PE_SNK_Ready` shall enter `PE_SNK_Chunk_Received`, initialize/run `ChunkingNotSupportedTimer`, and then send `Not_Supported`.

Code evidence:
- `Core/Inc/ch32l103_usbpd.h:260` defines the Message Header `Ext` bit, but `User/USBPD/Src/usbpd_pe.c:146-199` classifies messages only by `NumDO == 0` versus `NumDO > 0`.
- No code parses the Extended Message Header, Chunked bit, Request Chunk bit, or Chunk Number.
- No `ChunkingNotSupportedTimer` or chunking state exists, and the `Not_Supported` transmit path is also missing (PD-R3.2-007).

Why this is non-compliant:
- A PD3.x partner sending chunked or extended messages will be treated as ordinary control/data traffic or ignored, rather than being handled through the required chunking/error path.

## PD-R3.2-017 - Sink can silently skip the required Request when the offered 5V PDO lacks USB communication capability

Spec evidence:
- Section 7.9.2 says a Request Message shall be sent by a Sink during the Request phase of SPR power negotiation and shall be sent in response to the most recent `Source_Capabilities` Message.
- Section 6.4.2.1.6 says when the Source cannot satisfy the Sink's requirements, the Sink shall make a valid Request from the offered Source Capabilities and set the Capability Mismatch bit.
- Section 9.2.4.5 says `PE_SNK_Select_Capability` shall send a Request from offered Source Capabilities, optionally with Capability Mismatch set.
- Section 6.4.2.1.7 says the RDO `USB Communications Capable` bit describes whether the Sink has USB data lines; it is not a filter that makes an offered PDO invalid.

Code evidence:
- `User/USBPD/Src/usbpd_helper.c:182` only selects a fixed 5V PDO when the Source PDO has `USBCommCapable` set.
- `User/USBPD/Src/usbpd_pe.c:71-101` sends a Request only when `USBPD_FIND_5V_PDO()` returns a nonzero index; otherwise it returns to idle without any Request, Wait, Reject, Not_Supported, Soft Reset, or Hard Reset path.
- `User/USBPD/Src/usbpd_pe.c:94` always sets the Sink RDO `USBCommCapable` bit to 1 and never uses `CapabilityMismatch`.

Why this is non-compliant:
- A valid Source may advertise a 5V Fixed PDO without USB data capability. This firmware then sends no Request at all, instead of making a valid request for available power and indicating mismatch/local needs through the RDO.

## PD-R3.2-018 - GoodCRC response timing is not bounded to tTransmit

Spec evidence:
- Section 7.31.1 says the receiving Protocol Layer shall respond with a GoodCRC Message within `tTransmit`; `tTransmit` is measured from the last bit of the received Message EOP until the first bit of the GoodCRC Preamble is transmitted.
- Table 7.10 lists `tTransmit = 195 us`.
- Section 9.1.2.3.3 says `PRL_Rx_Send_GoodCRC` shall construct a GoodCRC Message and request the PHY Layer to transmit it.

Code evidence:
- `User/USBPD/Src/usbpd_pe.c:213-222` only records the header and switches state to `STA_TX_GOODCRC` from the RX interrupt.
- `User/USBPD/Src/usbpd_pe.c:125-129` sends GoodCRC later when `USBPD_PE_Run()` happens to execute that state.
- `User/USBPD/Src/usbpd_phy.c:18-24` then adds a fixed 25 us delay before every transmit.
- There is no timestamp, deadline, interrupt-level transmit, or timeout check proving the first GoodCRC preamble starts within 195 us of the received EOP.

Why this is non-compliant:
- The minimum inter-frame delay is not enough; the specification also imposes a maximum GoodCRC response time. Any main-loop latency can push the response beyond `tTransmit`, causing the sender's `CRCReceiveTimer` behavior to diverge from the required exchange.

## PD-R3.2-019 - Data_Reset messages are ignored instead of running the required Data Reset state machine

Spec evidence:
- Table 7.6 marks `BIST` and `Hard_Reset` as Required for Port receive applicability, and Section 7.8 defines the Data Reset AMS.
- Section 9.2.6.2.2 says `PE_UDR_Data_Reset_Received` shall be entered from `PE_SRC_Ready` or `PE_SNK_Ready` for a UFP when a `Data_Reset` Message is received.
- On entry to that state, the Policy Engine shall inform the DPM, send an Accept Message, initialize/run `DataResetFailUFPTimer`, and then either turn off VCONN/send `PS_RDY` or wait for `Data_Reset_Complete`.
- Section 7.31.9 defines the Data Reset timers, including `VCONNDischargeTimer`, `tDataReset`, `DataResetFailTimer`, and `DataResetFailUFPTimer`.

Code evidence:
- `Core/Inc/ch32l103_usbpd.h:98-99` defines `DEF_TYPE_DATA_RESET` and `DEF_TYPE_DATA_RESET_CMP`.
- `User/USBPD/Src/usbpd_pe.c:147-176` handles only `Soft_Reset`, `Accept`, `Reject`, `PS_RDY`, and `GoodCRC` among Control Messages.
- There is no `DEF_TYPE_DATA_RESET` or `DEF_TYPE_DATA_RESET_CMP` handler, no Data Reset DPM notification, no `Accept` response, no `PS_RDY` / `Data_Reset_Complete` path, and no Data Reset timers.

Why this is non-compliant:
- As a UFP/DP Sink, this firmware can receive `Data_Reset` from the DFP. It currently only GoodCRCs the packet and then drops it, leaving USB/Alternate Mode state unchanged and never completing the required Data Reset AMS.

## PD-R3.2-020 - DR_Swap during Modal Operation does not trigger the required Hard Reset

Spec evidence:
- Section 8.2 says a `DR_Swap` Message shall not be sent during Modal Operation between Port Partners.
- Section 7.31.10.3 says if a `DR_Swap` Message is received during Modal Operation then a Hard Reset shall be initiated by the recipient, with Hard Reset Signaling generated within `tDRSwapHardReset` of the GoodCRC EOP.
- Section 9.2.20.1.1 / 9.2.20.2.1 says the Policy Engine shall transition to `PE_SRC_Hard_Reset` or `PE_SNK_Hard_Reset` when a `DR_Swap` Message is received and there are one or more Active Modes.

Code evidence:
- `User/USBPD/Src/usbpd_vdm_handler.c:265-267` marks DP Alt Mode active and enables HPD when Enter Mode is ACKed.
- `Core/Inc/ch32l103_usbpd.h:93` defines `DEF_TYPE_DR_SWAP`.
- `User/USBPD/Src/usbpd_pe.c:147-176` has no `DEF_TYPE_DR_SWAP` handler in the Control Message path.
- The only current Hard Reset transmission path is the attach-time Hard Reset in `User/USBPD/Src/usbpd_phy.c:190`; there is no Hard Reset path tied to `DR_Swap` while `Mode_Try_Cnt` indicates Modal Operation.

Why this is non-compliant:
- If the DFP sends `DR_Swap` while DP Alt Mode is active, this firmware will silently ignore the control message after GoodCRC. The spec requires the recipient to force a Hard Reset within `tDRSwapHardReset`.

## PD-R3.2-021 - Detach does not exit Active Modes or return the port to USB operation

Spec evidence:
- Section 8.7.3 says unmanaged Alternate Mode termination is triggered by Data Reset, Hard Reset, Error Recovery, or Detach.
- Upon unmanaged termination, Ports shall exit all Active Modes, and upon either managed or unmanaged termination each Port shall return to USB operation as defined in USB-C.
- Section 7.1.3.2 also says Hard Reset shall cause all Active Modes to be exited by both Port Partners and Cable Plugs.

Code evidence:
- `User/USBPD/Src/usbpd_vdm_handler.c:265-267` sets the DP mode-active bit and enables HPD on Enter Mode.
- `User/USBPD/Src/usbpd_vdm_handler.c:352` applies the DP pin assignment through `VL171_ApplyDPPinAssignment()`.
- On detach, `User/USBPD/Src/usbpd_phy.c:153-158` only clears `Connected`, calls the weak event callback, and switches to `STA_DISCONNECT`.
- `User/USBPD/Src/usbpd_pe.c:116-119` does nothing in `STA_DISCONNECT`.
- `User/App/main.c:35-39` only stops a timer/prints `Detached`; it does not call `USBPD_PE_Reset()`, `USBPD_HPD_Reset()`, clear the active-mode bit, or return the VL171/pins to USB operation.

Why this is non-compliant:
- A cable detach can leave the local DP Alt Mode state, HPD interrupt state, and mux configuration stale. The next attach can start from a non-USB/default modal state instead of from USB operation with no Active Modes.

## PD-R3.2-022 - Exit Mode ACKs invalid or inactive modes instead of NAKing them

Spec evidence:
- Section 6.4.12.7 says the Exit Mode Object Position shall refer to an Alternate Mode from Discover Modes and shall have been used previously in an Enter Mode Command Request for an Active Mode.
- Section 8.6.5 says the Responder shall exit its Active Mode before sending the response Message.
- Section 8.6.5 also says the Responder shall not return BUSY and shall only return NAK to a Request not containing an Active Mode, i.e. an invalid object position.
- Table 8.1 says Exit Mode allowed responses are ACK or NAK, and a Responder shall NAK if it does not recognize the SVID, cannot process the command, or a VDO/parameter is invalid.

Code evidence:
- `User/USBPD/Src/usbpd_vdm_handler.c:270-275` handles every `USBPD_SVDM_CMD_EXIT_MODE` by clearing the DP active bit, disabling HPD, and sending ACK.
- That path does not check the SVID, does not check whether `ObjectPosition` is the active DP mode or `111b` for all modes, does not check whether any mode is active, and does not validate `NumDO == 1`.

Why this is non-compliant:
- A malformed Exit Mode request, an Exit Mode for an unsupported SVID/object position, or an Exit Mode received before Enter Mode will be ACKed as if a valid Active Mode was exited. The spec requires NAK for those invalid/inactive cases.

## PD-R3.2-023 - Structured VDM response timing is not bounded by the required VDM timers

Spec evidence:
- Section 7.31.11.1 says the receiver of a Structured VDM request requiring a response shall respond within `tVDMReceiverResponse`.
- Section 7.31.11.2 says Enter Mode responses shall be sent within `tVDMEnterMode`.
- Section 7.31.11.3 says Exit Mode responses shall be sent within `tVDMExitMode`.
- Table 7.9 lists `tVDMReceiverResponse = 15 ms`, `tVDMEnterMode = 25 ms`, and `tVDMExitMode = 25 ms`.

Code evidence:
- `User/USBPD/Src/usbpd_pe.c:190-193` only switches to `STA_VDM` when a Vendor Defined Message is received.
- `User/USBPD/Src/usbpd_pe.c:106-109` calls `USBPD_VDM_Handle()` later from `USBPD_PE_Run()`.
- `User/USBPD/Src/usbpd_vdm_handler.c:96-97` sends the VDM response from that later main-loop path and increments the MessageID immediately.
- There is no VDM response timestamp, no `VDMResponseTimer`, no `VDMModeEntryTimer`, no `VDMModeExitTimer`, and no deadline check proving the response preamble starts before the required timeout.

Why this is non-compliant:
- Discover/Enter/Exit/DP SVID-specific requests can be delayed by arbitrary main-loop latency. The initiator is allowed to time out according to the VDM timers, but this firmware does not enforce the corresponding responder timing.

## PD-R3.2-024 - BIST messages are required but not implemented

Spec evidence:
- Table 7.6 marks `BIST` as Required for Port transmit and receive applicability.
- Section 9.2.26.4.1 says a Source, Sink, or Cable Plug shall enter `PE_BIST_Carrier_Mode` from `PE_SRC_Ready`, `PE_SNK_Ready`, or `PE_CBL_Ready` when a BIST Message with the BIST Carrier Mode data object is received and VBUS is at vSafe5V.
- Section 9.2.26.4.2 says a Source, Sink, or Cable Plug shall enter `PE_BIST_Test_Mode` when a BIST Message with the BIST Test Data data object is received and VBUS is at vSafe5V.
- Section 7.31.6 defines `tBISTCarrierMode`, `BISTContModeTimer`, and `tBISTSharedTestMode` timing requirements.

Code evidence:
- `Core/Inc/ch32l103_usbpd.h:114` defines `DEF_TYPE_BIST`.
- `User/USBPD/Src/usbpd_pe.c:181-196` handles Data Messages only for `Source_Capabilities` and `Vendor_Defined`.
- No code parses BIST Data Objects, enters BIST Carrier/Test/Shared Capacity Test Mode, runs `BISTContModeTimer`, suppresses non-GoodCRC traffic in BIST Test Data Mode, or returns to default after continuous BIST.

Why this is non-compliant:
- A compliance tester or Port Partner sending BIST will receive only a GoodCRC while the firmware remains in normal operation. Required BIST receive behavior and timing are missing.

## PD-R3.2-025 - Get_Sink_Cap_Extended is not answered with Sink_Capabilities_Extended

Spec evidence:
- Table 7.5 lists `Get_Sink_Cap_Extended` as Recommended for ports that can operate as Source and Required for ports that can operate as Sink; the responder transmits `Sink_Capabilities_Extended`.
- Section 7.19.3 says the Port shall respond by returning a `Sink_Capabilities_Extended` Message.
- Section 7.19.4 says `Sink_Capabilities_Extended` shall be sent in response to a `Get_Sink_Cap_Extended` Message.
- Section 9.2.9.4.1 says the Sink Policy Engine shall transition to `PE_SNK_Give_Sink_Cap_Ext` from `PE_SNK_Ready` when `Get_Sink_Cap_Extended` is received, request present extended Sink capabilities from the DPM, and send `Sink_Capabilities_Extended`.

Code evidence:
- `Core/Inc/ch32l103_usbpd.h:107` defines `DEF_TYPE_GET_SNK_CAP_EX`.
- `User/USBPD/Src/usbpd_pe.c:147-176` has no handler for `DEF_TYPE_GET_SNK_CAP_EX`.
- All outgoing headers in the current USB PD stack set `.Ext = 0` (`User/USBPD/Src/usbpd_pe.c:61`, `User/USBPD/Src/usbpd_pe.c:82`, `User/USBPD/Src/usbpd_vdm_handler.c:75`), and no code constructs a `Sink_Capabilities_Extended` Extended Message.

Why this is non-compliant:
- A Source is allowed to query this Sink's extended Sink capabilities. This firmware GoodCRCs the request and then drops it instead of returning the required Extended Message.

## PD-R3.2-026 - Get_Revision is not answered with a Revision Message

Spec evidence:
- Table 7.5 lists `Get_Revision` responder applicability as Required, with `Revision` transmitted by the responder.
- Section 6.3.24 says `Get_Revision` requests the Revision and Version of the PD Specification that the Port Partner supports.
- Section 6.4.11 defines the `Revision` Message and says it is used to identify the highest PD Specification Revision at which the Port is capable of operating.
- Section 7.25.1 says the Port Partner shall respond by returning a `Revision` Message, and Section 7.25.2 says the `Revision` Message shall be sent in response to `Get_Revision`.
- Section 9.2.16.2.1 says the Policy Engine shall transition to `PE_Give_Revision` from `PE_SRC_Ready`, `PE_SNK_Ready`, or `PE_CBL_Ready` when a `Get_Revision` Message is received, request revision information from the DPM, and send a `Revision` Message.

Code evidence:
- `Core/Inc/ch32l103_usbpd.h:109` defines `DEF_TYPE_GET_REVISION`, and `Core/Inc/ch32l103_usbpd.h:123` defines `DEF_TYPE_REVISION`.
- `User/USBPD/Src/usbpd_pe.c:147-176` has no handler for `DEF_TYPE_GET_REVISION`.
- No code constructs the Revision Message Data Object (RMDO) for USB PD Revision 3.2 Version 1.2, and no state transitions to a Give Revision path exist.

Why this is non-compliant:
- A compliant Port Partner can request the supported PD revision/version. This firmware will silently ignore that request after GoodCRC, so the mandatory Revision AMS cannot complete.

## PD-R3.2-027 - Discover SVIDs ACKs requests whose SVID is not the PD SID

Spec evidence:
- Section 6.4.12.2 defines the Structured VDM Header SVID field and says no value other than a USB-IF assigned SID/VID shall be present; Table 6.33 lists `0xFF00` as the PD SID allocated to USB PD.
- Section 6.4.12.4 says the SVID in the Discover SVIDs Command shall be set to the PD SID by both the Initiator and the Responder for this Command.
- Section 8.5 says a Structured VDM Responder shall ACK only if it recognizes the SVID and is able to process it at the expected time, and shall NAK if it does not recognize the SVID or a VDO/parameter is invalid.
- Section 8.5 also says the ACK, NAK, or BUSY response shall contain the same SVID as the Command Request.

Code evidence:
- `User/USBPD/Src/usbpd_vdm_handler.c:225-232` handles every `USBPD_SVDM_CMD_DISCOVER_SVIDS` request by returning an ACK containing the DP SVID list, without checking that the incoming `vdm_header->Bit.SVID` is the PD SID.
- `User/USBPD/Src/usbpd_vdm_handler.c:118-124` replies by modifying the received VDM header in place, so a malformed Discover SVIDs request using an arbitrary incoming SVID is ACKed with that same arbitrary SVID.

Why this is non-compliant:
- Discover SVIDs is a PD SID command. A request using any other SVID is not a valid Discover SVIDs command for this Responder and should not be ACKed as a successful SVID discovery response.

## PD-R3.2-028 - SinkWaitCapTimer and HardResetCounter are not implemented for missing Source_Capabilities

Spec evidence:
- Section 9.2.4.3 says that on entry to `PE_SNK_Wait_for_Capabilities`, the Sink Policy Engine shall initialize and start `SinkWaitCapTimer`.
- Section 7.31.3.2 defines `SinkWaitCapTimer` using `tTypeCSinkWaitCap`; Table 7.9 lists `tTypeCSinkWaitCap = 310 ms / 465 ms / 620 ms`.
- Section 7.32.6 says a Sink shall use `SinkWaitCapTimer` to trigger the resending of `Source_Capabilities` by a Source that stopped sending them, and any attached Sink that does not detect `Source_Capabilities` shall issue Hard Reset Signaling when `SinkWaitCapTimer` times out.
- Section 9.2.4.8 says `PE_SNK_Hard_Reset` increments `HardResetCounter`, and if `SinkWaitCapTimer` times out while `HardResetCounter` is greater than `nHardResetCount`, the Sink shall assume the Source is non-responsive; Table 7.11 sets `nHardResetCount = 2`.

Code evidence:
- `User/USBPD/Src/usbpd_pe.c:32-46` implements `STA_Connect()` with a generic `PD_Comm_Timer > 999` path and `Err_Op_Cnt > 5`, not `SinkWaitCapTimer` at the required `tTypeCSinkWaitCap` values and not `HardResetCounter` with `nHardResetCount`.
- `User/USBPD/Src/usbpd_phy.c:188-191` enters `STA_SRC_CONNECT` and immediately sends Hard Reset on attach instead of entering `PE_SNK_Wait_for_Capabilities` and starting `SinkWaitCapTimer`.
- `User/USBPD/Src/usbpd_pe.c:183-188` reacts only when `Source_Capabilities` is received; there is no state that starts/stops `SinkWaitCapTimer`, issues Hard Reset on that timer expiry, or declares the Source non-responsive after the required counter limit.

Why this is non-compliant:
- If a PD Source stops sending or never sends `Source_Capabilities`, this Sink does not follow the required timer/counter behavior. Its timeout is the wrong duration, uses the wrong counter semantics, and is bypassed by an immediate attach Hard Reset.

## PD-R3.2-029 - Request transmission after Source_Capabilities is not bounded by tSenderResponse

Spec evidence:
- Section 9.2.3.3 says that once a `Source_Capabilities` Message has been received and acknowledged by a GoodCRC Message, the Sink is required to then send a `Request` Message within `tSenderResponse`.
- Section 7.31.2 says `SenderResponseTimer` ensures that a Message requesting a response is responded to within the bounded time of `tSenderResponse`.
- Table 7.9 lists `tSenderResponse = 27 ms minimum / 50 ms maximum`.

Code evidence:
- `User/USBPD/Src/usbpd_pe.c:183-188` handles `Source_Capabilities` by setting `STA_TX_REQ` and then running `USBPD_PDO_Analyse(pe_rx_buf)`.
- `User/USBPD/Src/usbpd_pe.c:67-105` sends the `Request` later from `STA_Req()`, which runs only when the main loop subsequently executes the `STA_TX_REQ` state.
- There is no timestamp taken at the GoodCRC EOP, no `SenderResponseTimer`, and no deadline check ensuring that the first bit of the `Request` preamble is transmitted within `tSenderResponse`.

Why this is non-compliant:
- A busy main loop, logging, PDO analysis, or interrupt latency can push the `Request` outside the Source's response window. The firmware has no mechanism to prove or enforce the required Source_Capabilities-to-Request timing.

## PD-R3.2-030 - Structured VDM requests with invalid NumDO are ACKed instead of NAKed

Spec evidence:
- Section 6.4.12.4 says the Number of Data Objects field in a Discover SVIDs Command Request shall be set to 1 because the request shall not contain any VDOs.
- Section 6.4.12.5 says the Number of Data Objects field in a Discover Modes Command Request shall be set to 1 because the request shall not contain any VDOs.
- Section 6.4.12.6 says the Number of Data Objects field in an Enter Mode Command Request shall be set to either 1 or 2 because the request shall not contain more than one VDO.
- Section 6.4.12.7 says the Number of Data Objects field in both Exit Mode Command Request and response shall be set to 1 because Exit Mode shall not contain any VDOs.
- Section 8.5 says a Structured VDM Responder shall NAK when a VDO in the Command Request contains an invalid field or parameter.

Code evidence:
- `User/USBPD/Src/usbpd_vdm_handler.c:189` receives `last_header`, but the standard SVDM request handlers do not consistently use it for request length validation.
- `User/USBPD/Src/usbpd_vdm_handler.c:225-232` ACKs Discover SVIDs without checking `last_header->Message_Header.NumDO == 1`.
- `User/USBPD/Src/usbpd_vdm_handler.c:235-250` ACKs Discover Modes for the DP SVID without checking `NumDO == 1`.
- `User/USBPD/Src/usbpd_vdm_handler.c:254-267` ACKs Enter Mode for the DP SVID/object position without checking that `NumDO` is 1 or 2.
- `User/USBPD/Src/usbpd_vdm_handler.c:270-275` ACKs Exit Mode without checking that `NumDO == 1`.

Why this is non-compliant:
- Malformed Structured VDM requests carrying extra VDOs, or otherwise using an invalid object count, can be acknowledged as successful. The responder should reject these invalid command parameters rather than advancing discovery or mode state.

## PD-R3.2-031 - Incoming SOP messages do not drive the required PRL_Tx_Discard_Message behavior

Spec evidence:
- Section 7.3 says that on receiving a Message on SOP, the Protocol Layer shall discard any pending SOP* Messages; Table 7.3 lists a pending SOP message plus a received SOP message as discarding the outgoing message.
- Section 9.1.2.2.1 says Protocol Layer message transmission shall enter `PRL_Tx_Discard_Message` whenever Protocol Layer message reception receives an incoming Message.
- The same section says that on entry to `PRL_Tx_Discard_Message`, if a Message is queued awaiting transmission, the Protocol Layer shall discard the Message according to Section 5.2.2 and increment `MessageIDCounter`.

Code evidence:
- `User/USBPD/Src/usbpd_pe.c:183-193` can leave an outgoing message pending in a state such as `STA_TX_REQ` or `STA_VDM` after receiving `Source_Capabilities` or a VDM.
- `User/USBPD/Src/usbpd_pe.c:211-221` handles a new received SOP packet by switching directly to `STA_TX_GOODCRC` and setting `Msg_Recvd`; it does not check whether a message is queued/pending for transmission.
- `User/USBPD/Inc/usbpd_helper.h:55-58` shows `SWITCH_PD_STATE()` only overwrites `PD_State_Last` and `PD_State`; it does not discard a queued message or increment `Msg_ID`.
- The only `Msg_ID` increments in this stack occur after actual transmit paths (`User/USBPD/Src/usbpd_pe.c:101`, `User/USBPD/Src/usbpd_vdm_handler.c:97`), not when a pending outgoing message is discarded by an incoming SOP message.

Why this is non-compliant:
- If a `Request`, VDM response, or other outgoing SOP message is pending and a new SOP message arrives first, the firmware may silently overwrite the pending transmit state without performing the mandated Protocol Layer discard action or MessageID update.

## PD-R3.2-032 - Protocol Layer reset does not reset MessageIDCounter or stored MessageID

Spec evidence:
- Section 9.1.2.2.1.3 says `PRL_Tx_Layer_Reset_for_Transmit` shall reset `MessageIDCounter` when sending a Soft Reset and reset the stored MessageID through the receive state machine.
- Section 9.1.2.3.2 says `PRL_Rx_Layer_Reset_for_Receive`, entered when a Soft_Reset Message is received, shall reset `MessageIDCounter` and clear the stored MessageID.
- Section 9.1.2.4 says `PRL_HR_Reset_Layer`, entered on Hard Reset signaling or request, shall reset `MessageIDCounter` and reset the Protocol Layer transmission and reception state machines.
- Section 9.2.4.1 says Sink startup after power-up or Hard Reset shall reset the Protocol Layer, and notes that this resets `MessageIDCounter` and stored MessageID.

Code evidence:
- `User/USBPD/Src/usbpd_pe.c:19-30` implements `USBPD_PE_Reset()` but does not reset `USBPD_Control.Msg_ID`, does not reset a retry counter, and cannot clear a stored received MessageID because no stored received MessageID is maintained.
- `User/USBPD/Src/usbpd_pe.c:151-154` handles a received `Soft_Reset` by calling only `USBPD_PE_Reset()`.
- `User/USBPD/Src/usbpd_pe.c:227-232` handles `IF_RX_RESET` by re-entering RX mode only; it does not run a Protocol Layer hard-reset state or reset message counters.

Why this is non-compliant:
- After Soft Reset, Hard Reset, or Sink startup, subsequent transmitted messages can continue with the old `Msg_ID`, and duplicate-message receive state cannot be cleared correctly. This violates the Protocol Layer reset semantics required for resynchronizing the Port Partners.

## PD-R3.2-033 - Received Not_Supported is ignored instead of informing the DPM

Spec evidence:
- Section 9.2.7.2.2 says `PE_SNK_Not_Supported_Received` shall be entered from `PE_SNK_Ready` when a `Not_Supported` Message is received.
- On entry to that state, the Sink Policy Engine shall inform the Device Policy Manager, then transition back to the previous `PE_SNK_Ready` state when the DPM has been informed.

Code evidence:
- `Core/Inc/ch32l103_usbpd.h:100` defines `DEF_TYPE_NOT_SUPPORT`.
- `User/USBPD/Src/usbpd_pe.c:147-176` handles received Control Messages but has no case for `DEF_TYPE_NOT_SUPPORT`; the `default` path drops it.
- There is no DPM notification path or `PE_SNK_Not_Supported_Received` equivalent state anywhere in `User/USBPD`.

Why this is non-compliant:
- If the Port Partner rejects an AMS or command with `Not_Supported`, this firmware silently loses that outcome. The Policy Engine cannot apply the required state-machine result or inform local policy.

## PD-R3.2-034 - Packet transmission does not check CC bus Idle immediately before transmit

Spec evidence:
- Section 5.2.2 says the PHY Layer shall monitor the channel for data transmission and only initiate transmissions when the CC bus is Idle.
- Section 5.2.2 also says the CC bus Idle condition shall be checked immediately prior to transmission.
- The same section says transmission shall only start if CC bus Idle is present, and if transmission cannot be initiated because CC is not Idle, the Packet shall be discarded and the PHY Layer shall signal to the Protocol Layer as soon as CC becomes Idle that the Message has been discarded.
- Section 9.1.2.2.1.5 says the Protocol Layer transitions to retry handling when the PHY indicates a Message was discarded due to the channel being busy and is now Idle.

Code evidence:
- `User/USBPD/Src/usbpd_phy.c:18-47` implements the common `USBPD_Phy_TxPacket()` path by waiting a fixed 25 us, clearing/configuring the USBPD peripheral, and starting BMC transmission.
- That path does not sample the CC bus for Idle immediately before setting `BMC_START`, does not discard the packet when the bus is busy, and does not signal a bus-idle discard indication back to the Protocol Layer.
- `Core/Inc/ch32l103_usbpd.h:295` defines `PD_BusIdle_Timer`, but it is not used in any transmission path.

Why this is non-compliant:
- Any PD packet, including `GoodCRC`, `Request`, VDM responses, and Hard Reset signaling, can be started while the CC bus is not Idle. The protocol layer also cannot retry or discard according to the required busy-channel state transitions.

## PD-R3.2-035 - Discover VDM responses can transmit an invalid Object Position field

Spec evidence:
- Table 6.33 defines the Structured VDM Header Object Position field.
- For Command values 0 through 3 and 7 through 15, Table 6.33 says Object Position `000b` shall be used; values `001b` through `111b` are invalid.
- Discover Identity, Discover SVIDs, and Discover Modes are Command values 1, 2, and 3 respectively.

Code evidence:
- `User/USBPD/Src/usbpd_vdm_handler.c:118-125` constructs a Structured VDM response by modifying the received VDM header in place, changing only `CommandType` and Structured VDM version fields before sending.
- `User/USBPD/Src/usbpd_vdm_handler.c:195-250` ACKs Discover Identity, Discover SVIDs, and Discover Modes without clearing `vdm_header->Bit.ObjectPosition` to zero.
- Therefore a Discover request received with Object Position `001b` through `111b` can produce a Discover ACK/NAK response that repeats that invalid Object Position value.

Why this is non-compliant:
- Even if the Responder ignores the invalid Object Position in the request, its transmitted Discover response is itself a Structured VDM with Command 1, 2, or 3 and must use Object Position `000b`.

## PD-R3.2-036 - Received Structured VDM Attention is ignored instead of informing the DPM

Spec evidence:
- Section 6.4.12.8 says the Attention Command may be used by the Initiator to notify the Responder that it requires service, and Attention has no response Message.
- Section 9.2.23.4 defines `PE_RCV_VDM_Attention_Request`; on entry, the Policy Engine shall inform the Device Policy Manager of the Attention Command request.
- The same state transitions back to `PE_SRC_Ready` or `PE_SNK_Ready` when the DPM has been informed.

Code evidence:
- `User/USBPD/Src/usbpd_vdm_handler.c:278-286` handles incoming `USBPD_SVDM_CMD_ATTENTION` by doing nothing and breaking out of the switch.
- There is no DPM notification or equivalent state transition for a received Attention request.

Why this is non-compliant:
- Although no VDM response is required, the received Attention event is still part of the Structured VDM state machine. Silently dropping it prevents local policy from reacting to a Port Partner's service request.

## PD-R3.2-037 - Discover Identity UFP VDO does not advertise the supported DP signal-reconfiguration mode

Spec evidence:
- Table 6.34 says the ID Header VDO Modal Operation Supported bit shall indicate whether the UFP-capable product supports Modes.
- Table 6.40 defines UFP VDO bit 4 as `Non-[TBT3] Signal Reconfig. Alternate Mode Support`, indicating support for Alternate Modes that reconfigure the USB-C connector signals except TBT3.
- DisplayPort Alternate Mode reconfigures USB-C connector signals, so a UFP that advertises DP Alt Mode support must make the UFP VDO consistent with that support.

Code evidence:
- `User/USBPD/Src/usbpd_vdm_handler.c:206` sets `id_header.Bit.ModalOperationSupported = 1u`.
- `User/USBPD/Src/usbpd_vdm.c:32-49` defines and advertises the DisplayPort SVID and DP Mode capabilities.
- `User/USBPD/Inc/pd_vdm.h:205-213` defines `USBPD_VDO_UFP` with bits 10..3 collapsed into `Reserved10_3`, so the code has no field for bit 4 `Non-[TBT3] Signal Reconfig. Alternate Mode Support`.
- `User/USBPD/Src/usbpd_vdm_handler.c:213-216` fills only USB speed/capability and UFP VDO version fields; bit 4 remains zero in every Discover Identity ACK.

Why this is non-compliant:
- The Discover Identity response says the product supports Modal Operation and later advertises DP Alt Mode, but its UFP VDO simultaneously reports that it does not support non-TBT signal-reconfiguration Alternate Modes. The identity data is internally inconsistent with the advertised DP capability.

## PD-R3.2-038 - Wait responses to Request are ignored and SinkRequestTimer is absent

Spec evidence:
- Section 7.9.2.2 says that after receiving a `Wait` Message in response to a `Request`, the Sink shall ensure that at least `tSinkRequest` has elapsed before sending another `Request`.
- Section 7.31.4.1 says `SinkRequestTimer` shall be started when the EOP of a `Wait` Message has been received, shall be stopped if any other Message is received or during Hard Reset, and the Sink shall wait at least `tSinkRequest` before sending a new `Request`.
- Table 7.9 lists `tSinkRequest = 100 ms`.
- Section 9.2.4.5 says `PE_SNK_Select_Capability` transitions to `PE_SNK_Wait_for_Capabilities` when there is no Explicit Contract and a `Wait` Message is received, or to `PE_SNK_Ready` when an Explicit Contract exists and a `Wait` Message is received.

Code evidence:
- `Core/Inc/ch32l103_usbpd.h:96` defines `DEF_TYPE_WAIT`.
- `User/USBPD/Src/usbpd_pe.c:147-176` has no `DEF_TYPE_WAIT` case in the received Control Message switch, so received `Wait` Messages fall through `default`.
- There is no `SinkRequestTimer` state variable or tSinkRequest timing logic in `User/USBPD`.

Why this is non-compliant:
- A Source is allowed to respond to a Sink `Request` with `Wait`. This firmware drops that response and cannot enforce the required minimum delay before a follow-up `Request` or perform the required Sink PE transition.

## PD-R3.2-039 - Transmission failure recovery does not send the required Soft_Reset

Spec evidence:
- Section 7.31.8.1 says failure to see a GoodCRC response within `tReceive` after `nRetryCount` retries while the Port Pair is connected shall cause the Source or Sink to send a `Soft_Reset`, and that transmission shall complete within `tSoftReset` of `CRCReceiveTimer` expiring.
- Section 7.31.8.2 says when a Protocol Error causes a Source or Sink to send `Soft_Reset`, the Soft_Reset transmission shall complete within `tProtErrSoftReset` of the EOP of the GoodCRC sent in response to the offending Message.
- Section 7.32.4 says the retry counter is used for transmission failure, and if the `nRetryCount` retry fails the link shall be reset using the Soft Reset mechanism.
- Section 9.2.5.2.1 says `PE_SNK_Send_Soft_Reset` shall be entered from any state when a Protocol Error on SOP is detected during an AMS or when a Message has not been sent after retries. On entry, the Sink shall request SOP Protocol Layer Soft Reset, send `Soft_Reset` on SOP, and initialize and run `SenderResponseTimer`.
- The same state transitions to `PE_SNK_Hard_Reset` on `SenderResponseTimer` timeout or Protocol Layer transmission error.

Code evidence:
- `Core/Inc/ch32l103_usbpd.h:97` defines `DEF_TYPE_SOFT_RESET`, and `Core/Inc/ch32l103_usbpd.h:239` declares `STA_TX_SOFTRST`, but there is no code path that constructs and transmits an outgoing Soft_Reset control message.
- `User/USBPD/Src/usbpd_phy.c:18-60` implements `USBPD_Phy_TxPacket()` as a synchronous or interrupt-driven PHY send and never starts a `CRCReceiveTimer`, retries the same packet with the same MessageID, or reports a Protocol Layer transmission error after retry exhaustion.
- `User/USBPD/Src/usbpd_phy.c:50-60` simply times out the synchronous poll, clears `IF_TX_END`, disables CC low-voltage output, and re-enters RX mode; it does not notify the Policy Engine to enter `PE_SNK_Send_Soft_Reset`.
- `User/USBPD/Src/usbpd_pe.c:69-102` sends `Request` directly and increments `Msg_ID`, with no retry-exhaustion branch to send `Soft_Reset`.
- `User/USBPD/Src/usbpd_pe.c:147-176` handles only received control messages; the `DEF_TYPE_SOFT_RESET` case resets local PE state but does not implement the Sink-initiated Soft Reset recovery state, `SenderResponseTimer`, or fallback to Hard Reset.

Why this is non-compliant:
- After a failed `Request`, VDM, or other SOP transmission, this Sink can return to idle/RX without performing the mandatory Soft Reset recovery. Protocol errors that require a timed Soft_Reset also have no implementation, so the Port Partners can remain desynchronized instead of following the required Soft Reset then Hard Reset recovery path.

## PD-R3.2-040 - Received Alert messages are ignored instead of informing the DPM

Spec evidence:
- Section 6.4.5 says the `Alert` Message allows Port Partners to inform each other when there is a status change event.
- Section 7.14 says the `Alert` Message is used when the Source or Sink detects a status change; Section 7.14.1 says a `Get_Status` Message should be sent in response to a non-Battery status change to get details of the change.
- Section 9.2.8.2 defines the Sink Port Source Alert state diagram. `PE_SNK_Source_Alert_Received` shall be entered from `PE_SNK_Ready` when an `Alert` Message is received.
- On entry to `PE_SNK_Source_Alert_Received`, the Policy Engine shall inform the Device Policy Manager of the details of the Source alert, then either transition to `PE_Get_Status` if the DPM requests status or back to `PE_SNK_Ready` if it does not.

Code evidence:
- `Core/Inc/ch32l103_usbpd.h:117` defines `DEF_TYPE_ALERT`.
- `User/USBPD/Src/usbpd_pe.c:179-197` handles received Data Messages but only has cases for `DEF_TYPE_SRC_CAP` and `DEF_TYPE_VENDOR_DEFINED`; an `Alert` Data Message falls through `default` and is dropped after GoodCRC.
- There is no DPM notification path, alert detail storage, or `PE_SNK_Source_Alert_Received` / `PE_Get_Status` equivalent state in `User/USBPD`.

Why this is non-compliant:
- A Source can legally report status changes with `Alert`. This Sink acknowledges the packet at the Protocol Layer but loses the event at the Policy Engine, so local policy cannot evaluate the alert or request status details as required.

## PD-R3.2-041 - Discover Identity ACKs can use an unrecognized SVID instead of the PD SID

Spec evidence:
- Table 6.33 defines the Structured VDM Header SVID field as a USB SID or USB-IF assigned VID and lists `0xFF00` as the PD SID allocated to this specification.
- Figure 6.5, Discover Identity Response Format, shows the Discover Identity ACK VDM Header with `SVID = PD`.
- Section 8.5 says a Responder that supports Structured VDMs shall NAK a Structured VDM with an SVID that it does not recognize.
- Section 8.6 says the Responder shall NAK when it does not recognize the SVID or when a VDO in the Command Request contains an invalid field or parameter.

Code evidence:
- `User/USBPD/Src/usbpd_vdm_handler.c:373-377` copies the received VDM Header from `rx_buf` into `vdm_header`.
- `User/USBPD/Src/usbpd_vdm_handler.c:195-222` handles `USBPD_SVDM_CMD_DISCOVER_IDENTITY` without checking `vdm_header->Bit.SVID`.
- `User/USBPD/Src/usbpd_vdm_handler.c:118-125` changes only `CommandType` and Structured VDM version fields before transmitting the response, so the ACK echoes whatever SVID was present in the request.

Why this is non-compliant:
- A malformed Discover Identity request with an SVID other than the PD SID can produce a Discover Identity ACK that is itself addressed with the wrong SVID. The responder should reject an unrecognized SVID rather than returning identity data under that SVID.

## PD-R3.2-042 - Exit Mode ACK is sent before returning the port to USB operation

Spec evidence:
- Section 6.4.12.7 says the `Exit Mode` Command commands a Responder to exit its Active Mode and return to normal USB operation.
- Section 8.6.5 says the Responder shall exit its Active Mode before sending the response Message, and Figure 8.3 shows the transition from Active Mode through USB Safe State to USB operation.
- Section 8.7.3 says that upon either managed or unmanaged Alternate Mode termination, each Port shall return to USB operation as defined in USB-C.
- Section 9.2.25.2 says the UFP Policy Engine shall request the DPM to exit the requested Mode, and only transition to the Exit Mode ACK state when the DPM indicates that the Mode has been exited. The state diagram note says the UFP is required to be in USB operation or USB Safe State at that point.

Code evidence:
- `User/USBPD/Src/usbpd_vdm_handler.c:348-352` applies a non-USB DP configuration by calling `VL171_ApplyDPPinAssignment(config_vdo)` when `DP Configure` selects a DP configuration.
- `User/Drivers/Src/vl171.c:89-103` maps DP pin assignments C/E to `VL171_MODE_DP_4LANE` and pin assignment D to `VL171_MODE_USB_DP_2LANE`.
- `User/USBPD/Src/usbpd_vdm_handler.c:270-275` handles `Exit Mode` by only clearing the active-mode bit and disabling HPD before immediately sending ACK; it does not request a DPM mode exit or reconfigure VL171 back to USB operation/USB Safe State before the ACK.
- `User/Drivers/Inc/vl171.h:13-21` exposes only `VL171_MODE_USB_DP_2LANE`, `VL171_MODE_DP_4LANE`, and DP pin-assignment application. There is no USB-only/default restore API used by the managed Exit Mode path.
- `User/App/main.c:22-30` applies `VL171_MODE_USB_DP_2LANE` on attach/orientation detection, but there is no corresponding call in the Exit Mode path. If the port was configured for 4-lane DP, it can remain in that mux state after the Exit Mode ACK.

Why this is non-compliant:
- A valid managed `Exit Mode` can be acknowledged while the local connector/mux state still reflects the prior DP Alternate Mode. The spec requires the UFP to have exited the Mode and be in USB operation or USB Safe State before sending the ACK, with a return to USB operation after the Alternate Mode exits.

## PD-R3.2-043 - SOP Port Data Role mismatches do not enter USB Type-C Error Recovery

Spec evidence:
- Table 6.2 defines the SOP Message Header `Port Data Role` field as the present Data Role of the Port sending the Message.
- Table 6.2 says that at Attachment or Hard Reset, this field is set to 0 for the Port presenting Rd and to 1 for the Port presenting Rp.
- Table 6.2 says that if a USB Type-C Port receives a Message with the `Port Data Role` field set to the same Data Role as its current Data Role, except for the `GoodCRC` Message, USB Type-C Error Recovery actions shall be performed.
- The same table explicitly says the `Port Power Role` field shall not be verified, so this finding is limited to the required Data Role check.

Code evidence:
- `Core/Inc/ch32l103_usbpd.h:254-257` defines the received Message Header `PDRole`, `SpecRev`, and `PRRole` fields, and `Core/Inc/ch32l103_usbpd.h:273-274` stores the local Data Role/Power Role flags.
- `User/USBPD/Src/usbpd_pe.c:24-25` resets this Sink/UFP implementation to `PR_Role = 0` and `PD_Role = 0`.
- `User/USBPD/Src/usbpd_pe.c:215-222` stores `last_rx_header` and suppresses only received `GoodCRC` from triggering a GoodCRC response; it does not compare `last_rx_header.Message_Header.PDRole` with `USBPD_Control.Flag.PD_Role`.
- `User/USBPD/Src/usbpd_pe.c:147-197` processes the received message by type after GoodCRC, with no branch that enters USB Type-C Error Recovery on a Data Role mismatch.

Why this is non-compliant:
- If this UFP receives a non-GoodCRC SOP message whose sender also claims UFP Data Role, the firmware can acknowledge and process it as normal. The required behavior is to perform USB Type-C Error Recovery because both ends are claiming the same Data Role.

## PD-R3.2-044 - Structured VDM responses can echo a nonzero reserved bit

Spec evidence:
- The specification glossary defines Reserved bits, bytes, words, or fields as set to zero by the sender and ignored by the receiver.
- Table 6.33 defines Structured VDM Header bit 5 as `Reserved`.
- Table 6.33 also marks the Structured VDM Header fields as static where applicable, so a transmitted Structured VDM Header must not set this reserved bit.

Code evidence:
- `User/USBPD/Src/usbpd_vdm_handler.c:373-377` copies the received VDM Header directly from `rx_buf` into `vdm_header`.
- `User/USBPD/Src/usbpd_vdm_handler.c:118-125` prepares every Structured VDM response by changing only `CommandType` and Structured VDM version fields.
- `User/USBPD/Src/usbpd_vdm_handler.c:101-114` then transmits `vdm_header->Raw` as Data Object 0 of the response.
- `User/USBPD/Inc/pd_vdm.h:147` defines `Reserved5`, but no response path clears `vdm_header->Bit.Reserved5` before transmit.

Why this is non-compliant:
- A malformed Structured VDM request with bit 5 set can cause the firmware to send an ACK or NAK whose Structured VDM Header also has bit 5 set. Reserved fields are ignored by receivers, but senders are still required to transmit them as zero.

## PD-R3.2-045 - Unsupported or unevaluated role-swap requests are silently ignored

Spec evidence:
- Table 7.4 lists Power Role Swap as required for DRP and unsupported by Source-only/Sink-only Ports. It also lists Data Role Swap as required for DRD and unsupported otherwise.
- Table 7.4 also lists the `Unsupported Sequence` response as required, with `Not_Supported` sent by the responder to an initiating message.
- Sections 7.10 and 7.12.1 say that when the role-swap AMS is supported, the recipient of `PR_Swap` or `DR_Swap` shall respond with `Accept`, `Wait`, or `Reject`.
- Sections 9.2.20.2 and 9.2.20.4 define the DRD/DRP evaluation paths that send `Accept`, `Reject`, or `Wait` when those role-swap AMSs are supported.

Code evidence:
- `Core/Inc/ch32l103_usbpd.h:93-94` defines `DEF_TYPE_DR_SWAP` and `DEF_TYPE_PR_SWAP`, and the state enum declares role-swap states such as `STA_TX_DR_SWAP`, `STA_RX_DR_SWAP_ACCEPT`, `STA_TX_PR_SWAP`, and `STA_RX_PR_SWAP_ACCEPT`.
- `User/USBPD/Src/usbpd_pe.c:147-176` handles received Control Messages only for `Soft_Reset`, `Accept`, `Reject`, `PS_RDY`, and `GoodCRC`.
- There is no `DEF_TYPE_PR_SWAP` handler, no non-modal `DEF_TYPE_DR_SWAP` evaluate path, and no code path that sends `Accept`, `Reject`, or `Wait` if these role-swap AMSs are intended to be supported.
- There is also no `Not_Supported` transmit path for treating these role-swap requests as unsupported sequences on this Sink-only/UFP-only implementation.
- `PD-R3.2-020` covers the special Modal Operation case where `DR_Swap` must trigger Hard Reset; this finding covers the separate non-modal DR_Swap and PR_Swap response requirements.

Why this is non-compliant:
- A compliant Port Partner can initiate a role-swap request. This firmware GoodCRCs the control message and then silently drops it, instead of either running the supported AMS response path or returning `Not_Supported` for an unsupported sequence.

## PD-R3.2-046 - Sink discovery is not gated by VBUS-present detection

Spec evidence:
- Section 9.2.4.1 says `PE_SNK_Startup` shall reset the Protocol Layer and then transition to `PE_SNK_Discovery`.
- Section 9.2.4.2 says that in `PE_SNK_Discovery` the Sink Policy Engine waits for VBUS to be present.
- The same section says the Policy Engine shall transition to `PE_SNK_Wait_for_Capabilities` when the Device Policy Manager indicates that VBUS has been detected.
- The note before Section 9.2.4.1 says that during Hard Reset the Source voltage transitions to vSafe0V and then vSafe5V, and Sinks need to ensure VBUS present is not indicated until after both transitions are detected.

Code evidence:
- `User/USBPD/Src/usbpd_phy.c:122-193` detects attach only from CC comparator state and, once the CC condition is stable, sets `USBPD_Control.Flag.Connected = 1`, enters `STA_SRC_CONNECT`, sends a Hard Reset, and enables RX.
- `User/USBPD/Src/usbpd_pe.c:183-188` accepts any received `Source_Capabilities` Data Message and schedules a `Request` without checking whether the DPM has indicated VBUS present.
- No VBUS/vSafe5V detection signal, ADC/PVD measurement path, DPM VBUS-present flag, or equivalent gate exists in `User/USBPD`, `User/App`, `User/Board`, or `User/Drivers`.

Why this is non-compliant:
- This Sink can start PD discovery traffic and process Source Capabilities based only on CC attach. The Sink Policy Engine is required to remain in `PE_SNK_Discovery` until the DPM reports VBUS present, so it cannot correctly handle cold-socket attach or post-Hard-Reset vSafe0V-to-vSafe5V sequencing.

## PD-R3.2-047 - DP pin configuration is applied before the Enter Mode process

Spec evidence:
- Section 8.6.4 says that before entering an Alternate Mode that requires reconfiguring pins, the Responder shall ensure the pins being reconfigured are placed into either USB operation or USB Safe State.
- Section 8.6.4 also says that if the Responder ACKs an `Enter Mode` Command Request, the Responder shall enter the Alternate Mode before sending the ACK.
- Figure 8.1 shows the UFP Responder remaining in USB or USB Safe State before the successful `Enter Mode` ACK, and entering the new Mode as part of that sequence.
- Section 9.2.25.1 says the UFP Policy Engine shall request the DPM to evaluate the `Enter Mode` request and enter the indicated Mode if acceptable; only when the DPM indicates that the Mode has been entered does the PE transition to the Enter Mode ACK state.

Code evidence:
- `User/App/main.c:23` and `User/App/main.c:30` call `VL171_ApplyMode(VL171_MODE_USB_DP_2LANE)` immediately from the Type-C attach/orientation callback, before any Explicit Contract, Structured VDM discovery, or `Enter Mode` request has completed.
- `User/Drivers/Src/vl171.c:72-75` implements `VL171_MODE_USB_DP_2LANE` as a DP-related mux state and logs it as `VL171 2-lane DP + USB3`.
- `User/Drivers/Src/vl171.c:89-103` uses the same `VL171_ApplyMode()` API to apply DP pin assignments later from a `DP Configure` command, confirming that these modes are the DP Alt Mode connector configurations.
- `User/USBPD/Src/usbpd_vdm_handler.c:254-267` handles `Enter Mode` by setting a mode-active bit, enabling HPD, and ACKing; it does not first restore or verify USB operation/USB Safe State for the pins that had already been placed in the DP+USB mux configuration at attach.

Why this is non-compliant:
- The local connector is placed into a DP Alt Mode mux configuration as soon as CC attach is detected, before the PD Alternate Mode entry process authorizes that pin reconfiguration. The required sequence is USB operation or USB Safe State until a valid `Enter Mode` request is evaluated and the Responder enters the Mode as part of the ACK path.

## PD-R3.2-048 - DP SVID-specific commands are ACKed when no DP Active Mode exists

Spec evidence:
- The glossary defines an Active Mode as a Mode which has been through the Mode Entry process but not the Mode Exit process.
- Section 8.7.2 says the Initiator uses the `Enter Mode` Command to enable the Alternate Mode, and once the Alternate Mode is entered, the Device shall remain in that Active Mode until the `Exit Mode` Command is successful.
- Figure 8.5 shows `Discover Modes`, then `Enter Mode`, then `ACK (Responder switched to Mode)`, followed by the Initiator and Responder operating using the Mode.
- Section 8.6 says the Responder shall ACK only if it recognizes the SVID and is able to process the command at the expected time, and shall NAK if it recognizes the SVID but cannot process the Command Request.

Code evidence:
- `User/USBPD/Src/usbpd_vdm_handler.c:265` sets `USBPD_Control.Mode_Try_Cnt |= 0x80u` on `Enter Mode`, and `User/USBPD/Src/usbpd_vdm_handler.c:273` clears that active-mode bit on `Exit Mode`.
- `User/USBPD/Inc/pd_dp_alt_mode.h:19-21` defines DP SVID-specific command values `USBPD_DP_CMD_STATUS_UPDATE` and `USBPD_DP_CMD_CONFIGURE`.
- `User/USBPD/Src/usbpd_vdm_handler.c:287-313` ACKs a DP `Status Update` for the DP SVID without checking whether the DP active-mode bit is set.
- `User/USBPD/Src/usbpd_vdm_handler.c:317-359` validates and ACKs a DP `Configure` command for the DP SVID without checking whether the DP active-mode bit is set; when the requested configuration is a DP configuration, `User/USBPD/Src/usbpd_vdm_handler.c:352` applies the DP pin assignment through `VL171_ApplyDPPinAssignment(config_vdo)`.

Why this is non-compliant:
- A DFP can send DP Mode-specific Status or Configure commands before a successful `Enter Mode`, or after `Exit Mode`, and this firmware can ACK them and even change the mux. Until the DP Mode has become an Active Mode, those commands are not processable at the expected time and should be rejected rather than treated as valid mode operation.

## PD-R3.2-049 - Enter_USB requests to the UFP are ignored instead of answered

Spec evidence:
- Section 6.4.7 says the `Enter_USB` Message shall be sent by the DFP to its UFP Port Partner and to Active Cable Plug(s), when in an Explicit Contract, to enter a specified USB Mode of operation.
- Section 7.29 says the recipient of an `Enter_USB` Message shall respond by sending an `Accept`, `Wait`, or `Reject` Message.
- Section 7.29 says `Reject` shall be sent by the UFP on receiving an `Enter_USB` Message to indicate it is unable to enter the requested USB Mode.
- Section 9.2.17.2 says `PE_UEU_Enter_USB_Received` shall be entered when an `Enter_USB` Message is received and the Port is operating as a UFP; on entry, the PE shall inform the DPM and send `Accept`, `Wait`, or `Reject` based on the DPM response.

Code evidence:
- `Core/Inc/ch32l103_usbpd.h:119` defines `DEF_TYPE_ENTER_USB` as Data Message type `0x08`.
- `User/USBPD/Src/usbpd_pe.c:179-197` handles received Data Messages only for `DEF_TYPE_SRC_CAP` and `DEF_TYPE_VENDOR_DEFINED`.
- There is no `DEF_TYPE_ENTER_USB` case, no DPM notification path for an Enter USB request, and no outgoing `Accept`, `Wait`, or `Reject` response path for this AMS.
- `User/USBPD/Src/usbpd_pe.c:24-25` resets this implementation to Sink/UFP roles, so this is the UFP responder path when a DFP sends `Enter_USB`.

Why this is non-compliant:
- A DFP can legally request USB mode entry with `Enter_USB`. This UFP acknowledges the packet at the Protocol Layer with GoodCRC and then silently drops the request, leaving the DFP without the required AMS response and preventing the DPM from accepting, deferring, or rejecting the requested USB mode.

## PD-R3.2-050 - Soft_Reset disrupts local Alternate Mode state instead of only resetting PD protocol

Spec evidence:
- Section 7.1 says USB Power Delivery defines Soft Reset as resetting protocol, while Data Reset resets USB communications and Hard Reset resets both power supplies and protocol.
- Section 7.1.1 says a Soft Reset shall not have any impact on power supply operation and shall impact USB Power Delivery layers by resetting MessageIDCounter, RetryCounter, Protocol Layer state machines, and Policy Engine state-dependent behavior through Explicit Contract Negotiation.
- Section 6.3.14 says `Data_Reset` is the message used to reset the USB data connection and exit all Alternate Modes while preserving VBUS.
- Section 8.7.3 lists unmanaged Alternate Mode termination triggers as Data Reset, Hard Reset, Error Recovery, and Detach; Soft Reset is not one of the triggers.

Code evidence:
- `User/USBPD/Src/usbpd_vdm_handler.c:265-266` marks DP Alt Mode active with `Mode_Try_Cnt |= 0x80u` and enables HPD through `USBPD_HPD_EnterMode()` when `Enter Mode` is ACKed.
- `User/USBPD/Src/usbpd_pe.c:151-154` handles a received `Soft_Reset` by calling `USBPD_PE_Reset()`.
- `User/USBPD/Src/usbpd_pe.c:21-29` implements `USBPD_PE_Reset()` by resetting local roles, VDM version, communication success state, and calling `USBPD_HPD_Reset()`.
- `User/USBPD/Src/usbpd_hpd.c:118-127` disables HPD interrupt handling and clears HPD logical/reporting state.
- `Core/Inc/ch32l103_usbpd.h:296` stores the active-mode marker in `Mode_Try_Cnt`, but `USBPD_PE_Reset()` does not clear it or run an `Exit Mode`, Data Reset, Hard Reset, Error Recovery, or Detach path.

Why this is non-compliant:
- A Soft Reset is a PD protocol recovery operation, not an Alternate Mode termination mechanism. If DP Alt Mode is active, this firmware can locally disable HPD and clear mode-related reporting state while leaving the Active Mode marker and connector/mux state inconsistent, even though the spec only defines Alternate Mode exit through managed `Exit Mode` or the unmanaged termination events listed in Section 8.7.3.

## PD-R3.2-051 - VCONN_Swap requests are silently ignored

Spec evidence:
- Section 6.3.11 says the `VCONN_Swap` Message is used to request an exchange of VCONN Source ownership and is used in the VCONN Swap sequence.
- Table 7.4 lists `VCONN_Swap` as an AMS that may be initiated by any Port, with `Accept`, `Reject`, or `Wait` sent by the Responder and `PS_RDY` sent by the New VCONN Source.
- Table 7.4 says VCONN Swap responder behavior is required for ports that can supply VCONN.
- Section 9.2.21 says the VCONN Swap state diagram applies to ports that supply VCONN, on sending or receiving a VCONN Swap request.
- Section 9.2.21.2 says that when a `VCONN_Swap` Message is received, the Policy Engine shall enter `PE_VCS_Evaluate_Swap` and request the Device Policy Manager to evaluate the VCONN Swap request.
- Sections 9.2.21.3 and 9.2.21.4 require the responder path to send `Accept`, or `Reject`/`Wait` as appropriate.
- Section 6.3.16 says `Not_Supported` shall be sent in response to any Message the Port does not support or is unable to interpret.

Code evidence:
- `Core/Inc/ch32l103_usbpd.h:95` defines `DEF_TYPE_VCONN_SWAP`.
- `User/USBPD/Src/usbpd_pe.c:147-176` handles received Control Messages only for `Soft_Reset`, `Accept`, `Reject`, `PS_RDY`, and `GoodCRC`.
- There is no `DEF_TYPE_VCONN_SWAP` receive case, no DPM VCONN-swap evaluation path, no `Accept`/`Reject`/`Wait` response path, no `PS_RDY` VCONN-swap completion path, and no `Not_Supported` fallback for treating VCONN Swap as unsupported.
- A focused search for VCONN handling under `User/USBPD` finds only the VPD product-type enum in `pd_vdm.h`, not any VCONN supply or swap state-machine implementation.

Why this is non-compliant:
- If this Port can supply VCONN, a received `VCONN_Swap` must enter the VCONN Swap responder AMS and answer with `Accept`, `Reject`, or `Wait`. If this Port does not support VCONN Swap, it must return `Not_Supported`. The current firmware GoodCRCs the control message and then silently drops it, so the initiator sees a missing AMS response instead of the defined responder behavior.

## PD-R3.2-052 - Invalid Structured VDM command NAKs can echo an invalid Object Position

Spec evidence:
- Table 6.33 defines Structured VDM Header `Command` value 0 as invalid and says the receiver shall respond with NAK.
- Table 6.33 also defines `Command` values 7 through 15 as invalid and says the receiver shall respond with NAK.
- Table 6.33 says that when `Command` is 0 through 3 or 7 through 15, Object Position `000b` shall be used and values `001b` through `111b` are invalid.
- Section 6.4.12.2.2 says the Object Position field shall be set to zero in the request or response, including NAK, when not required by the individual command.
- Section 8.5 says the responder shall NAK a Structured VDM command request that is an unrecognized message.

Code evidence:
- `User/USBPD/Src/usbpd_vdm_handler.c:373-377` copies the incoming Structured VDM Header from the received buffer into `vdm_header`.
- `User/USBPD/Src/usbpd_vdm_handler.c:362-365` handles every otherwise unrecognized Structured VDM command by calling `USBPD_ReplyStructuredVDM(..., USBPD_SVDM_CMDTYPE_NAK, 1u, NULL)`.
- `User/USBPD/Src/usbpd_vdm_handler.c:118-125` builds that response by changing only `CommandType` and Structured VDM version fields before transmitting the copied header.
- There is no clearing of `vdm_header->Bit.ObjectPosition` in the default NAK path for invalid command values 0 or 7 through 15.
- `PD-R3.2-035` covers the separate Discover Identity/SVIDs/Modes response paths; this finding covers the default invalid-command NAK path.

Why this is non-compliant:
- A malformed Structured VDM with an invalid command and Object Position `001b` through `111b` can cause the firmware to send a NAK response that repeats the invalid Object Position. The responder is required to NAK the command, but the response header itself still has to encode Object Position as `000b` when that field is not required by the command.

## PD-R3.2-053 - Unexpected recognized control responses do not trigger Protocol Error recovery

Spec evidence:
- The glossary defines an `Unexpected Message` as a message that a Port supports but has received in an incorrect state.
- The glossary defines `Protocol Error` as an Unexpected Message during an AMS and says a Protocol Error during an AMS results in either a Soft Reset or a Hard Reset.
- Section 7.1.1 says a protocol breakdown includes receiving an Unexpected Message during an AMS, an expected Message failing to arrive, or a timeout while waiting for a Message or event.
- Table 7.1 says that in `PE_SNK_Ready`, an unexpected recognized/supported incoming message shall cause a `Soft_Reset` Message when power is not transitioning, and a Hard Reset when power is transitioning.
- Section 9.2.5.2.1 says `PE_SNK_Send_Soft_Reset` shall be entered from any state when a Protocol Error on SOP is detected during an AMS; on entry, the Sink shall request SOP Protocol Layer Soft Reset, send `Soft_Reset` on SOP, and initialize/run `SenderResponseTimer`.

Code evidence:
- `User/USBPD/Src/usbpd_pe.c:147-176` handles received Control Messages only by message type, not by the current Policy Engine AMS state.
- `User/USBPD/Src/usbpd_pe.c:156-168` accepts `Accept`, `Reject`, and `PS_RDY` in any state by printing a log line and then falling through to clear `Msg_Recvd`.
- There is no check that an `Accept` is being received during `PE_SNK_Select_Capability` or a supported swap/reset AMS, no check that `PS_RDY` is being received during `PE_SNK_Transition_Sink`, and no unexpected-response path that enters `PE_SNK_Send_Soft_Reset` or `PE_SNK_Hard_Reset`.
- `User/USBPD/Src/usbpd_pe.c:112-205` has no Policy Engine state that tracks an active AMS, power-transition phase, or expected next control response; the only transmit states used by this Sink path are `STA_TX_GOODCRC`, `STA_TX_REQ`, and `STA_VDM`.

Why this is non-compliant:
- A Source can send a recognized control response such as `Accept`, `Reject`, or `PS_RDY` when this Sink has no matching AMS pending, or while a different AMS is active. The firmware GoodCRCs and silently accepts the unexpected response instead of performing the Protocol Error recovery required for recognized messages received in the wrong state.

## PD-R3.2-054 - Unexpected Structured VDM responses are accepted without Protocol Error handling

Spec evidence:
- Section 7.1.1 says a Protocol Error includes an Unexpected Message received during an AMS, and that the resulting recovery may be a Soft Reset or Hard Reset.
- Table 7.1 says an unexpected recognized/supported incoming message in `PE_SNK_Ready` shall cause a `Soft_Reset` Message when power is not transitioning, or Hard Reset signaling when power is transitioning.
- Table 7.4 identifies Structured VDM `ACK`/`NAK`/`BUSY` messages as responses transmitted by the Responder in the corresponding SVDM AMS.
- Section 8.6 says a Structured VDM AMS normally consists of a Command Request and a Command response, and that Attention is the exception to the request/response flow.
- Table 8.1 says responses not listed for a given Structured VDM Command shall not be sent, and lists `Attention` with response `None`.
- Section 9.2.5.2.1 says `PE_SNK_Send_Soft_Reset` shall be entered when a Protocol Error on SOP is detected during an AMS; on entry, the Sink shall reset the SOP Protocol Layer, send `Soft_Reset` on SOP, and run `SenderResponseTimer`.

Code evidence:
- `User/USBPD/Src/usbpd_vdm_handler.c:128-144` constructs the only local Structured VDM request path as an `Attention` request.
- `User/USBPD/Src/usbpd_pe.c:202-204` only attempts that local Attention request from the idle path; there is no local Discover Identity, Discover SVIDs, Discover Modes, Enter Mode, or Exit Mode initiator state that would expect an `ACK`, `NAK`, or `BUSY` response.
- `User/USBPD/Src/usbpd_vdm_handler.c:383-395` handles received Structured VDM `ACK`, `NAK`, and `BUSY` command types by only calling `USBPD_LogVDMCommandType()`.
- There is no check that the received response matches a pending SVDM request, no rejection of an illegal response to the local Attention command, and no transition to `PE_SNK_Send_Soft_Reset` or `PE_SNK_Hard_Reset`.

Why this is non-compliant:
- A Port Partner can send a Structured VDM response when this UFP has no corresponding SVDM request outstanding, or can illegally answer the UFP's Attention request even though Attention has no response. The firmware treats those recognized VDM responses as harmless log events instead of detecting the unexpected message and running the Protocol Error recovery required by the Sink Policy Engine.

## PD-R3.2-055 - Modal Operation lacks required Structured VDM discovery initiator support

Spec evidence:
- Section 7.5 says the `Initiator Applicability` column in Table 7.4 is a Port's requirement to be able to start an AMS, and that Ports may initiate or respond to any AMS not explicitly forbidden.
- Table 7.4 lists `Discover Identity (SVDM)` initiated by `Any` Port and makes it required for ports that support Modal Operation.
- Table 7.4 lists `Discover SVIDs (SVDM)` and `Discover Modes (SVDM)` initiated by `Any` Port, with initiator applicability required for ports that support Modal Operation.
- Section 8.5 says either Port may initiate a Structured VDM AMS, except that the UFP shall not initiate `Enter Mode` or `Exit Mode`; discovery commands are not part of that UFP prohibition.
- Section 9.2.22 defines Initiator Structured VDM discovery state diagrams from `PE_SRC_Ready` or `PE_SNK_Ready`: the PE sends Discover Identity, Discover SVIDs, or Discover Modes requests when the DPM requests discovery, starts the required VDM timer, and informs the DPM of ACK/NAK/BUSY/timeout results.

Code evidence:
- `User/USBPD/Src/usbpd_vdm_handler.c:204-207` sets `ModalOperationSupported = 1` in the Discover Identity ACK, and `User/USBPD/Src/usbpd_vdm.c:32-58` defines this Port's DisplayPort Alt Mode capability, so this firmware is implementing a Modal Operation-capable Port.
- `User/USBPD/Src/usbpd_vdm_handler.c:195-250` implements Discover Identity, Discover SVIDs, and Discover Modes only as incoming request responder cases.
- `User/USBPD/Src/usbpd_vdm_handler.c:128-144` constructs the only local Structured VDM request, and that request is `Attention`.
- `User/USBPD/Src/usbpd_pe.c:202-204` only calls `USBPD_VDM_TrySendAttention()` from the idle path; there is no DPM-driven initiator state for Discover Identity, Discover SVIDs, or Discover Modes, no `VDMResponseTimer`, and no handling of discovery ACK/NAK/BUSY/timeout results.

Why this is non-compliant:
- The Port can answer a DFP's DP Alt Mode discovery, but it cannot itself start the Structured VDM discovery AMSs that Table 7.4 requires for Modal Operation-capable Ports. Since UFPs are only forbidden from initiating Enter Mode and Exit Mode, this Sink/UFP still needs the discovery initiator capability and the corresponding Policy Engine states/timers when local policy requests discovery.

## PD-R3.2-056 - DP Status and Configure commands accept invalid Object Position values

Spec evidence:
- USB PD Table 6.33 defines Structured VDM Header `Object Position` for SVID-specific commands, Command values 16 through 31, as defined by the SVID.
- USB PD Section 8.6 says a Structured VDM Responder shall ACK only if it recognizes the SVID and is able to process the command at the expected time, and shall NAK if it recognizes the SVID but cannot process the Command Request, or if a command parameter is invalid.
- DisplayPort Alt Mode v2.0 Section 5.2 says the DFP_U and UFP_U shall use the corresponding DP Capabilities VDO offset, indexed from 1, as the Object Position for `DisplayPort Status Update` and `DisplayPort Configure`.
- The same DisplayPort Alt Mode note says that if the Object Position is not valid for DisplayPort Alt Mode or some other Mode, USB PD mandates that the Responder respond with a NAK.
- DisplayPort Alt Mode Section 5.2.4 says the UFP_U shall respond with a USB PD Responder NAK if it is unable to change to the requested Configuration.

Code evidence:
- `User/USBPD/Src/usbpd_vdm.c:34` sets this implementation's only DP Mode object position to `USBPD_DP_OBJECT_POSITION_1`.
- `User/USBPD/Src/usbpd_vdm_handler.c:238-250` returns exactly one DP Mode VDO for the DP SVID, so Object Position 1 is the only valid DP Mode reference exposed by this responder.
- `User/USBPD/Src/usbpd_vdm_handler.c:257-260` validates `ObjectPosition` for `Enter Mode`, showing that the implementation already has the local DP mode offset available.
- `User/USBPD/Src/usbpd_vdm_handler.c:287-313` handles `DisplayPort Status Update` by checking only the SVID, optionally logging the received status VDO, and then ACKing with local status; it never checks that `vdm_header->Bit.ObjectPosition == USBPD_DP_ALT_MODE.object_position`.
- `User/USBPD/Src/usbpd_vdm_handler.c:317-359` handles `DisplayPort Configure` by checking SVID, `NumDO`, and the Configure VDO contents, but never checks the Structured VDM Object Position before applying a DP pin assignment and ACKing.

Why this is non-compliant:
- After DP Mode discovery exposes only Object Position 1, a DFP can send DP `Status Update` or `Configure` with Object Position 0 or 2 through 7. The firmware treats those commands as valid for the local DP Mode and can even change the mux, instead of NAKing an invalid DP Mode reference.

## PD-R3.2-057 - DisplayPort Configure to USB is ACKed without reconnecting pins to USB

Spec evidence:
- DisplayPort Alt Mode v2.0 Section 5.2.4 says the DFP_U may change to USB Configuration by using the DisplayPort Configure Command with `Select Configuration` programmed to USB.
- The same section says the UFP_U may start to use USB immediately after receiving this command.
- The same section requires the UFP_U to respond with a USB PD Responder ACK only after connecting the reconfigured pins to USB, where USB functionality on these pins is supported.
- DisplayPort Alt Mode Table 5.8 defines the USB Configuration encoding as `Select Configuration = 00b`, unspecified signaling, and pin assignment cleared to 0.

Code evidence:
- `User/USBPD/Src/usbpd_vdm.c:42-48` includes the USB Configuration VDO in `USBPD_DP_ALT_MODE.supported_configurations`, so the firmware advertises that this DP Configure request is supported.
- `User/USBPD/Src/usbpd_vdm_handler.c:42-58` treats that exact USB Configuration VDO as supported.
- `User/USBPD/Src/usbpd_vdm_handler.c:343-359` handles a supported DP Configure request, but the `USBPD_DP_SELECT_USB` branch only calls `USBPD_HPD_Disable()` before sending ACK.
- `User/USBPD/Src/usbpd_vdm_handler.c:352` applies a VL171 mux change only in the non-USB branch through `VL171_ApplyDPPinAssignment(config_vdo)`.
- `User/Drivers/Inc/vl171.h:13-21` and `User/Drivers/Src/vl171.c:68-104` expose only DP-related `VL171_MODE_USB_DP_2LANE` and `VL171_MODE_DP_4LANE` modes plus DP pin-assignment application; no USB-only/default restore API is called from the USB Configure path.

Why this is non-compliant:
- If the port was previously configured for DP, a valid DP Configure request selecting USB Configuration can be ACKed while the VL171 and high-speed pins remain in the earlier DP-related mux state. The responder is required to connect the reconfigured pins to USB before ACKing the command.

## PD-R3.2-058 - DP Attention transmission lacks the required third-message pacing

Spec evidence:
- DisplayPort Alt Mode v2.0 Section 5.2.2 says a UFP_U may transmit a USB PD Attention Command Request after entering DisplayPort Alt Mode and shall do so as soon as possible after its status changes.
- The same section says that, when operating in USB PD 3.0 Mode, USB PD itself does not restrict the rate at which Attention Command Requests are generated.
- The same section then requires the UFP_U to ensure a 10 ms gap before transmitting a third USB PD Attention Command Request after transmitting two USB PD Attention Command Requests spaced less than 10 ms apart.

Code evidence:
- `User/USBPD/Src/usbpd_pe.c:202-204` calls `USBPD_VDM_TrySendAttention(pe_tx_buf)` on every idle Policy Engine pass when no received message is pending.
- `User/USBPD/Src/usbpd_vdm_handler.c:147-185` sends an Attention immediately whenever `USBPD_HPD_PollEvent()` returns an HPD event.
- `User/USBPD/Src/usbpd_hpd.c:15-19` stores pending HPD high, low, and IRQ events, and `User/USBPD/Src/usbpd_hpd.c:88-109` pops those pending events one at a time without any Attention transmit-rate state.
- `User/USBPD/Src/usbpd_hpd.c:54` and `User/USBPD/Src/usbpd_hpd.c:211` use `USBPD_Tim_GetUs16()` only to measure HPD low pulse width; no code stores prior Attention transmit times or enforces a 10 ms gap before a third Attention.

Why this is non-compliant:
- If HPD changes queue multiple Attention-worthy events close together, this firmware can transmit them on consecutive idle iterations with only the generic inter-frame delay. DP Alt Mode requires the UFP_U to throttle the third closely spaced Attention so the DFP_U is not overrun.

## PD-R3.2-059 - DP Capabilities can omit the mandatory DP-only pin assignment in multi-function mode

Spec evidence:
- DisplayPort Alt Mode v2.0 Section 3.2.1 says Table 3.7 lists mandatory pin assignments for a USB-C receptacle DP Sink device.
- Table 3.7 marks Pin Assignment C as mandatory for a USB-C receptacle DP Sink device using a USB-C-to-USB-C connection, and marks Pin Assignment D as optional.
- DisplayPort Alt Mode Table 5.5 defines the `DP Sink Device Pin Assignments Supported` field returned in the DP Capabilities VDO.
- DisplayPort Alt Mode Section 5.2 note c says a system supporting DisplayPort on a USB-C connector and supporting Multi-function Mode, simultaneous USB SuperSpeed and DisplayPort, shall offer both the multi-function pin assignment and the associated DP-only pin assignment.
- The same note says the associated DP-only pin assignment for multi-function Pin Assignment D is Pin Assignment C, and the system shall offer both pin assignments even if it supports only one or two DP lanes.

Code evidence:
- `User/USBPD/Src/usbpd_vdm.c:36-40` declares this port as a DP Sink/UFP_D on a USB-C receptacle and initializes the DP Capabilities VDO with only Pin Assignment C.
- `User/App/main.c:42-48` selects `USBPD_DP_LANE_MODE_2LANE` by default unless the startup key is pressed.
- `User/USBPD/Inc/usbpd_vdm.h:8-10` defines `USBPD_DP_LANE_MODE_2LANE` as Pin Assignment D, 2-lane DP plus USB3.
- `User/USBPD/Src/usbpd_vdm.c:62-69` changes `USBPD_DP_ALT_MODE.mode_vdo.Bit.UFP_DPinAssignments` to exactly one pin assignment: Pin D in 2-lane mode or Pin C in 4-lane mode.
- `User/USBPD/Src/usbpd_vdm_handler.c:235-250` returns that single DP Capabilities VDO in the Discover Modes ACK for the DP SVID.

Why this is non-compliant:
- In the default 2-lane/multi-function configuration, the Discover Modes ACK advertises Pin Assignment D but omits the mandatory associated DP-only Pin Assignment C. A DFP_U is not given the required capability set for this USB-C receptacle DP Sink, and cannot select the mandated C fallback/DP-only configuration from the advertised Mode VDO.

## PD-R3.2-060 - Extended Messages are decoded as Control/Data Messages when Ext is set

Spec evidence:
- USB PD Table 6.2 defines the Message Header `Extended` bit and says the Message Type is determined in this order: if `Extended` is set, refer to Section 6.5; otherwise, if `Number of Data Objects` is greater than 0, refer to Table 6.5; otherwise refer to Table 6.4.
- Section 6.5 says an Extended Message shall contain a Message Header, an Extended Message Header indicated by the Message Header `Extended` field being set, and zero or more data bytes.
- Table 6.47 defines Extended Message Type `01101b` as `Country_Info`, not `Soft_Reset`; it also defines Extended Message Type `00001b` as `Source_Capabilities_Extended`, not the SPR `Source_Capabilities` Data Message.
- Section 7.1.1 says an Unrecognized or Unsupported Message received in a Policy Engine ready state causes a `Not_Supported` Message to be generated.

Code evidence:
- `Core/Inc/ch32l103_usbpd.h:252-260` defines the received Message Header fields, including the `Ext` bit.
- `User/USBPD/Inc/usbpd_helper.h:29` extracts only the low five Message Type bits with `USBPD_MSG_TYPE_FROM_HEADER(HEADER)` and does not include the `Ext` bit in message classification.
- `User/USBPD/Src/usbpd_pe.c:144-147` reads the low five Message Type bits and classifies incoming messages only as `NumDO == 0` Control Messages or `NumDO > 0` Data Messages.
- `User/USBPD/Src/usbpd_pe.c:151-154` handles Message Type `0x0D` as `Soft_Reset` and resets the PE without checking that `last_rx_header.Message_Header.Ext == 0`.
- `User/USBPD/Src/usbpd_pe.c:183-192` handles Message Types `0x01` and `0x0F` as `Source_Capabilities` and `Vendor_Defined` Data Messages without checking that `Ext == 0`.

Why this is non-compliant:
- The Message Header `Ext` bit is the first discriminator for the Message Type namespace. This firmware ignores it, so an Extended Message can enter the ordinary Control/Data handlers. For example, an Extended `Country_Info` message carrying Message Type `0x0D` can be treated as `Soft_Reset`, and an Extended `Source_Capabilities_Extended` message can be treated as an SPR `Source_Capabilities` Data Message. The correct behavior is to classify the packet as an Extended Message and either process the defined Extended Message flow or return the required unsupported-message response, not execute an unrelated Control/Data AMS.

## PD-R3.2-061 - HPD-to-USB PD conversion can drop the second queued IRQ_HPD event

Spec evidence:
- DisplayPort Alt Mode v2.0 Section 3.9.2.3.1 says that if an `IRQ_HPD` is detected while a previous `IRQ_HPD` is in the queue, the converter shall transmit DisplayPort Status Update or USB PD Attention Commands for both `IRQ_HPD` events.
- The same section says only `IRQ_HPD` events detected while two `IRQ_HPD` events are already in the queue may be discarded.
- The same section notes that the worst-case status buffering needed in the HPD-to-USB PD converter is the sequence `HPD_Low`, `HPD_High`, `IRQ_HPD`, `IRQ_HPD`.

Code evidence:
- `User/USBPD/Src/usbpd_hpd.c:15-19` stores pending HPD events as one boolean each: `s_pending_high`, `s_pending_low`, and `s_pending_irq`, with only one `s_pending_irq_low_us` value.
- `User/USBPD/Src/usbpd_hpd.c:103-109` pops at most one pending `IRQ_HPD` event and then clears `s_pending_irq`.
- `User/USBPD/Src/usbpd_hpd.c:234-238` handles every qualifying IRQ pulse by overwriting `s_pending_irq_low_us`, setting `s_pending_irq = 1`, and returning; it has no second IRQ slot, queue depth, or counter.
- `User/USBPD/Src/usbpd_vdm_handler.c:147-185` later emits one Attention for one popped HPD event, so the lost queue entry is not reconstructed at the USB PD layer.

Why this is non-compliant:
- If two valid `IRQ_HPD` pulses occur before the main loop transmits the first pending Attention or Status response, the second pulse overwrites the single stored IRQ state instead of being retained as a second queued `IRQ_HPD`. The DP Alt Mode HPD-to-USB PD converter is required to transmit both queued IRQ events and may discard only additional IRQ events after two are already queued.

## PD-R3.2-062 - DP Capabilities omit mandatory Pin Assignment E for a USB-C receptacle DP Sink

Spec evidence:
- DisplayPort Alt Mode v2.0 Section 3.2.1 says Table 3.6 and Table 3.7 list the mandatory pin assignments for a USB-C receptacle that supports DisplayPort.
- Table 3.7, `USB-C Receptacle DP Sink Device Pin Assignment Mandates`, marks Pin Assignment E as mandatory for a USB-C-to-DP connection for both USB Host and USB Device rows; Pin Assignment C is mandatory for USB-C-to-USB-C and Pin Assignment D is optional.
- DisplayPort Alt Mode Table 5.5 defines the `DP Sink Device Pin Assignments Supported` field returned by a DP Sink/UFP_D in the DP Capabilities VDO.
- DisplayPort Alt Mode Section 5.2.4 and Table 5.8 define Pin Assignment E (`10h`) as a selectable DisplayPort Configure pin assignment.

Code evidence:
- `User/USBPD/Src/usbpd_vdm.c:36-40` declares this port as a DP Sink/UFP_D implemented on a USB-C receptacle, but initializes the DP Capabilities VDO with only Pin Assignment C.
- `User/USBPD/Src/usbpd_vdm.c:41-58` exposes only USB Configuration and one DP Configuration in the supported Configure whitelist; the DP entry is initialized as Pin Assignment C.
- `User/USBPD/Src/usbpd_vdm.c:62-69` changes both the advertised `UFP_DPinAssignments` field and the accepted DP Configure entry to exactly one pin assignment: Pin D in 2-lane mode or Pin C in 4-lane mode.
- `User/USBPD/Src/usbpd_vdm_handler.c:42-58` accepts a DP Configure VDO only if it exactly matches an entry in that whitelist, so a Configure request selecting Pin Assignment E is rejected even though `User/Drivers/Src/vl171.c:96-102` can map Pin E to the same 4-lane mux mode as Pin C.
- `User/USBPD/Src/usbpd_vdm_handler.c:235-250` returns the single DP Capabilities VDO from the mutable `USBPD_DP_ALT_MODE.mode_vdo` in Discover Modes ACKs.

Why this is non-compliant:
- A USB-C receptacle DP Sink device is required to support and advertise Pin Assignment E for USB-C-to-DP connections. This firmware never advertises Pin E in Discover Modes and never includes Pin E in the accepted Configure VDO set. A DFP_U cannot discover or select the mandatory USB-C-to-DP DP Sink pin assignment for this receptacle-based DP Sink.

## PD-R3.2-063 - HPD_Low can be reported before older queued HPD events and leave stale IRQ_HPD pending

Spec evidence:
- DisplayPort Alt Mode v2.0 Section 3.9.2.3.1 defines HPD-to-USB PD converter message queuing mandates and says `HPD_Low`, `HPD_High`, and `IRQ_HPD` are HPD events.
- The same section says that if `HPD_Low` is detected while any previous HPD events are in the queue, the previous HPD events may be discarded.
- The same section says that an `IRQ_HPD` detected while a previous `HPD_High` is in the queue shall be transmitted either in one message or as separate messages in the order detected.
- DisplayPort Alt Mode Table 5.6 says `IRQ_HPD` may be generated only when the HPD State is `HPD_High`.

Code evidence:
- `User/USBPD/Src/usbpd_hpd.c:15-19` represents the HPD event queue as independent booleans for pending high, low, and IRQ events, not as an ordered FIFO.
- `User/USBPD/Src/usbpd_hpd.c:88-108` always pops events in fixed priority order: `s_pending_low`, then `s_pending_high`, then `s_pending_irq`, regardless of the order in which those events were detected.
- `User/USBPD/Src/usbpd_hpd.c:72-76` can detect a long-low `HPD_Low` while HPD remains low and return that low event without clearing any older `s_pending_high` or `s_pending_irq`.
- `User/USBPD/Src/usbpd_hpd.c:242-246` sets `s_pending_low = 1` after a long-low pulse but also does not clear older pending high or IRQ events.
- `User/USBPD/Src/usbpd_hpd.c:102-108` later converts a stale pending IRQ into an event with `logical_high = 1` and `irq_hpd = 1`.

Why this is non-compliant:
- If an `IRQ_HPD` or `HPD_High` event is queued and a later `HPD_Low` is detected before the queue is drained, the firmware can report `HPD_Low` first and then report the older high/IRQ event afterward. The DP Alt Mode converter may discard previous HPD events when `HPD_Low` is detected, or it must preserve valid event ordering; it must not send a stale `IRQ_HPD` after reporting HPD low, because `IRQ_HPD` is only valid with HPD State high.

## PD-R3.2-064 - DP Status reports Enabled even when DisplayPort functionality has been disabled

Spec evidence:
- DisplayPort Alt Mode v2.0 Section 5.2.3 says the DFP_U may transmit a DisplayPort Status Update Command at any time and that the UFP_U responds by transmitting its DisplayPort Status Update in the VDO.
- DisplayPort Alt Mode Table 5.6 defines the DisplayPort Status `Enabled` bit: `0 = Adapter DP functionality is disabled`, `1 = Adapter DP functionality is enabled and operational`.
- DisplayPort Alt Mode Section 5.2.4 says the DFP_U may change to USB Configuration using DisplayPort Configure with `Select Configuration` programmed to USB, and the UFP_U may start to use USB immediately after receiving this command.

Code evidence:
- `User/USBPD/Src/usbpd_vdm_handler.c:15-23` builds every transmitted DP Status VDO through `USBPD_BuildDPStatusVDO()` and unconditionally sets `status_vdo.Bit.Enabled = 1u`.
- `User/USBPD/Src/usbpd_vdm_handler.c:287-315` uses that helper for every DisplayPort Status Update ACK.
- `User/USBPD/Src/usbpd_vdm_handler.c:346-348` handles a supported DP Configure request selecting USB Configuration by calling `USBPD_HPD_Disable()`, but it does not track that DP functionality is disabled.
- `User/USBPD/Src/usbpd_vdm_handler.c:265` sets the DP active-mode marker on Enter Mode, and `User/USBPD/Src/usbpd_vdm_handler.c:346-348` does not clear that active mode on USB Configuration, so a later valid Status Update while still in DP Alt Mode can receive a VDO with `Enabled = 1`.

Why this is non-compliant:
- After the DFP_U selects USB Configuration, DisplayPort functionality on the USB-C interface is disabled even though the DP Alt Mode bracket may remain active until Exit Mode. A subsequent DisplayPort Status response should report disabled DP functionality, but this firmware always reports `Enabled = 1`, incorrectly telling the DFP_U that DP functionality is enabled and operational.

## PD-R3.2-065 - HPD Attention can be sent before the initial DisplayPort Status exchange

Spec evidence:
- DisplayPort Alt Mode v2.0 Section 3.9.2.1 says that, when DisplayPort Alt Mode is enabled, the HPD-to-USB PD converter shall transmit the current HPD state as part of the initial DisplayPort Status Update Command exchange.
- DisplayPort Alt Mode v2.0 Section 3.9.2.3.1 repeats that, when DisplayPort Alt Mode is enabled, the current HPD state is transmitted as part of the initial DisplayPort Status exchange.
- DisplayPort Alt Mode v2.0 Section 5.2.3 says the DFP_U generally transmits a DisplayPort Status Update Command immediately after receiving the ACK to Enter Mode, and the UFP_U responds by transmitting its DisplayPort Status Update in the VDO.
- DisplayPort Alt Mode v2.0 Section 5.2.5 says a UFP_U uses USB PD Attention to signal to the DFP_U that there has been some change in the UFP_U's status since last reported.

Code evidence:
- `User/USBPD/Src/usbpd_vdm_handler.c:254-267` handles Enter Mode by marking DP Alt Mode active, calling `USBPD_HPD_EnterMode()`, and then ACKing Enter Mode.
- `User/USBPD/Src/usbpd_hpd.c:130-140` enables HPD event detection on Enter Mode, clears pending events, and sets `s_reported_valid = 0`.
- `User/USBPD/Src/usbpd_hpd.c:208-253` queues HPD high, low, or IRQ events whenever HPD is enabled, without checking whether the initial DisplayPort Status exchange has occurred.
- `User/USBPD/Src/usbpd_pe.c:202-204` calls `USBPD_VDM_TrySendAttention()` from the idle Policy Engine path.
- `User/USBPD/Src/usbpd_vdm_handler.c:147-156` gates Attention only on connection state, HPD enable state, and the presence of a queued HPD event; it does not check `USBPD_HPD_GetReportedValid()`.
- `User/USBPD/Src/usbpd_vdm_handler.c:184-185` sends the Attention and only then records the HPD state as reported, while `User/USBPD/Src/usbpd_vdm_handler.c:309` records the state after a Status Update ACK.

Why this is non-compliant:
- After Enter Mode is ACKed but before the DFP_U sends the initial DisplayPort Status Update Command, any HPD edge can be queued and transmitted by the idle path as an Attention. That reports an HPD change before the current HPD state has been established through the required initial DisplayPort Status exchange. Attention is for status changes since the last reported status, so sending it with no prior reported HPD baseline violates the DP Alt Mode HPD-to-USB PD ordering requirement.

## PD-R3.2-066 - UFP_U has no USB Billboard path when DisplayPort Alt Mode entry fails

Spec evidence:
- DisplayPort Alt Mode v2.0 Section 5.2.2 says that if the UFP_U responds to the Enter Mode VDM with a USB PD Responder NAK response, DisplayPort Alt Mode is not entered and the UFP_U shall expose a USB Billboard device.
- DisplayPort Alt Mode v2.0 Section 5.4 says the UFP_U shall present a USB 2.0 USB Billboard if the `tAMETimeout` timer times out before DisplayPort Alt Mode is entered.
- The UFP_U DisplayPort Alt Mode Discovery and Entry flow text says USB-C requires the UFP_U to present a USB Billboard device class if the UFP_U fails to receive and act on an Enter Mode Command request within the `tAMETimeout` timer period, and that the UFP_U shall await further commands from the DFP_U after presenting USB Billboard.

Code evidence:
- `User/USBPD/Src/usbpd_vdm_handler.c:257-260` returns a Responder NAK to an Enter Mode request whose DP SVID or Object Position does not match the local DP mode.
- `User/USBPD/Src/usbpd_vdm_handler.c:265-267` enters DP Alt Mode only for the valid Enter Mode path; the NAK path has no call to start a USB Billboard device or connect one to USB2 D+/D-.
- `User/USBPD/Src/usbpd_vdm_handler.c:204-215` advertises this product as Modal Operation capable and USB-device capable in Discover Identity, including USB2 and USB3.2 device capability.
- `User/USBPD/Src/usbpd_vdm.c:20-23` defines the product as a PD USB peripheral with full USB2 device capability and USB 3.2 device capability.
- `User/App/main.c:61-74` initializes clocks, debug UART, the PD timer, board IO, lane mode, and the USB PD PHY, but no USBFS device stack, Billboard descriptor set, Billboard connect path, or `tAMETimeout` timer.
- A repository search finds only the unused `USBPD_USB2_CAP_BILLBOARD_ONLY` enum in `User/USBPD/Inc/pd_vdm.h:112` and USBFS register/descriptor definitions under `Core/Inc`; there is no Billboard implementation or runtime trigger.

Why this is non-compliant:
- This UFP_U can explicitly fail DP Alt Mode entry by NAKing Enter Mode, and it can also remain outside DP Alt Mode indefinitely if the DFP_U never sends a usable Enter Mode request. In both cases the DP Alt Mode flow requires USB Billboard presentation, but the firmware only sends the VDM response or waits in its PD loop. The host therefore receives neither DP Alt Mode entry nor the required USB Billboard indication explaining the failed alternate-mode path.

## PD-R3.2-067 - Re-entering DP Configuration after USB Configuration leaves HPD disabled

Spec evidence:
- DisplayPort Alt Mode v2.0 Section 5.2.4 says the DFP_U may transmit a DisplayPort Configure Command at any time while in DisplayPort Alt Mode.
- The same section says the UFP_U may enable DisplayPort Alt Mode immediately after receiving a Configure Command and shall ACK a DP Configuration only after ensuring the reconfigured pins are connected to DisplayPort.
- The same section says it is not necessary for the DFP_U to exit DisplayPort Alt Mode to change the DisplayPort Configuration settings on the interface.
- DisplayPort Alt Mode v2.0 Section 3.9.2.1 says the HPD-to-USB PD converter timing mandates apply to USB-C DP Sink devices and that the HPD detector may monitor the HPD state so the detector can debounce and track the HPD signal's current state.
- DisplayPort Alt Mode v2.0 Section 5.2.5 says a UFP_U uses USB PD Attention to signal status changes and shall report its updated status in the VDO using the DisplayPort Status format.

Code evidence:
- `User/USBPD/Src/usbpd_vdm_handler.c:346-348` handles a supported DisplayPort Configure command selecting USB Configuration by calling `USBPD_HPD_Disable()`.
- `User/USBPD/Src/usbpd_hpd.c:143-146` implements `USBPD_HPD_Disable()` by calling `USBPD_HPD_Reset()`, and `User/USBPD/Src/usbpd_hpd.c:118-127` clears `s_enabled`, `s_logical_high`, the reported baseline, and all pending HPD events.
- `User/USBPD/Src/usbpd_vdm_handler.c:350-356` handles a later supported DisplayPort Configure command selecting DP Configuration by applying the VL171 pin assignment and taking an HPD snapshot, but it never calls `USBPD_HPD_EnterMode()` or otherwise re-enables HPD detection.
- `User/USBPD/Src/usbpd_vdm_handler.c:147-156` only sends Attention when `USBPD_HPD_IsEnabled()` is true, so all later HPD-triggered Attention messages are suppressed after the USB Configuration path disables HPD.
- `User/USBPD/Src/usbpd_hpd.c:153-170` returns status through `USBPD_HPD_ReadStatus()`, but with HPD disabled after reset the logical HPD state remains cleared rather than being re-established as the current debounced HPD state.

Why this is non-compliant:
- A DFP_U is allowed to switch a still-active DisplayPort Alt Mode session from USB Configuration back to DP Configuration without exiting and re-entering the mode. This firmware accepts that DP Configure command and ACKs it, but the HPD-to-USB PD converter remains disabled from the earlier USB Configuration command. The UFP_U can therefore stop reporting HPD changes and can report a stale low HPD state after it has claimed that the DisplayPort pins are configured again.

## PD-R3.2-068 - HPD_High can be reported before the required high-level debounce interval

Spec evidence:
- DisplayPort Alt Mode v2.0 Section 3.9.2 says HPD's logical state is unchanged during glitches on the HPD link, and `IRQ_HPD` is detected only when a high-to-low transition is followed by a low-to-high transition between 250 us and 2 ms later.
- DisplayPort Alt Mode v2.0 Section 3.9.2.1/Table 3-22 defines the `IRQ_HPD Pulse/Glitch Detection Threshold` as 0.25 ms, with the DP Standard taking precedence.
- DisplayPort Alt Mode v2.0 Figure 3-6 shows the HPD-to-USB PD converter queueing `HPD_High` only after the HPD signal has been high for greater than the `IRQ_HPD Pulse/Glitch Detection Threshold`.
- DisplayPort Alt Mode Table 5.6 says HPD State is reported after glitch filtering, IRQ_HPD filtering, and de-bouncing when applied.

Code evidence:
- `User/USBPD/Src/usbpd_hpd.c:6-7` defines only the low-pulse thresholds `USBPD_HPD_IRQ_MIN_US = 250` and `USBPD_HPD_UNPLUG_MIN_US = 2000`.
- `User/USBPD/Src/usbpd_hpd.c:208-253` handles HPD entirely from edge callbacks and elapsed low time; it has no timer or pending state that verifies a newly high HPD input remains high for at least 250 us before becoming logical HPD high.
- `User/USBPD/Src/usbpd_hpd.c:248-253` immediately sets `s_logical_high = 1` and `s_pending_high = 1` on any rising edge seen while the logical state is low.
- `User/USBPD/Src/usbpd_vdm_handler.c:147-185` later converts that pending high event directly into a DP Attention VDO with `HPDState = 1`.

Why this is non-compliant:
- A short high glitch shorter than the 250 us HPD pulse/glitch detection threshold while the converter is logically in `HPD_Low` can be queued and reported as `HPD_High`. The DP Alt Mode HPD-to-USB PD converter is required to keep the logical HPD state unchanged during glitches and only report `HPD_High` after the high level has met the required detection/debounce threshold.

## PD-R3.2-069 - A rejected Sink Request can be repeated unchanged

Spec evidence:
- USB PD R3.2 Section 7.9.2 says a `Request` Message shall be sent by a Sink in response to the most recent `Source_Capabilities` Message when in SPR Mode.
- The same section says a `Reject` Message signals that the Source is unable to meet the `Request`, either because the request is invalid or because the Source can no longer provide what it advertised.
- The same section says the Sink may send a different `Request` Message from the rejected one, but shall not repeat the same `Request` Message using the same RDO unless there has been a New Explicit Contract Negotiation, Data Role Swap, or Data Reset.

Code evidence:
- `User/USBPD/Src/usbpd_pe.c:91-99` constructs the fixed/variable RDO directly from the selected 5 V Source PDO current and constant flags, then copies that RDO into every outgoing `Request`.
- `User/USBPD/Src/usbpd_pe.c:161-164` handles a received `Reject` only by printing `REJECT received`; it does not store the rejected RDO, mark the Source offer as rejected, or require a changed request.
- `User/USBPD/Src/usbpd_pe.c:183-187` schedules `STA_TX_REQ` for every later `Source_Capabilities` Message.
- `User/USBPD/Src/usbpd_pe.c:69-104` then regenerates the same RDO whenever the same 5 V Source PDO is selected, with no check for a prior rejection and no guard for the required New Explicit Contract Negotiation, Data Role Swap, or Data Reset conditions.

Why this is non-compliant:
- If a Source rejects the firmware's 5 V fixed-supply `Request` and later sends the same `Source_Capabilities` again, this Sink can send the identical RDO again. USB PD allows a different follow-up request, but explicitly forbids repeating the same rejected RDO unless one of the listed reset/renegotiation events has occurred.

## PD-R3.2-070 - Transmitted Hard Reset does not run the required Sink transition-to-default recovery

Spec evidence:
- USB PD R3.2 Section 9.2.4.8 says that, on entry to `PE_SNK_Hard_Reset`, the Sink Policy Engine shall request generation of Hard Reset Signaling by the PHY Layer and increment `HardResetCounter`.
- The same section says the Sink Policy Engine shall transition to `PE_SNK_Transition_to_default` when the Hard Reset is complete.
- Section 9.2.4.9 says that, when Hard Reset Signaling is received or transmitted, the Sink Policy Engine shall transition from any state to `PE_SNK_Transition_to_default`.
- Section 9.2.4.9 also says that, on entry to `PE_SNK_Transition_to_default`, the Sink shall indicate to the Device Policy Manager that the Sink shall transition to default, request a reset of local hardware, request that the Port Data Role is set to UFP, and transition to `PE_SNK_Startup` when the Sink has reached the default level.

Code evidence:
- `User/USBPD/Src/usbpd_phy.c:173-192` treats a stable CC attach as connected, switches to `STA_SRC_CONNECT`, transmits `UPD_HARD_RESET`, and immediately re-enters RX mode.
- `User/USBPD/Src/usbpd_phy.c:188-192` has no transition into a Sink hard-reset state, no transition-to-default state, and no follow-up path that waits for the Sink to reach the default power level before starting the Sink Policy Engine again.
- A repository search finds no `HardResetCounter` implementation; the attach-time Hard Reset path therefore cannot increment the required counter or enforce the `nHardResetCount` limit.
- `User/USBPD/Src/usbpd_pe.c:21-30` is the only local PE reset helper, but the transmit-Hard-Reset path in `User/USBPD/Src/usbpd_phy.c:188-192` does not call it and does not request DPM/hardware transition-to-default actions.

Why this is non-compliant:
- Independent of whether the attach-time Hard Reset should have been sent, once the firmware transmits Hard Reset Signaling the Sink Policy Engine is required to execute the transition-to-default recovery sequence. This firmware only transmits the signaling and returns to RX mode, leaving the Sink without the required default-power recovery, local hardware reset request, data-role reset request, startup transition, or Hard Reset counter handling.

## PD-R3.2-071 - Initial DP Status can report raw HPD high without debounce or glitch filtering

Spec evidence:
- DisplayPort Alt Mode v2.0 Section 3.9.2 says HPD's logical state is unchanged during glitches on the HPD link.
- DisplayPort Alt Mode Section 3.9.2.1 says that, when DisplayPort Alt Mode is enabled, the HPD-to-USB PD converter shall transmit the current HPD state as part of the initial DisplayPort Status Update Command exchange.
- The same section says the HPD detector may monitor HPD outside the time that DisplayPort Alt Mode is enabled so the detector can perform HPD de-bouncing and track the HPD signal's current state.
- DisplayPort Alt Mode Figure 3-6 shows the HPD-to-USB PD converter queueing `HPD_High` only after the HPD signal has been high for greater than the `IRQ_HPD Pulse/Glitch Detection Threshold`.
- DisplayPort Alt Mode Table 5.6 says HPD State is reported after glitch filtering, IRQ_HPD filtering, and de-bouncing when applied.

Code evidence:
- `User/USBPD/Src/usbpd_hpd.c:130-140` enables HPD on Enter Mode by setting `s_logical_high = DP_HPD_IsHigh()` directly and clearing all pending events; it does not verify that the HPD input has been high for the required threshold.
- `User/USBPD/Src/usbpd_hpd.c:118-127` and `User/USBPD/Src/usbpd_hpd.c:143-146` disable/reset HPD tracking outside the active mode, so the detector does not maintain a debounced HPD baseline before Enter Mode.
- `User/USBPD/Src/usbpd_hpd.c:153-170` returns that raw `s_logical_high` value through `USBPD_HPD_ReadStatus()` when no pending event is present.
- `User/USBPD/Src/usbpd_vdm_handler.c:287-313` uses `USBPD_HPD_ReadStatus()` to build the UFP_U's response to the initial DisplayPort Status Update Command after Enter Mode.

Why this is non-compliant:
- If HPD is momentarily high due to a glitch or unsettled mechanical/electrical state at the moment Enter Mode enables HPD handling, the firmware can report `HPDState = 1` in the required initial DisplayPort Status exchange. The initial baseline is still a USB PD HPD report and must represent the converter's logical, filtered HPD state, not a raw GPIO sample.

## PD-R3.2-072 - Unexpected recognized non-VDM Data Messages are silently dropped

Spec evidence:
- USB PD R3.2 Section 7.1.1 defines a Protocol Error as including an Unexpected Message received during an AMS, and says the resulting recovery may be Soft Reset, Hard Reset, or no response depending on the case.
- Table 7.1, `Response to an incoming Message (except VDM)`, says an unexpected recognized and supported incoming message in `PE_SNK_Ready` shall cause a `Soft_Reset` Message, while an unexpected recognized and supported incoming message during an AMS shall cause `Soft_Reset` when power is not transitioning or Hard Reset signaling when power is transitioning.
- Table 7.1 also says unsupported or unrecognized non-VDM messages shall receive `Not_Supported`, so a received non-VDM Data Message cannot be acknowledged at the Protocol Layer and then silently discarded by the Policy Engine.
- USB PD Table 6.5 defines non-VDM Data Message types such as `Sink_Capabilities`, `Battery_Status`, `Source_Info`, and `Revision`; Table 7.4 defines those response messages as part of their corresponding AMSs.

Code evidence:
- `Core/Inc/ch32l103_usbpd.h:113-124` defines the non-VDM Data Message types `Request`, `Sink_Capabilities`, `Battery_Status`, `Alert`, `Get_Country_Info`, `Enter_USB`, `EPR_Request`, `EPR_Mode`, `Source_Info`, and `Revision`.
- `User/USBPD/Src/usbpd_pe.c:147-196` dispatches received messages only by `NumDO == 0` versus `NumDO > 0`; the Data Message branch handles only `DEF_TYPE_SRC_CAP` and `DEF_TYPE_VENDOR_DEFINED`.
- `User/USBPD/Src/usbpd_pe.c:196` uses `default: break` for all other Data Message types, and `User/USBPD/Src/usbpd_pe.c:199` then clears `USBPD_Control.Flag.Msg_Recvd`.
- `User/USBPD/Src/usbpd_pe.c:112-205` has no Policy Engine state that tracks an outstanding non-VDM Data Message response AMS, and has no branch that sends `Soft_Reset`, Hard Reset signaling, or `Not_Supported` after such a Data Message is received in the wrong state.
- `PD-R3.2-007` covers unsupported/unrecognized/reserved messages, `PD-R3.2-053` covers unexpected recognized Control responses, and `PD-R3.2-054` covers unexpected Structured VDM responses; this finding covers the remaining recognized non-VDM Data Message path.

Why this is non-compliant:
- A Port Partner can send a recognized non-VDM Data Message such as an unsolicited `Revision`, `Source_Info`, `Battery_Status`, or `Sink_Capabilities` response when this Sink has no matching AMS pending, or while another AMS is active. The firmware sends GoodCRC and then drops the message without classifying it as expected, unexpected, unsupported, or unrecognized. USB PD requires the Sink Policy Engine to run the Table 7.1 recovery path for unexpected recognized messages, or to send `Not_Supported` for unsupported/unrecognized messages, rather than losing the protocol event silently.

## PD-R3.2-073 - Get_Status is not answered with the required Status Extended Message

Spec evidence:
- USB PD R3.2 Section 6.3.18 says the `Get_Status` Message is sent by a Port using SOP to request the Port Partner's present status, and is used in the Get Status and Alert sequences.
- Section 6.5.3 says that, when sent to SOP, the `Status` Message returns the status of the Port's Port Partner and is used in the Get Status sequence.
- Section 9.2.11.2 says the Policy Engine shall transition to `PE_Give_Status` from `PE_SRC_Ready`, `PE_SNK_Ready`, or `PE_CBL_Ready` when a `Get_Status` Message is received.
- Section 9.2.11.2.1 says that, on entry to `PE_Give_Status`, the Policy Engine shall request the present status from the Device Policy Manager and then send a `Status` Message based on that information.

Code evidence:
- `Core/Inc/ch32l103_usbpd.h:102-103` defines `DEF_TYPE_GET_STATUS` as Control Message type `0x12` and separately defines the Extended-message `Status` type as `DEF_TYPE_GET_STATUS_R`.
- `User/USBPD/Src/usbpd_pe.c:147-176` dispatches incoming Control Messages but only handles `Soft_Reset`, `Accept`, `Reject`, `PS_RDY`, and `GoodCRC`; there is no `DEF_TYPE_GET_STATUS` case.
- `User/USBPD/Src/usbpd_pe.c:176` drops all other Control Messages through `default: break`, and `User/USBPD/Src/usbpd_pe.c:199` then clears the receive flag.
- All current transmit-header builders set `.Ext = 0` (`User/USBPD/Src/usbpd_pe.c:61`, `User/USBPD/Src/usbpd_pe.c:82`, `User/USBPD/Src/usbpd_vdm_handler.c:75`), and no code constructs or sends the Extended `Status` Message required for a `Get_Status` response.

Why this is non-compliant:
- A Source can query this Sink's present status with `Get_Status` while an Explicit Contract is in place. The firmware GoodCRCs that Control Message and then silently drops it instead of entering `PE_Give_Status`, asking the DPM for current status, and returning the required Extended `Status` Message.

## PD-R3.2-074 - DP Status and Configure requests do not enforce the required DP VDO payload

Spec evidence:
- DisplayPort Alt Mode v2.0 Section 5.2.3 says the DFP_U provides its latest DisplayPort Status Update in the VDO, the UFP_U responds by transmitting its DisplayPort Status Update in the VDO, and Table 5-6 defines that DisplayPort Status Update VDO.
- DisplayPort Alt Mode v2.0 Section 5.2.4 says the DisplayPort Configure Command uses the VDO containing the details of the requested configuration, and Table 5-8 defines that DisplayPort Configuration VDO.
- USB PD R3.2 Section 8.6 says a Structured VDM responder shall ACK only if it recognizes the SVID and is able to process the command at the expected time, and shall NAK when it recognizes the SVID but cannot process the Command Request or when a command parameter is invalid.

Code evidence:
- `User/USBPD/Src/usbpd_vdm_handler.c:287-313` handles `DisplayPort Status Update` by checking only the SVID. It logs the DFP_U Status VDO only when `last_header->Message_Header.NumDO > 1`, but it still ACKs the command when `NumDO == 1` and ignores any extra VDOs when `NumDO > 2`.
- `User/USBPD/Src/usbpd_vdm_handler.c:303-313` still calls `USBPD_HPD_ReadStatus()`, records the reported HPD baseline, and sends a Status ACK even when the incoming Status Update request did not contain the required DFP_U Status VDO.
- `User/USBPD/Src/usbpd_vdm_handler.c:317-359` handles `DisplayPort Configure` by NAKing `NumDO < 2`, but it never requires `NumDO == 2`; requests with extra trailing VDOs are accepted after reading only the first Configure VDO at `rx_buf[6]`.
- `User/USBPD/Src/usbpd_vdm_handler.c:343-359` can apply a VL171 pin assignment and send a Configure ACK for such an over-length command.
- `PD-R3.2-030` covers invalid `NumDO` for the standard Discover SVIDs, Discover Modes, Enter Mode, and Exit Mode SVDM commands; this finding covers the separate DP_SID-specific Status Update and Configure commands.

Why this is non-compliant:
- The DP_SID-specific commands have a defined single DP VDO payload. This firmware can treat a malformed Status Update with no DFP_U Status VDO as successful, consuming or recording HPD state as though a valid status exchange occurred. It can also accept and act on an over-length Configure request whose trailing data objects are outside the defined DP Configure command format. A malformed DP command request must not be acknowledged and acted on as a valid DisplayPort Alt Mode command.

## PD-R3.2-075 - Standard SVDM commands advertise the pre-R3.1 Structured VDM minor version

Spec evidence:
- USB PD R3.2 Table 6.33 defines Structured VDM Version Minor for Command values 0 through 15: `00b` is Version 2.0 for ports implemented prior to USB PD Revision 3.1 Version 1.6, while `01b` is Version 2.1 for ports implemented starting with USB PD Revision 3.1 Version 1.6.
- USB PD R3.2 Section 6.4.12.2.1 says the Structured VDM Version Major field shall be set to `01b` for Version 2.x and the Minor field shall be set as appropriate based on whether the Port is implemented to USB PD Revision 3.1 Version 1.6 or newer.
- USB PD R3.2 Section 8.5.1 says the Discover Identity SVDM version fields are used to determine the highest common Structured VDM version, and that each Port Partner shall continue to use that common Structured VDM version when initiating Structured VDMs until Detach, Hard Reset, or Error Recovery.

Code evidence:
- `User/USBPD/Src/usbpd_pe.c:18` initializes SOP communication as PD 3.x by default, and transmitted headers use SpecRev `10b` when `USBPD_Control.Flag.PD_Version` is set (`User/USBPD/Src/usbpd_pe.c:57-59`, `User/USBPD/Src/usbpd_vdm_handler.c:71-73`).
- The local protocol data headers are explicitly written against USB PD R3.2 (`User/USBPD/Inc/pd_pdo.h:7`, `User/USBPD/Inc/pd_rdo.h:7`, `User/USBPD/Inc/pd_vdm.h:5`).
- `User/USBPD/Inc/pd_vdm.h:35-36` defines both `USBPD_SVDM_MINOR_2P0` and `USBPD_SVDM_MINOR_2P1`, so the implementation has a representation for Version 2.1.
- `User/USBPD/Src/usbpd_vdm_handler.c:118-125` forces every Structured VDM response, including standard commands such as Discover Identity, Discover SVIDs, Discover Modes, Enter Mode, and Exit Mode, to `USBPD_SVDM_MINOR_2P0`.
- `User/USBPD/Src/usbpd_vdm_handler.c:128-144` also constructs locally initiated Attention requests, another standard SVDM command, with `USBPD_SVDM_MINOR_2P0`.

Why this is non-compliant:
- For a USB PD R3.2 implementation, standard Structured VDM commands in the 0 through 15 command range must advertise/use the Version 2.1 minor value unless a lower common version has actually been negotiated with the Port Partner. This firmware hard-codes Version 2.0 for those standard SVDM commands, which presents the Port as an older pre-USB PD Revision 3.1 Version 1.6 implementation and prevents correct common Structured VDM version use for later locally initiated commands such as Attention. `PD-R3.2-011` covers the missing negotiation/matching logic; this finding covers the separate fixed local minor-version value being too old for an R3.2 implementation.

## PD-R3.2-076 - Structured VDM requests with invalid version fields can be ACKed

Spec evidence:
- USB PD R3.2 Table 6.33 defines the Structured VDM Header and says that, for Command values 0 through 15, Structured VDM Version Minor values `10b` and `11b` are invalid and shall not be used.
- DisplayPort Alt Mode v2.0 Table 5-4 defines the DP_SID Structured VDM Header and says bits 12:11 are reserved and always `00b`; it also defines Structured VDM Version `00b` as Version 1.0, shall not be used, `01b` as Version 2.0, and all other values as reserved.
- USB PD R3.2 Section 8.6 says a Structured VDM Responder shall return NAK when a VDO in the Command Request contains a field that is invalid.

Code evidence:
- `User/USBPD/Src/usbpd_vdm_handler.c:371-377` copies the incoming VDM Header from the first Data Object into `vdm_header`.
- `User/USBPD/Src/usbpd_vdm_handler.c:383-390` dispatches every Structured VDM request to `USBPD_HandleStructuredVDMRequest()` without validating `StructuredVDMVersionMajor` or `StructuredVDMVersionMinor`.
- `User/USBPD/Src/usbpd_vdm_handler.c:193-267` can ACK standard Discover Identity, Discover SVIDs, Discover Modes, and Enter Mode requests based on only command-specific SVID/Object Position checks, even when the request used invalid standard-command minor values `10b` or `11b`.
- `User/USBPD/Src/usbpd_vdm_handler.c:287-359` can ACK DP Status Update and DP Configure requests, and can apply the DP Configure mux, without rejecting nonzero reserved bits 12:11 or reserved/forbidden DP Structured VDM Version values.
- `User/USBPD/Src/usbpd_vdm_handler.c:118-125` overwrites version fields in the outgoing response, but that happens after the malformed request has already been accepted and processed as a valid command.

Why this is non-compliant:
- The Structured VDM Header is the first VDO in a VDM Command Request. Requests that carry invalid standard SVDM minor-version values, or reserved DP_SID version/reserved bits, contain invalid VDO fields and must be NAKed. This firmware treats those malformed requests as valid discovery, mode-entry, status, or configure commands, so an invalid request can advance modal state or change the DP mux instead of being rejected.

## PD-R3.2-077 - Enter Mode can be ACKed without a prior Discover Modes result

Spec evidence:
- USB PD R3.2 Section 6.4.12.6 says the `Enter Mode` Object Position field shall indicate the Alternate Mode in the `Discover Modes` Command to which the VDO refers.
- USB PD R3.2 Table 6.33 says that, for `Enter Mode`, Object Position values greater than the number of VDOs supplied by the `Discover Modes ACK` are invalid.
- USB PD R3.2 Section 8.7.2 says the result of the Discovery Process is that both the Initiator and Responder identify the Modes they mutually support, and that the DFP may initiate the Enter Mode Process after it has successfully completed the Discovery Process with that Responder.
- USB PD R3.2 Section 8.6 says a Structured VDM responder shall ACK only if it recognizes the SVID and is able to process the command at the expected time, and shall NAK when it recognizes the SVID but cannot process the Command Request or when a VDO field is invalid.

Code evidence:
- `User/USBPD/Src/usbpd_vdm_handler.c:235-250` sends a `Discover Modes ACK` for the DP SVID, but it does not store that discovery has been completed for the current PD connection or Port Partner.
- `User/USBPD/Src/usbpd_vdm_handler.c:254-267` handles `Enter Mode` by checking only that the request SVID matches `USBPD_DP_ALT_MODE.svid` and that Object Position equals `USBPD_DP_ALT_MODE.object_position`.
- `User/USBPD/Src/usbpd_vdm_handler.c:265-267` then marks DP Alt Mode active, enables HPD, and sends an `Enter Mode ACK` even if no `Discover Modes ACK` has been sent in the current attach/contract.
- `User/USBPD/Src/usbpd_vdm_handler.c:371-390` dispatches every Structured VDM request directly to the request handler and has no discovery-state gate for `Enter Mode`.

Why this is non-compliant:
- The `Enter Mode` Object Position is not a standalone constant; it is an index into the Mode VDO list previously supplied by `Discover Modes ACK`. A DFP can send `Enter Mode` for DP object position 1 without first performing Discover Modes in this connection, and this firmware will still enter DP Alt Mode and ACK the request. At that point no Mode VDO list has been supplied for the Object Position to reference, so the request is not processable at the expected time and its Object Position is not backed by a valid prior discovery result. The responder should NAK such an out-of-sequence mode-entry request instead of advancing modal state.

## PD-R3.2-078 - Sink can mirror an invalid Source PDO current into its Request

Spec evidence:
- USB PD R3.2 Section 6.4.1.1 says a `Source_Capabilities` Message contains 1 to 7 PDOs and that the `vSafe5V` Fixed Supply PDO shall always be the first PDO.
- USB PD R3.2 Table 6.8 defines the Fixed 5 V Source PDO `Maximum Current` field as 10 mA units, with values 0 through 500 allowed and all other values invalid.
- USB PD R3.2 Section 6.4.2 says a `Request` Message shall contain a single RDO that identifies the PDO being requested.
- USB PD R3.2 Table 6.19 says the Fixed/Variable RDO `Operating Current` field shall not exceed the `Maximum Current` field of the `Source_Capabilities` Message.
- USB PD R3.2 Section 6.4.2.1.6 and Section 7.9.2.1 say that, when the offered Source Capabilities do not satisfy the Sink's requirements, the Sink shall make a valid Request from the offered Source Capabilities and set the Capability Mismatch bit.

Code evidence:
- `User/USBPD/Src/usbpd_pe.c:183-187` schedules `STA_TX_REQ` for every received `Source_Capabilities` Message and only logs the PDOs through `USBPD_PDO_Analyse()`.
- `User/USBPD/Src/usbpd_helper.c:153-188` selects the first PDO whose type is Fixed, whose voltage field is 5 V, and whose `USBCommCapable` bit is set; it does not require that the PDO is the first `vSafe5V` PDO and does not validate that `MaxCurrentIn10mA <= 500`.
- `User/USBPD/Src/usbpd_pe.c:86-93` reads the selected Source PDO and copies `fpdo.Bit.MaxCurrentIn10mA` directly into both the Fixed/Variable RDO `MaxOperatingCurrentIn10mA` and `OperatingCurrentIn10mA` fields.
- `User/USBPD/Src/usbpd_pe.c:91-99` then transmits that RDO as a `Request` without rejecting the malformed Source Capabilities, clamping the current field, or setting `CapabilityMismatch`.
- `User/USBPD/Inc/pd_pdo.h:61` and `User/USBPD/Inc/pd_rdo.h:47-48` model both the Source PDO current and RDO current fields as unconstrained 10-bit values, so values greater than the specification's 500-unit maximum can be represented and copied unchanged.

Why this is non-compliant:
- A malformed Source can advertise a Fixed 5 V PDO with `Maximum Current` greater than 500, or put such a 5 V PDO in a later object position. The firmware can select that invalid PDO and send a `Request` whose operating current mirrors the invalid advertised value. The Sink is required to make a valid Request from valid offered capabilities; it must not turn an invalid Source PDO field into its own invalid power request.

## PD-R3.2-079 - Receive/main-loop race can process a message without sending GoodCRC

Spec evidence:
- USB PD R3.2 Section 7.31.1 says the Protocol Layer receiving a Message shall respond with a `GoodCRC` Message within `tTransmit`, measured from the received Message EOP to the first bit of the GoodCRC Preamble.
- USB PD R3.2 Section 9.1.2.3.1 says `PRL_Rx_Wait_for_PHY_Message` shall transition to `PRL_Rx_Send_GoodCRC` when a Message is passed up from the PHY Layer.
- USB PD R3.2 Section 9.1.2.3.3 says that, on entry to `PRL_Rx_Send_GoodCRC`, the Protocol Layer shall construct a `GoodCRC` Message and request the PHY Layer to transmit it, then transition to MessageID checking only after the GoodCRC has been passed to the PHY Layer.

Code evidence:
- `User/USBPD/Src/usbpd_pe.c:112-140` runs the current `USBPD_Control.PD_State` first, including `STA_TX_GOODCRC`, before checking `USBPD_Control.Flag.Msg_Recvd`.
- `User/USBPD/Src/usbpd_pe.c:141-198` then processes any received message and may overwrite the state with `STA_TX_REQ` for `Source_Capabilities`, `STA_VDM` for VDMs, `STA_IDLE` through `USBPD_PE_Reset()` for `Soft_Reset`, or leave the state unchanged for other messages.
- `User/USBPD/Src/usbpd_pe.c:207-222` is an interrupt handler that can run asynchronously during `USBPD_PE_Run()`. For every non-GoodCRC SOP message it records the header, switches the state to `STA_TX_GOODCRC`, and sets `Msg_Recvd`.
- There is no critical section, pending-GoodCRC flag, or immediate interrupt-level GoodCRC transmit that forces `STA_TX_GOODCRC` to run before the message-processing block consumes `Msg_Recvd`.
- Therefore, if `USBPD_IRQHandler()` receives a non-GoodCRC message after the state switch at `USBPD_PE_Run()` has already executed but before the `Msg_Recvd` block runs, the same main-loop iteration can process the message, overwrite `STA_TX_GOODCRC`, clear `Msg_Recvd`, and never call `STA_Tx_GoodCRC()` for that received packet.

Why this is non-compliant:
- The USB PD receive state machine sends `GoodCRC` before MessageID checking and before passing the message to the Policy Engine. This firmware represents GoodCRC as a normal main-loop state that can be preempted and overwritten by later message handling. A valid incoming `Source_Capabilities`, VDM, `Soft_Reset`, or other non-GoodCRC message can therefore be acknowledged at neither the required time nor at all, causing the Port Partner to retry or time out even though the local Policy Engine may already have acted on the unacknowledged message. `PD-R3.2-018` covers the missing `tTransmit` deadline; this finding covers the separate race that can skip GoodCRC transmission entirely.

## PD-R3.2-080 - Enter Mode ACK loss can leave the UFP in DP Alt Mode while the DFP remains in USB

Spec evidence:
- USB PD R3.2 Section 8.6 says a Structured VDM AMS is completed, and any applicable transition to the requested functionality is made, when the Responder's Command response has been successfully transmitted.
- Section 8.6.4 says that, if the Responder ACKs an `Enter Mode` Command Request, the Responder shall enter the Alternate Mode before sending the ACK, while the Initiator enters the Alternate Mode on reception of the ACK.
- The same section says successful transmission of the Message confirms to the Responder that the Initiator will enter an Active Mode, and that if the Initiator fails to receive a response within `tVDMWaitModeEntry` it shall not enter the Alternate Mode but return to USB operation.
- Section 9.1.2.2.1.5 says the Protocol Layer waits for a `GoodCRC` response after passing a transmitted Message to the PHY Layer.
- Section 9.1.2.2.1.6 says the Protocol Layer transitions to `PRL_Tx_Message_Sent` only when the received `GoodCRC` MessageID matches the `MessageIDCounter`.
- Section 9.1.2.2.1.7 says `PRL_Tx_Message_Sent` increments the MessageIDCounter and informs the Policy Engine that the Message has been sent.

Code evidence:
- `User/USBPD/Src/usbpd_vdm_handler.c:254-267` handles `Enter Mode` by setting the DP active marker (`Mode_Try_Cnt |= 0x80`), enabling HPD through `USBPD_HPD_EnterMode()`, and only then sending the `Enter Mode ACK`.
- `User/USBPD/Src/usbpd_vdm_handler.c:91-97` sends a VDM response through `USBPD_Phy_TxPacket()` and immediately increments `USBPD_Control.Msg_ID`.
- `User/USBPD/Src/usbpd_phy.c:18-61` waits only for local `IF_TX_END` in synchronous mode, clears it, and re-enters receive mode; it does not wait for a matching `GoodCRC`, return a transmit-success result to the VDM responder, or report a `Message Sent` event back to the Policy Engine.
- `User/USBPD/Src/usbpd_pe.c:202-204` can then call `USBPD_VDM_TrySendAttention()` from the idle path, and `User/USBPD/Src/usbpd_vdm_handler.c:147-156` allows Attention whenever the port is connected, HPD is enabled, and an HPD event is queued.

Why this is non-compliant:
- The Enter Mode responder is required to enter the mode before sending the ACK, but successful ACK transmission is the confirmation that the DFP Initiator will also enter the Active Mode. If the `Enter Mode ACK` is lost or not GoodCRCed, the DFP will time out and return to USB operation, while this firmware has no way to detect that failure and continues with DP Alt Mode active and HPD/Attention enabled. `PD-R3.2-003` covers the generic missing GoodCRC/retry/MessageID behavior; this finding covers the separate modal-state consequence where the UFP keeps operating as though the Enter Mode AMS succeeded even when the ACK was not successfully transmitted.

## PD-R3.2-081 - HPD events are removed from the queue before the USB PD report is successfully sent

Spec evidence:
- DisplayPort Alt Mode v2.0 Section 3.9.2.1 says the HPD-to-USB PD converter shall transmit the current HPD state in the initial DisplayPort Status Update exchange and refers to Section 3.9.2.3 for message queuing mandates.
- DisplayPort Alt Mode v2.0 Section 3.9.2.3.1 says `IRQ_HPD`, `HPD_Low`, and `HPD_High` events are HPD events in the HPD-to-USB PD converter queue, and defines when queued events shall be transmitted or may be discarded.
- The same section says that, when `IRQ_HPD` is detected while a previous `IRQ_HPD` is in the queue, the converter shall transmit DisplayPort Status Update or USB PD Attention Commands for both events, and that only `IRQ_HPD` events detected while two `IRQ_HPD` events are already in the queue may be discarded.
- USB PD R3.2 Sections 9.1.2.2.1.5 through 9.1.2.2.1.7 say a transmitted Message is reported to the Policy Engine as sent only after the Protocol Layer receives a matching `GoodCRC`.

Code evidence:
- `User/USBPD/Src/usbpd_hpd.c:83-109` implements `USBPD_HPD_PopPendingEvent()` by copying one pending HPD event into the caller's structure and immediately clearing `s_pending_low`, `s_pending_high`, or `s_pending_irq`.
- `User/USBPD/Src/usbpd_hpd.c:153-166` calls `USBPD_HPD_PopPendingEvent()` from `USBPD_HPD_ReadStatus()`, so a pending HPD event can be removed while preparing a DisplayPort Status Update response.
- `User/USBPD/Src/usbpd_hpd.c:177-189` calls the same pop helper from `USBPD_HPD_PollEvent()`, so a pending HPD event is removed before the Attention transmission path starts.
- `User/USBPD/Src/usbpd_vdm_handler.c:156-185` sends Attention after `USBPD_HPD_PollEvent()` has already removed the event, then records the HPD level as reported through `USBPD_HPD_RecordReported()`.
- `User/USBPD/Src/usbpd_vdm_handler.c:303-314` reads/pops HPD status, records the HPD level as reported, and only then sends the DisplayPort Status Update ACK.
- `User/USBPD/Src/usbpd_vdm_handler.c:83-97` and `User/USBPD/Src/usbpd_phy.c:18-61` provide no matching-GoodCRC result to either path; transmission waits only for local `IF_TX_END` and the VDM sender increments `Msg_ID` immediately.

Why this is non-compliant:
- A queued HPD event is not successfully transmitted merely because firmware copied it into a pending Attention or Status ACK payload. If that USB PD Message is not acknowledged by a matching `GoodCRC`, the DFP_U has not received the HPD update and the converter must not silently lose the queued event. This firmware clears the event before the Protocol Layer can prove message delivery, and it can also mark the HPD level as reported before the report was successfully sent. A lost Attention or Status ACK can therefore discard a required `IRQ_HPD`, `HPD_Low`, or `HPD_High` update even though the DP Alt Mode queueing rules only allow specific event-discard cases. `PD-R3.2-003` covers the missing generic GoodCRC retry machinery; this finding covers the separate HPD converter consequence where required queued events are consumed before the USB PD report has actually been delivered.

## PD-R3.2-082 - Multi-function mode rejects the mandatory associated DP-only Configure pin assignment

Spec evidence:
- DisplayPort Alt Mode v2.0 Table 5-5 note c says a system supporting DisplayPort on a USB-C connector and supporting Multi-function Mode, simultaneous USB SuperSpeed and DisplayPort, shall offer both the multi-function pin assignment and the associated DP-only pin assignment.
- The same note identifies Pin Assignment C as the associated DP-only pin assignment for multi-function Pin Assignment D, and says the system shall offer both pin assignments even if it supports only one or two DP lanes.
- DisplayPort Alt Mode v2.0 Section 5.2.4 says a DFP_U may transmit a DisplayPort Configure Command at any time while in DisplayPort Alt Mode, and Table 5-8 defines Pin Assignment C (`04h`) and Pin Assignment D (`08h`) as selectable Configure UFP_U pin assignments.
- Section 5.2.4 further says a UFP_U supporting DisplayPort Alt Mode and Multi-function Mode may be instructed by the DFP_U to configure the related DisplayPort-only pin assignment, and shall ensure the normally USB SuperSpeed channels that are not used by that pin assignment are in USB Safe State when instructed to do so.

Code evidence:
- `User/USBPD/Inc/usbpd_vdm.h:8-10` defines `USBPD_DP_LANE_MODE_2LANE` as Pin Assignment D, 2-lane DP plus USB3.
- `User/App/main.c:42-48` selects `USBPD_DP_LANE_MODE_2LANE` by default unless the startup key is pressed.
- `User/USBPD/Src/usbpd_vdm.c:62-69` maps the current lane mode to exactly one `pin_assignment` and writes that single value into both `USBPD_DP_ALT_MODE.mode_vdo.Bit.UFP_DPinAssignments` and `USBPD_DP_ALT_MODE.supported_configurations[1].Bit.PinAssignment`.
- In the default 2-lane mode, `USBPD_DP_SetLaneMode()` therefore changes the only supported DP Configure entry from Pin Assignment C to Pin Assignment D.
- `User/USBPD/Src/usbpd_vdm_handler.c:42-58` accepts a received DP Configure VDO only if it exactly equals one of the entries in `USBPD_DP_ALT_MODE.supported_configurations`.
- `User/USBPD/Src/usbpd_vdm_handler.c:336-340` sends a Structured VDM NAK when `USBPD_IsSupportedDPConfigure(config_vdo)` rejects the Configure VDO.

Why this is non-compliant:
- In the default 2-lane/multi-function configuration, this UFP_U supports and selects Pin Assignment D but removes the associated DP-only Pin Assignment C from the accepted Configure set. A DFP_U that instructs the UFP_U to switch from multi-function Pin Assignment D to the required associated DP-only Pin Assignment C receives a NAK, even though the DP Alt Mode rules require multi-function systems to offer and handle that associated DP-only configuration. `PD-R3.2-059` covers the incomplete Discover Modes capability advertisement; this finding covers the separate Configure responder behavior that rejects the mandatory associated DP-only pin assignment.

## PD-R3.2-083 - DP Sink configuration can complete without the required HPD High Attention

Spec evidence:
- DisplayPort Alt Mode v2.0 Section 4.10.2 says a UFP_U that is a DP Sink device shall transmit a USB PD Attention Command request with a DisplayPort Status Update VDO with HPD State High after receiving a DisplayPort Configure Command to configure the UFP_U as a DP Sink device.
- The same section says the DP Source device shall transmit an AUX transaction after receiving the DisplayPort Status Update VDO with HPD State High.
- DisplayPort Alt Mode v2.0 Section 5.2.4 says the DFP_U may transmit a DisplayPort Configure Command at any time while in DisplayPort Alt Mode, and that the UFP_U shall respond with a USB PD Responder ACK after ensuring the reconfigured pins are connected to DisplayPort.
- DisplayPort Alt Mode v2.0 Section 5.2.5 says a UFP_U may transmit a USB PD Attention Command request after entering DisplayPort Alt Mode and shall do so as soon as possible after its status changes.

Code evidence:
- `User/USBPD/Src/usbpd_vdm.c:36-40` declares this port as a DP Sink/UFP_D, and `User/USBPD/Src/usbpd_vdm.c:51-53` defines the accepted DP Configure object as `USBPD_DP_SELECT_UFP_D_SINK`.
- `User/USBPD/Src/usbpd_vdm_handler.c:317-359` handles a supported DisplayPort Configure request. In the DP Configuration branch it applies the pin assignment and takes an HPD snapshot, but it does not call `USBPD_SendDPAttention()`, queue an HPD event, or otherwise schedule the required Attention.
- `User/USBPD/Src/usbpd_vdm_handler.c:352-359` calls `VL171_ApplyDPPinAssignment(config_vdo)`, reads `USBPD_HPD_GetSnapshot()`, prints that snapshot, and then sends only the Configure ACK.
- `User/USBPD/Src/usbpd_vdm_handler.c:147-185` sends Attention only when `USBPD_HPD_PollEvent()` returns a pending HPD edge event.
- `User/USBPD/Src/usbpd_hpd.c:130-140` enables HPD handling on Enter Mode by sampling the current raw HPD level and clearing all pending HPD events, and `User/USBPD/Src/usbpd_hpd.c:172-175` implements `USBPD_HPD_GetSnapshot()` as a read-only raw snapshot that does not create a pending HPD event.

Why this is non-compliant:
- If HPD is already high when the DFP_U configures this UFP_U as a DP Sink, the firmware ACKs the Configure command after applying the mux but does not transmit the required HPD High Attention. Because Enter Mode and the Configure path clear or only sample the HPD state rather than queueing a report, no later Attention is generated unless a new HPD edge occurs. The DP Source can therefore complete configuration without receiving the HPD High DisplayPort Status VDO that the DP Alt Mode flow requires before AUX activity. `PD-R3.2-065` covers premature Attention before the initial Status exchange, and `PD-R3.2-081` covers queued HPD events being consumed before successful USB PD delivery; this finding covers the separate missing Attention after a successful DP Sink Configure when HPD is already high.

## PD-R3.2-084 - Repeated Enter Mode is ACKed while the DP mode is already active

Spec evidence:
- USB PD R3.2 Section 8.6 says a Responder shall ACK a Structured VDM request only if it recognizes the SVID and is able to process the request at the expected time, and shall NAK when it recognizes the SVID but cannot process the Command Request.
- Section 8.7.2 says that, once an Alternate Mode is entered, the device shall remain in that Active Mode until the Exit Mode Command is successful.
- Section 9.2.25.1 says the UFP Structured VDM Enter Mode state applies when an Enter Mode request is received from the DFP, and note 1 says the UFP is required to be in USB operation or USB Safe State at that point.
- Section 9.2.25.1.1 says the UFP Policy Engine shall request the DPM to evaluate the Enter Mode request and enter the indicated Mode only if the request is acceptable; otherwise it transitions to the Enter Mode NAK path.

Code evidence:
- `User/USBPD/Src/usbpd_vdm_handler.c:254-267` handles every DP `Enter Mode` request by checking only the SVID and Object Position, setting the DP active marker (`Mode_Try_Cnt |= 0x80`), calling `USBPD_HPD_EnterMode()`, and sending an Enter Mode ACK.
- That path does not check whether `Mode_Try_Cnt` already marks DP Alt Mode active, so a second `Enter Mode` request for the same DP object position is processed and ACKed before any `Exit Mode` has succeeded.
- `User/USBPD/Src/usbpd_vdm_handler.c:271-276` clears the active marker only in the `Exit Mode` path.
- `User/USBPD/Src/usbpd_hpd.c:130-140` implements `USBPD_HPD_EnterMode()` by resetting the reported HPD baseline and clearing all pending HPD events through `USBPD_HPD_ClearPendingEvents()`.
- `User/USBPD/Src/usbpd_hpd.c:42-48` clears pending `HPD_High`, `HPD_Low`, and `IRQ_HPD` events.

Why this is non-compliant:
- After a successful DP Enter Mode ACK, this UFP is no longer in the pre-entry USB operation or USB Safe State for that mode; it is already in an Active Mode that must persist until a successful Exit Mode or an unmanaged termination. A repeated Enter Mode request for the same active DP mode is therefore not processable at the expected time and should be rejected rather than ACKed as a fresh mode entry. This firmware ACKs the repeated request and reinitializes the HPD converter, which can also discard HPD events that were required to be reported during the already-active mode. `PD-R3.2-077` covers Enter Mode without a prior Discover Modes result, and `PD-R3.2-080` covers ACK transmission failure after entering mode; this finding covers the separate case where an already-active DP mode can be re-entered and reset without a successful Exit Mode.

## PD-R3.2-085 - Detach can leave a stale received message that is processed after the Port Pair is gone

Spec evidence:
- The USB PD glossary defines a `Port Pair` as two Attached PD Capable Ports and defines `Detach` as mechanical unjoining of the Port Pair by removal of the cable.
- USB PD R3.2 Section 9 state-diagram notes define `PD Connected` as the Port Partners actively communicating and say the Port Partners remain PD Connected until the connector is able to identify a Detach.
- Section 9.2.4.2 says the Sink Policy Engine waits in `PE_SNK_Discovery` until the DPM reports VBUS present, then Section 9.2.4.3 waits in `PE_SNK_Wait_for_Capabilities` for `Source_Capabilities`.
- Section 9.2.4.4 says the Sink first enters `PE_SNK_Evaluate_Capability` when it receives `Source_Capabilities` from the Source, at which point it knows it is Attached to and communicating with a PD Capable Source.
- Section 7.9.2 says a `Request` Message shall be sent by a Sink in response to the most recent `Source_Capabilities` Message when in SPR Mode.

Code evidence:
- `User/USBPD/Src/usbpd_pe.c:213-222` records the received SOP header/payload, schedules `STA_TX_GOODCRC`, and sets `USBPD_Control.Flag.Msg_Recvd = 1`.
- On Detach, `User/USBPD/Src/usbpd_phy.c:153-158` only clears `Connected`, calls the detach callback, and switches to `STA_DISCONNECT`; it does not clear `Msg_Recvd`, `last_rx_header`, `pe_rx_buf`, or any pending policy-engine message state.
- `User/USBPD/Src/usbpd_pe.c:112-143` handles `STA_DISCONNECT` by only breaking out of the state switch, then still processes `USBPD_Control.Flag.Msg_Recvd` in the same run.
- `User/USBPD/Src/usbpd_pe.c:183-187` schedules `STA_TX_REQ` for a latched `Source_Capabilities` message without checking whether the port is still attached or PD Connected.
- `User/USBPD/Src/usbpd_pe.c:69-104` sends the resulting `Request` from `STA_Req()` without checking `USBPD_Control.Flag.Connected`, VBUS present, or whether the `Source_Capabilities` offer still belongs to an attached Port Partner.

Why this is non-compliant:
- If a `Source_Capabilities` packet is received and latched, then Detach is identified before the main loop consumes `Msg_Recvd`, the firmware can still process that stale packet after `Connected` has been cleared and schedule/send a `Request` based on the old RX buffer. After Detach there is no attached Port Pair and no PD Connected Port Partner whose capabilities can be negotiated. A Sink must restart from the attachment/VBUS/capability-wait sequence for a new connection rather than letting a stale pre-detach receive event drive a new post-detach power Request. `PD-R3.2-021` covers stale Alternate Mode/mux state across Detach; this finding covers the separate pending-message path that can transmit a PD Request after the Port Pair has already been detached.

## PD-R3.2-086 - HPD Attention can interrupt an unfinished Power Negotiation AMS

Spec evidence:
- The glossary defines an Atomic Message Sequence as a fixed sequence of Messages that must complete before other messages are allowed to be sent.
- USB PD R3.2 Section 7.9 defines Power Negotiation (SPR) as an AMS; Section 7.9.2 says the Sink sends a `Request`, the Source sends `Accept` or `Reject`, and Section 7.9.3 says the Source sends `PS_RDY` when the power supply reaches the desired operating condition.
- Section 9.2.4.5 says `PE_SNK_Select_Capability` shall send the `Request`, initialize and run `SenderResponseTimer`, and remain in that negotiation flow until `Accept`, `Reject`, `Wait`, or timeout drives the defined transition.
- Section 9.2.4.6 says `PE_SNK_Transition_Sink` shall run `PSTransitionTimer` and transition to `PE_SNK_Ready` only when `PS_RDY` is received from the Source.
- Table 7.6 covers messages that may not be part of an AMS and lists `Attention (SVDM)` separately from AMS messages.

Code evidence:
- `User/USBPD/Src/usbpd_vdm_handler.c:266` enables HPD handling when a DP `Enter Mode` request is ACKed, so later HPD changes can drive locally initiated Attention messages.
- `User/USBPD/Src/usbpd_pe.c:183-187` handles any received `Source_Capabilities` message by scheduling `STA_TX_REQ`, even while DP Alt Mode/HPD handling may already be active under an existing contract.
- `User/USBPD/Src/usbpd_pe.c:69-104` sends the resulting `Request`, increments the local MessageID, and immediately switches back to `STA_IDLE`; it does not stay in a Select/Transition state waiting for `Accept`, `Reject`, `Wait`, `PS_RDY`, or timeout.
- `User/USBPD/Src/usbpd_pe.c:202-204` calls `USBPD_VDM_TrySendAttention()` whenever `Msg_Recvd` is clear and `PD_State == STA_IDLE`.
- `User/USBPD/Src/usbpd_vdm_handler.c:147-184` sends a DP Attention whenever the port is connected, HPD is enabled, and `USBPD_HPD_PollEvent()` returns a queued HPD event; it has no gate for an outstanding Power Negotiation AMS.

Why this is non-compliant:
- During a new Source-Capabilities-driven negotiation while DP Alt Mode is active, the firmware can send the Sink `Request`, return to idle immediately, and then transmit an HPD Attention before the Source has responded with `Accept` and `PS_RDY` or ended the negotiation with `Reject`/`Wait`. That inserts an unrelated DP Attention into the fixed Power Negotiation AMS. `PD-R3.2-005` covers the missing Select/Transition/Ready state machine itself, and `PD-R3.2-014` covers SinkTxOK collision avoidance for Attention; this finding covers the separate AMS interleaving where Attention is allowed before the Power Negotiation sequence has completed.

## PD-R3.2-087 - Structured VDM requests with reserved Header bit 5 can be ACKed and acted upon

Spec evidence:
- USB PD R3.2 Table 6.33 defines Structured VDM Header bit 5 as `Reserved`; it is a static field and the receiver shall ignore this field.
- Section 8.6 says the Responder shall return `NAK` when a VDO in the Structured VDM Command Request contains a field which is invalid.
- Section 8.6 also says an `ACK` is returned only when the Responder recognizes the SVID and is able to process the Command Request at the expected time.
- DisplayPort Alt Mode v2.0 Table 5-4 likewise defines Structured VDM Header bit 5 as `RESERVED (always 0)` for DP-specific commands.

Code evidence:
- `User/USBPD/Inc/pd_vdm.h:146-154` models Structured VDM Header bit 5 as `Reserved5`.
- `User/USBPD/Src/usbpd_vdm_handler.c:375-376` copies the received VDM Header directly from the received payload into `vdm_header`.
- `User/USBPD/Src/usbpd_vdm_handler.c:383-388` dispatches every Structured VDM whose `CommandType` is `REQ` to `USBPD_HandleStructuredVDMRequest()` without checking `vdm_header.Bit.Reserved5`.
- `User/USBPD/Src/usbpd_vdm_handler.c:195-267` ACKs valid-looking Discover Identity, Discover SVIDs, Discover Modes, and Enter Mode requests based on command/SVID/object-position checks only; an Enter Mode request with bit 5 set still sets the DP active marker and enables HPD before ACKing.
- `User/USBPD/Src/usbpd_vdm_handler.c:287-359` similarly processes DP Status Update and Configure requests without rejecting a nonzero Header bit 5.

Why this is non-compliant:
- Ignoring a reserved field for forward compatibility does not permit treating a malformed Structured VDM Command Request as processable when that reserved field is required to be zero by the command format. With bit 5 set, the request contains an invalid field, so the Responder should reject it with `NAK` instead of executing mode-entry, status, or configure side effects and returning `ACK`. `PD-R3.2-044` covers the transmit-side consequence where the reserved bit can be echoed in a response; this finding covers the separate receive-side behavior where an invalid Structured VDM request is accepted and acted upon.

## PD-R3.2-088 - Incoming Structured VDM requests can interrupt an unfinished Power Negotiation AMS

Spec evidence:
- The glossary defines an Atomic Message Sequence as a fixed sequence of Messages that must complete before other messages are allowed to be sent.
- USB PD R3.2 Section 7.1.1 says a Protocol Error includes an Unexpected Message received during an AMS, and that a Protocol Error during an AMS results in Soft Reset, Hard Reset, or no response depending on the case.
- Section 7.9 defines Power Negotiation (SPR) as an AMS; Section 7.9.2 says the Sink sends a `Request`, the Source sends `Accept` or `Reject`, and Section 7.9.3 says the Source sends `PS_RDY` when the power supply reaches the desired operating condition.
- Section 8.6 says a Structured VDM AMS normally consists of a Command Request and a Command response, with Attention as the request-only exception.
- Section 9.2.4.5 says `PE_SNK_Select_Capability` shall send the `Request`, initialize and run `SenderResponseTimer`, and remain in that flow until `Accept`, `Reject`, `Wait`, or timeout drives the defined transition; Section 9.2.4.6 says `PE_SNK_Transition_Sink` waits for `PS_RDY`.

Code evidence:
- `User/USBPD/Src/usbpd_pe.c:183-187` schedules `STA_TX_REQ` for a received `Source_Capabilities` message.
- `User/USBPD/Src/usbpd_pe.c:69-104` sends the resulting Sink `Request` and immediately switches back to `STA_IDLE`; it does not record an outstanding Power Negotiation AMS or expected `Accept`/`Reject`/`Wait`/`PS_RDY` sequence.
- `User/USBPD/Src/usbpd_pe.c:190-193` schedules `STA_VDM` for any received Vendor Defined Message whenever `NumDO > 0` and the message type is `Vendor_Defined`; it has no gate for an active Power Negotiation AMS.
- `User/USBPD/Src/usbpd_pe.c:106-109` runs `USBPD_VDM_Handle()` and then returns to `STA_IDLE`.
- `User/USBPD/Src/usbpd_vdm_handler.c:383-388` dispatches every Structured VDM request to the responder handler, and `User/USBPD/Src/usbpd_vdm_handler.c:195-267` and `User/USBPD/Src/usbpd_vdm_handler.c:287-359` can ACK discovery, Enter Mode, DP Status Update, or DP Configure requests without checking whether a Power Negotiation AMS is unfinished.

Why this is non-compliant:
- After this Sink sends a `Request`, the fixed Power Negotiation AMS is not complete until the Source's `Accept`/`Reject`/`Wait` decision and, for an accepted request, the `PS_RDY` transition have occurred. If a Port Partner sends a Structured VDM request in that interval, it is an unexpected attempt to start or continue a separate VDM AMS during Power Negotiation. The firmware GoodCRCs the packet, schedules the VDM handler, and can ACK or act on that VDM instead of treating it as a Protocol Error for the active AMS. `PD-R3.2-086` covers this firmware's own locally initiated Attention interrupting the same Power Negotiation AMS; this finding covers the opposite direction, where an incoming Structured VDM request is accepted while the Sink is still waiting for the Source's negotiation response.

## PD-R3.2-089 - Mandatory Pin Assignment E Configure is rejected for a USB-C receptacle DP Sink

Spec evidence:
- DisplayPort Alt Mode v2.0 Section 3.2.1 Table 3-7 lists the USB-C receptacle DP Sink Device pin assignment mandates and marks Pin Assignment C as mandatory for USB-C-to-USB-C operation and Pin Assignment E as mandatory for USB-C-to-DP operation, with Pin Assignment D optional.
- DisplayPort Alt Mode v2.0 Section 5.2.4 says a receptacle-based UFP_U is always capable of supporting Pin Assignments C and E, and possibly D.
- The same section says Table 5-7 determines mutually supported DP configurations; for USB-C-to-DP cable/receptacle cases where the UFP_U supports only E, the configured Pin Assignment is E.
- DisplayPort Alt Mode v2.0 Table 5-8 defines DisplayPort Configure Pin Assignment value `10h` as selecting Pin Assignment E.
- DisplayPort Alt Mode v2.0 Section 5.2.4 says the UFP_U shall respond to a DisplayPort Configure Command with a USB PD Responder ACK after ensuring that the reconfigured pins are connected to DisplayPort.

Code evidence:
- `User/USBPD/Src/usbpd_vdm.c:36-39` declares this port as `USBPD_DP_PORT_UFP_D` and sets `ReceptacleIndication = 1`, so the firmware is advertising a USB-C receptacle DP Sink/UFP_D.
- `User/USBPD/Src/usbpd_vdm.c:41-57` initializes the Configure whitelist with only USB Configuration and one DP Sink Configuration entry, and sets `supported_configuration_count = 2`.
- `User/USBPD/Src/usbpd_vdm.c:62-70` changes that single DP Configure entry between Pin Assignment C and Pin Assignment D depending on the lane mode, but never adds a Pin Assignment E entry.
- `User/USBPD/Src/usbpd_vdm_handler.c:42-60` accepts a Configure VDO only when its raw value exactly matches one of the whitelist entries.
- `User/USBPD/Src/usbpd_vdm_handler.c:336-339` sends a Configure NAK when the requested Configure VDO is not in that whitelist.
- `User/Drivers/Src/vl171.c:96-99` contains a mux path that maps Pin Assignment E to the same four-lane DP mode as Pin Assignment C, but the Configure handler never reaches it for a Pin Assignment E request because the whitelist rejects E first.

Why this is non-compliant:
- A USB-C receptacle DP Sink must be capable of the mandatory Pin Assignment E path used for USB-C-to-DP operation. This firmware advertises and handles a receptacle DP Sink, but its Configure validation rejects a valid DP Sink Configure VDO selecting Pin Assignment E instead of connecting the pins and ACKing. `PD-R3.2-062` covers the separate Discover Modes capability-advertisement omission for Pin Assignment E, and `PD-R3.2-082` covers rejection of the associated DP-only C assignment in multi-function mode; this finding covers the separate responder behavior where the mandatory E Configure command is not accepted.

## PD-R3.2-090 - Exit Mode ACK loss can leave the UFP in USB while the DFP still treats the mode as active

Spec evidence:
- USB PD R3.2 Section 8.6 says a Structured VDM AMS is deemed complete, and the requested functionality transition is made if applicable, when the Responder's Command response has been successfully transmitted.
- Section 8.6.5 says the Exit Mode Responder shall exit its Active Mode before sending the response Message, the Initiator exits its Active Mode when it receives the ACK, and an Initiator that fails to receive an ACK within `tVDMWaitModeExit` or receives NAK/BUSY shall exit its Active Mode.
- Section 7.31.11.3 says `VDMModeExitTimer` ensures the ACK response indicating that the requested Alternate Mode has been exited arrives within `tVDMWaitModeExit`, and that the timer is stopped when the GoodCRC EOP corresponding to the expected Exit Mode ACK has been transmitted by the PHY Layer.
- Section 9.2.25.2.2 says the UFP Mode Exit ACK state sends the Structured VDM Exit Mode ACK response and transitions to Ready when the ACK response has been sent.

Code evidence:
- `User/USBPD/Src/usbpd_vdm_handler.c:270-275` handles every `USBPD_SVDM_CMD_EXIT_MODE` by immediately clearing the DP active marker (`Mode_Try_Cnt &= ~0x80`), disabling HPD through `USBPD_HPD_Disable()`, and then sending an Exit Mode ACK.
- `User/USBPD/Src/usbpd_vdm_handler.c:91-97` sends the VDM response through `USBPD_Phy_TxPacket()` and increments `USBPD_Control.Msg_ID` immediately after the call.
- `User/USBPD/Src/usbpd_phy.c:18-61` implements synchronous transmit by waiting only for the local `IF_TX_END` condition; it does not wait for the matching GoodCRC, report transmit success/failure, retry the response, or give the Policy Engine a message-sent indication.

Why this is non-compliant:
- The Exit Mode Responder is required to stop modal operation before sending the ACK, but the AMS and the DFP's transition are not complete until the ACK response is successfully transmitted and observed. This firmware clears the local DP active state and disables HPD before it can prove that the Exit Mode ACK was GoodCRCed. If the ACK is lost, the DFP can continue to wait through `tVDMWaitModeExit` while this UFP has already stopped DP modal operation and HPD reporting, and the firmware has no retry or failure path to coordinate the managed termination result. `PD-R3.2-080` covers the opposite Enter Mode case where the UFP enters DP before ACK transmission success; this finding covers the separate Exit Mode consequence where the UFP leaves DP/HPD before successful ACK delivery is known.

## PD-R3.2-091 - DisplayPort Configure ACK loss can leave the UFP and DFP on different pin configurations

Spec evidence:
- USB PD R3.2 Section 8.6 says a Structured VDM AMS consists of a Command Request and a Command response, and that the AMS is completed, with the requested functionality transition made if applicable, when the Responder's Command response has been successfully transmitted.
- USB PD R3.2 Section 7.31.11.1 says `VDMResponseTimer` applies to Structured VDM Commands other than Enter Mode and Exit Mode, and is stopped when the GoodCRC EOP corresponding to the expected VDM Command response has been transmitted by the PHY Layer.
- DisplayPort Alt Mode v2.0 Section 5.2.4 says the DFP_U shall place pins that are to be reconfigured into the Safe state before issuing a DisplayPort Configure Command.
- The same section says the UFP_U shall respond to a DisplayPort Configure Command with a USB PD Responder ACK after ensuring that the reconfigured pins are connected to DisplayPort; after receiving that ACK, the DFP_U changes its USB-C receptacle pins from Safe state to DisplayPort and connects the SBU pins.
- For a DisplayPort Configure Command selecting USB Configuration, the same section says the UFP_U shall ACK after connecting the reconfigured pins to USB where supported, and the DFP_U changes its previously reconfigured pins to USB only after receiving the ACK.

Code evidence:
- `User/USBPD/Src/usbpd_vdm_handler.c:317-359` handles a supported DisplayPort Configure request by applying the local side effect before sending the ACK.
- `User/USBPD/Src/usbpd_vdm_handler.c:346-348` disables HPD immediately for a Configure-to-USB request.
- `User/USBPD/Src/usbpd_vdm_handler.c:350-357` calls `VL171_ApplyDPPinAssignment(config_vdo)` and samples HPD immediately for a Configure-to-DisplayPort request.
- `User/USBPD/Src/usbpd_vdm_handler.c:359` sends the DisplayPort Configure ACK only after those local side effects.
- `User/USBPD/Src/usbpd_vdm_handler.c:91-97` sends that VDM response through `USBPD_Phy_TxPacket()` and increments `USBPD_Control.Msg_ID` immediately after the call.
- `User/USBPD/Src/usbpd_phy.c:18-61` waits only for local `IF_TX_END`; it does not wait for the matching GoodCRC, report transmit success/failure, retry the Configure ACK, or notify the Policy Engine that the response was actually sent.

Why this is non-compliant:
- DisplayPort Configure is a coordinated Structured VDM AMS: the UFP_U prepares its side before ACKing, while the DFP_U does not change from Safe/previous configuration to the requested configuration until it receives the ACK. This firmware changes the local mux or HPD state before it can prove that the Configure ACK was successfully transmitted. If the ACK is lost or not GoodCRCed, the UFP_U can remain in the new local pin/HPD state while the DFP_U is still waiting for the Configure response or times out under `VDMResponseTimer`, with no retry or failure handling to re-synchronize the two sides. `PD-R3.2-003` covers the generic missing GoodCRC/retry behavior; this finding covers the separate DP Alt Mode consequence where Configure side effects occur before successful response delivery is known.

## PD-R3.2-092 - Discover VDM requests with nonzero Object Position are ACKed instead of NAKed

Spec evidence:
- USB PD R3.2 Table 6.33 defines Structured VDM command values `1`, `2`, and `3` as `Discover Identity`, `Discover SVIDs`, and `Discover Modes`.
- Section 6.4.12.2.2 says the `Object Position` field shall be used by the `Enter Mode` and `Exit Mode` commands, and shall be set to zero in a Request or Response when it is not required by the individual command.
- Section 8.6 says the Responder shall return `NAK` when a VDO in the Structured VDM Command Request contains a field which is invalid.

Code evidence:
- `User/USBPD/Inc/pd_vdm.h:146-150` defines the received Structured VDM Header fields, including `Command` and `ObjectPosition`.
- `User/USBPD/Src/usbpd_vdm_handler.c:371-377` copies the incoming VDM Header from the first Data Object into `vdm_header`.
- `User/USBPD/Src/usbpd_vdm_handler.c:195-222` ACKs every `Discover Identity` request without checking that `vdm_header->Bit.ObjectPosition == 0`.
- `User/USBPD/Src/usbpd_vdm_handler.c:225-232` ACKs every `Discover SVIDs` request without checking that `vdm_header->Bit.ObjectPosition == 0`.
- `User/USBPD/Src/usbpd_vdm_handler.c:235-250` ACKs `Discover Modes` for the DP SVID without checking that `vdm_header->Bit.ObjectPosition == 0`.

Why this is non-compliant:
- For Discover Identity, Discover SVIDs, and Discover Modes, a nonzero `Object Position` is not a valid command parameter because those commands do not use the field. This firmware can treat such malformed Discover requests as valid discovery traffic and return `ACK`, allowing an invalid VDM Header field to drive discovery state. `PD-R3.2-035` covers the transmit-side consequence where the response can echo the invalid Object Position; this finding covers the separate receive-side requirement to reject the invalid Discover request instead of accepting it as processable.
