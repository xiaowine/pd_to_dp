# USB PD R3.2 Fix Map

Source review log: `USB_PD_R3_2_COMPLIANCE_REVIEW.md`

Purpose:
- Track each compliance finding as an actionable modification checklist.
- Keep related findings together so fixes can be batched by subsystem.
- Mark entries as done only after code change and verification.

Status legend:
- `[ ]` Open
- `[x]` Fixed and verified
- `[~]` Partially fixed or needs retest

Priority guide:
- `P0`: Blocks a reliable USB PD protocol stack or can break basic attach/power negotiation.
- `P1`: Required by spec and likely visible in compliance testing or interoperability.
- `P2`: DP Alt Mode/detail behavior, edge cases, or cleanup that depends on P0/P1 foundations.

Recommended fix order:
1. Protocol Layer transmit/receive correctness.
2. Sink Policy Engine power/reset state machine.
3. Required message responder coverage.
4. Common VDM/SVDM validation and state management.
5. DisplayPort Alt Mode and HPD behavior.

## 1. Protocol Layer Foundations

Primary files:
- `User/USBPD/Src/usbpd_phy.c`
- `User/USBPD/Src/usbpd_pe.c`
- `User/USBPD/Inc/*`

| Status | ID | Priority | Fix target |
| --- | --- | --- | --- |
| [x] | PD-R3.2-003 | P0 | Wait for matching GoodCRC, retry with same MessageID, increment MessageID only after success. |
| [x] | PD-R3.2-004 | P0 | Store last received MessageID per SOP and discard duplicate retries after GoodCRC. |
| [x] | PD-R3.2-018 | P0 | Bound GoodCRC response timing to `tTransmit`. |
| [ ] | PD-R3.2-031 | P0 | Implement `PRL_Tx_Discard_Message` behavior when incoming SOP traffic interrupts transmit preparation. |
| [x] | PD-R3.2-032 | P0 | Reset MessageID counters and stored receive IDs on Protocol Layer reset. |
| [ ] | PD-R3.2-034 | P0 | Check CC bus Idle immediately before packet transmission. |
| [ ] | PD-R3.2-039 | P0 | Recover transmission failure by sending required Soft Reset. |
| [x] | PD-R3.2-079 | P0 | Fix receive/main-loop race where a message can be processed without sending GoodCRC. |

## 2. Sink Policy Engine: Attach, Power Negotiation, Reset

Primary files:
- `User/USBPD/Src/usbpd_pe.c`
- `User/USBPD/Src/usbpd_phy.c`
- board VBUS/CC/timer integration files

| Status | ID | Priority | Fix target |
| --- | --- | --- | --- |
| [x] | PD-R3.2-001 | P0 | Remove normal-attach Hard Reset; enter Sink discovery/capability wait flow instead. |
| [x] | PD-R3.2-002 | P0 | Respond to received `Soft_Reset` with `Accept` after resetting SOP protocol state. |
| [~] | PD-R3.2-005 | P0 | Implement `PE_SNK_Select_Capability`, `PE_SNK_Transition_Sink`, explicit contract tracking, and `PE_SNK_Ready`. |
| [x] | PD-R3.2-006 | P0 | Treat `Source_Capabilities` outside allowed Sink states as Protocol Error. |
| [x] | PD-R3.2-013 | P0 | Handle received Hard Reset with Sink transition-to-default recovery. |
| [x] | PD-R3.2-017 | P1 | Do not silently skip required Request when offered 5V PDO lacks USB communication capability. |
| [x] | PD-R3.2-028 | P0 | Implement `SinkWaitCapTimer` and `HardResetCounter` for missing `Source_Capabilities`. |
| [ ] | PD-R3.2-029 | P0 | Bound Request transmission after `Source_Capabilities` by `tSenderResponse`. |
| [~] | PD-R3.2-038 | P0 | Handle `Wait` response and implement `SinkRequestTimer`. |
| [ ] | PD-R3.2-043 | P1 | Enter USB Type-C Error Recovery on SOP Port Data Role mismatch. |
| [ ] | PD-R3.2-046 | P0 | Gate Sink discovery by VBUS-present detection. |
| [x] | PD-R3.2-053 | P0 | Treat unexpected recognized control responses as Protocol Error. |
| [x] | PD-R3.2-069 | P0 | Avoid repeating an unchanged Sink Request after Source `Reject`. |
| [x] | PD-R3.2-070 | P0 | Run Sink transition-to-default recovery after transmitting Hard Reset. |
| [x] | PD-R3.2-078 | P1 | Validate Source PDO current before mirroring it into Request. |
| [x] | PD-R3.2-085 | P0 | Clear pending receive/Request state on Detach. |
| [x] | PD-R3.2-086 | P0 | Prevent HPD Attention from interrupting unfinished Power Negotiation AMS. |
| [x] | PD-R3.2-088 | P0 | Reject or defer incoming Structured VDM requests during unfinished Power Negotiation AMS. |

