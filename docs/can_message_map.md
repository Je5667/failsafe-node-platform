# CAN Message Map

| Message | CAN ID | Description |
|---|---|---|
| Heartbeat | `CAN_ID_HEARTBEAT_BASE` | Periodic node status broadcast |
| Fault Report | `CAN_ID_FAULT_REPORT` | Reports detected faults or error states |
| OTA Control | `CAN_ID_OTA_CONTROL` | Remote firmware update control message |

The protocol layer centralizes these IDs and message definitions.
