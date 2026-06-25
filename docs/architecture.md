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