## 3. Required Message Responder Coverage

Primary files:
- `User/USBPD/Src/usbpd_pe.c`
- `User/USBPD/Src/usbpd_vdm_handler.c`
- PDO/capability definition files

| Status | ID | Priority | Fix target |
| --- | --- | --- | --- |
| [~] | PD-R3.2-007 | P1 | Send `Not_Supported` for unsupported, unrecognized, and reserved messages. |
| [x] | PD-R3.2-008 | P1 | Respond to `Get_Sink_Cap` with `Sink_Capabilities`. |
| [ ] | PD-R3.2-016 | P1 | Classify and handle Extended/Chunked messages, including `ChunkingNotSupportedTimer`. |
| [ ] | PD-R3.2-019 | P1 | Implement required Data Reset state machine or compliant response path. |
| [ ] | PD-R3.2-024 | P1 | Implement required BIST message behavior. |
| [ ] | PD-R3.2-025 | P1 | Respond to `Get_Sink_Cap_Extended` with `Sink_Capabilities_Extended`. |
| [ ] | PD-R3.2-026 | P1 | Respond to `Get_Revision` with Revision Message. |
| [ ] | PD-R3.2-033 | P1 | Inform DPM when `Not_Supported` is received. |
| [ ] | PD-R3.2-040 | P1 | Inform DPM when `Alert` is received. |
| [ ] | PD-R3.2-045 | P1 | Respond correctly to unsupported or unevaluated role-swap requests. |
| [ ] | PD-R3.2-049 | P1 | Answer `Enter_USB` requests to the UFP. |
| [ ] | PD-R3.2-051 | P1 | Respond correctly to `VCONN_Swap` requests. |
| [ ] | PD-R3.2-060 | P1 | Decode messages with Header `Ext` bit as Extended Messages, not Control/Data messages. |
| [ ] | PD-R3.2-072 | P1 | Treat unexpected recognized non-VDM Data Messages as Protocol Error or required response. |
| [ ] | PD-R3.2-073 | P1 | Respond to `Get_Status` with required Status Extended Message. |

## 4. Common VDM and Structured VDM Framework

Primary files:
- `User/USBPD/Src/usbpd_vdm_handler.c`
- `User/USBPD/Src/usbpd_vdm.c`
- `User/USBPD/Inc/pd_vdm.h`
- `User/USBPD/Src/usbpd_pe.c`

| Status | ID | Priority | Fix target |
| --- | --- | --- | --- |
| [x] | PD-R3.2-009 | P1 | Ignore SOP VDMs until an Explicit Contract exists. |
| [x] | PD-R3.2-010 | P1 | Send `Not_Supported` for unsupported Unstructured VDMs after Explicit Contract. |
| [ ] | PD-R3.2-011 | P1 | Implement Structured VDM version negotiation and common-version storage. |
| [ ] | PD-R3.2-015 | P1 | Detect and track SOP Specification Revision. |
| [ ] | PD-R3.2-023 | P1 | Bound Structured VDM response timing by required VDM timers. |
| [x] | PD-R3.2-027 | P1 | NAK Discover SVIDs requests whose SVID is not the PD SID. |
| [~] | PD-R3.2-030 | P1 | NAK Structured VDM requests with invalid `NumDO`. |
| [x] | PD-R3.2-035 | P1 | Prevent Discover VDM responses from transmitting invalid Object Position. |
| [ ] | PD-R3.2-036 | P1 | Inform DPM when Structured VDM Attention is received. |
| [x] | PD-R3.2-041 | P1 | ACK Discover Identity only for valid PD SID request context. |
| [x] | PD-R3.2-044 | P1 | Sanitize reserved bits in Structured VDM responses. |
| [x] | PD-R3.2-050 | P1 | Keep Alternate Mode state across Soft Reset; reset only PD protocol scope. |
| [ ] | PD-R3.2-052 | P1 | Sanitize Object Position in invalid-command NAKs. |
| [ ] | PD-R3.2-054 | P1 | Treat unexpected Structured VDM responses as Protocol Error. |
| [ ] | PD-R3.2-055 | P2 | Add required Structured VDM discovery initiator support for Modal Operation. |
| [x] | PD-R3.2-076 | P1 | NAK Structured VDM requests with invalid version fields. |
| [x] | PD-R3.2-077 | P1 | Require prior Discover Modes result before ACKing Enter Mode. |
| [x] | PD-R3.2-084 | P1 | NAK or correctly handle repeated Enter Mode while DP mode is already active. |
| [x] | PD-R3.2-087 | P1 | NAK Structured VDM requests with reserved Header bit 5 set. |
| [x] | PD-R3.2-092 | P1 | NAK Discover VDM requests with nonzero Object Position. |

