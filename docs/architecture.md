# Architecture

The platform follows a layered architecture to isolate application logic from hardware specifics.

## Layers

- Application Layer: High-level control and orchestration.
- Middleware Layer: Protocol handling, heartbeat service, state management, and fault handling.
- Hardware Abstraction Layer: Interface wrappers for CAN, timer, and OTA operations.
- STM32 HAL Driver: Platform-specific HAL implementation (future work).
- CAN Hardware: Physical communication bus.

## Design Principles

- Upper layers never call STM32 HAL directly.
- Hardware-specific operations use abstract wrapper functions.
- Middleware remains independent from hardware implementation.
- All CAN message IDs and protocol constants are centralized in the protocol layer.

## Role-based state machines

The platform supports runtime role selection between a Master and Slave node within a single repository and a single main loop. Role selection is handled by the `NodeRole` API and the active state machine is executed at runtime:

- `NodeRole_Get()` returns `NODE_ROLE_MASTER` or `NODE_ROLE_SLAVE`.
- Master and Slave have distinct state enums and behaviors but share the same communication and protocol stacks.

This design allows one firmware image to adapt behavior based on configuration or runtime role selection while keeping middleware and hardware layers common.

## Slave table (Master 측 저장소)

Master 노드는 네트워크 상의 다수 Slave 상태를 추적하기 위해 `SlaveTable`을 사용합니다. `SlaveTable`은 각 Slave의 `nodeId`, 최근 Heartbeat 수신 시각, 연속 누락 카운트(`missedCount`), 상태(`SlaveState`) 및 기타 메타데이터를 보관합니다. 구현 파일: `Middleware/Node/slave_table.h`, `Middleware/Node/slave_table.c`.

SlaveTable의 목적:

- Master가 여러 Slave를 모니터링하고 장애를 탐지하기 위함
- Heartbeat 기반 타임아웃 계산 및 자동 상태 전이 지원
- FaultManager와 연계하여 자동 복구 또는 격리 트리거

## Protocol vs Hardware

To keep responsibilities clear:

- Middleware uses a `ProtocolPacket` abstraction (defined in `Middleware/Protocol/protocol_packet.h`) describing semantic packets (HeartbeatPacket, FaultPacket, OTAControlPacket, ...).
- HAL/Hardware layer exposes a `CAN_Frame` / `CAN_Frame`-style structure via `Hardware/CAN/can_wrapper.h` for low-level send/receive.
- Encode/decode functions (middleware) convert between `ProtocolPacket` and `CAN_Frame`.

This separation keeps protocol logic independent from transport specifics and simplifies testing and emulation.
