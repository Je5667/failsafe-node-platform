# Protocol Specification

## CAN Message IDs

All CAN IDs are defined in the protocol layer to avoid hardcoding across the repository.

- `CAN_ID_HEARTBEAT_BASE` - base ID for heartbeat messages
- `CAN_ID_FAULT_REPORT` - fault reporting messages
- `CAN_ID_OTA_CONTROL` - OTA control and command messages

## Message structure

Messages are defined in terms of packet types and payload formats. The middleware layer uses these definitions to build and parse CAN frames.