## 5. DisplayPort Alt Mode and HPD

Primary files:
- `User/USBPD/Src/usbpd_vdm_handler.c`
- `User/USBPD/Src/usbpd_vdm.c`
- `User/USBPD/Src/usbpd_hpd.c`
- `User/Drivers/Src/vl171.c`

| Status | ID | Priority | Fix target |
| --- | --- | --- | --- |
| [ ] | PD-R3.2-012 | P1 | Replace Discover Identity placeholder VID/PID with valid device identity values. |
| [ ] | PD-R3.2-014 | P1 | Make Sink-initiated Attention obey SinkTxOK collision avoidance. |
| [ ] | PD-R3.2-020 | P1 | Trigger required Hard Reset for `DR_Swap` during Modal Operation. |
| [x] | PD-R3.2-021 | P1 | Exit Active Modes and return port to USB operation on Detach. |
| [x] | PD-R3.2-022 | P1 | NAK Exit Mode for invalid or inactive modes. |
| [ ] | PD-R3.2-037 | P1 | Advertise supported DP signal-reconfiguration mode in Discover Identity UFP VDO. |
| [x] | PD-R3.2-042 | P1 | Return port to USB operation before sending Exit Mode ACK. |
| [x] | PD-R3.2-047 | P1 | Do not apply DP pin configuration before Enter Mode process completes. |
| [x] | PD-R3.2-048 | P1 | NAK DP SVID-specific commands when no DP Active Mode exists. |
| [x] | PD-R3.2-056 | P1 | Validate Object Position for DP Status and Configure commands. |
| [x] | PD-R3.2-057 | P1 | Reconnect pins to USB before ACKing DisplayPort Configure to USB. |
| [ ] | PD-R3.2-058 | P1 | Enforce required third-message pacing for DP Attention transmission. |
| [x] | PD-R3.2-059 | P1 | Advertise mandatory DP-only pin assignment in multi-function mode. |
| [ ] | PD-R3.2-061 | P2 | Preserve queued second `IRQ_HPD` event in HPD-to-USB PD conversion. |
| [x] | PD-R3.2-062 | P1 | Advertise mandatory Pin Assignment E for USB-C receptacle DP Sink. |
| [ ] | PD-R3.2-063 | P2 | Preserve HPD queue ordering after `HPD_Low` and clear stale `IRQ_HPD`. |
| [x] | PD-R3.2-064 | P1 | Report DP Status Enabled only when DisplayPort functionality is enabled. |
| [ ] | PD-R3.2-065 | P1 | Do not send HPD Attention before initial DisplayPort Status exchange. |
| [ ] | PD-R3.2-066 | P2 | Add USB Billboard path when DisplayPort Alt Mode entry fails. |
| [ ] | PD-R3.2-067 | P1 | Re-enable HPD after returning from USB Configuration to DP Configuration. |
| [ ] | PD-R3.2-068 | P1 | Debounce HPD High before USB PD reporting. |
| [ ] | PD-R3.2-071 | P1 | Debounce/filter raw HPD high before initial DP Status report. |
| [ ] | PD-R3.2-074 | P1 | Enforce required DP Status/Configure VDO payload fields. |
| [ ] | PD-R3.2-075 | P1 | Advertise current Structured VDM minor version for standard SVDM commands. |
| [x] | PD-R3.2-080 | P1 | Avoid entering DP Alt Mode before Enter Mode ACK transmission succeeds. |
| [x] | PD-R3.2-081 | P1 | Remove HPD events from queue only after USB PD report succeeds. |
| [x] | PD-R3.2-082 | P1 | Accept mandatory associated DP-only Configure pin assignment in multi-function mode. |
| [ ] | PD-R3.2-083 | P1 | Send required HPD High Attention after DP Sink configuration completes. |
| [x] | PD-R3.2-089 | P1 | Accept mandatory Pin Assignment E Configure for USB-C receptacle DP Sink. |
| [ ] | PD-R3.2-090 | P1 | Handle Exit Mode ACK loss without leaving UFP/DFP mode states inconsistent. |
| [ ] | PD-R3.2-091 | P1 | Handle DisplayPort Configure ACK loss without leaving pin configurations inconsistent. |

## Cross-Cutting Implementation Notes

- Many DP/VDM findings depend on a reliable transmit-complete signal from the Protocol Layer. Fix `PD-R3.2-003` before marking ACK-loss findings done.
- Many AMS interleaving findings depend on explicit PE state tracking. Fix `PD-R3.2-005` before marking `PD-R3.2-086` or `PD-R3.2-088` done.
- Avoid marking a field-validation issue fixed until malformed requests are tested for both response type and side effects.
- Detach, Hard Reset, Soft Reset, and Error Recovery should each have an explicit cleanup matrix for protocol state, pending RX/TX state, PE state, VDM state, mux state, and HPD queue state.
