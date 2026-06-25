# Protocol Specification

## CAN Message IDs

All CAN IDs are defined in the protocol layer to avoid hardcoding across the repository.

- `CAN_ID_HEARTBEAT_BASE` - base ID for heartbeat messages
- `CAN_ID_FAULT_REPORT` - fault reporting messages
- `CAN_ID_OTA_CONTROL` - OTA control and command messages

## Message structure

Messages are defined in terms of packet types and payload formats. The middleware layer uses these definitions to build and parse CAN frames.

## Current definitions

Canonical definitions are in `Middleware/Protocol/protocol_packet.h`. Key points:

- `ProtocolPacket` is the middleware generic packet (fields: `id`, `length`, `data[8]`).
- Semantic payload structures exist for heartbeat, fault, recovery and OTA control (e.g. `HeartbeatPacket`, `FaultPacket`, `RecoveryPacket`, `OTAControlPacket`).
- CAN IDs are defined as `CAN_ID_HEARTBEAT`, `CAN_ID_FAULT_REPORT`, `CAN_ID_RECOVERY`, `CAN_ID_OTA_CONTROL`, etc. A backwards-compatible alias `CAN_ID_HEARTBEAT_BASE` is provided.

## Transport mapping

- The Hardware layer provides `CAN_Frame` (defined in `Hardware/CAN/can_wrapper.h`) with low-level fields (`id`, `extended`, `dlc`, `data[]`).
- Middleware must serialize `ProtocolPacket` into one or more `CAN_Frame`s before calling `CAN_Send()` and vice versa for reception.

## Versioning and compatibility

- When extending payload formats, add new CAN IDs or introduce a protocol version field inside the payload. Avoid changing meanings of existing fields in-place to keep backward compatibility.

## Notes

- `NodeState` definitions live in `Middleware/Node/node_state.h` (Master/Slave enums). Protocol payloads should reference state values numerically (e.g. `uint8_t state`) rather than including Node headers directly — mapping between numeric state values and `NodeState` enums is handled in middleware.
