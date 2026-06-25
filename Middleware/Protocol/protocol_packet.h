# Explanation: align protocol definitions with middleware expectations by adding ProtocolPacket and heartbeat ID alias, and removing node_state include to reduce coupling.

#ifndef PROTOCOL_PACKET_H
#define PROTOCOL_PACKET_H

#include <stdint.h>

/* CAN ID definitions (protocol-level) */
#define CAN_ID_HEARTBEAT        0x100
#define CAN_ID_FAULT_REPORT     0x200
#define CAN_ID_RECOVERY         0x300
#define CAN_ID_OTA_CONTROL      0x400
#define CAN_ID_NODE_STATUS      0x500

/* Backwards-compatible alias used in some modules */
#define CAN_ID_HEARTBEAT_BASE CAN_ID_HEARTBEAT

/* Protocol-level generic packet used by middleware */
typedef struct {
    uint32_t id;         /* CAN identifier */
    uint8_t length;      /* payload length (DLC) */
    uint8_t data[8];     /* payload (max 8 bytes) */
} ProtocolPacket;

/* Specific packet payload structures (semantic definitions) */
typedef struct {
    uint8_t nodeId;
    uint8_t state;
    uint8_t errorCode;
    uint32_t uptimeSec;
} HeartbeatPacket;

typedef struct {
    uint8_t nodeId;
    uint8_t faultCode;
    uint8_t severity;
} FaultPacket;

typedef struct {
    uint8_t targetNodeId;
    uint8_t recoveryAction;
} RecoveryPacket;

typedef struct {
    uint8_t command;
    uint32_t firmwareVersion;
} OTAControlPacket;

typedef struct {
    uint8_t nodeId;
    uint8_t state;
    uint8_t cpuUsage;
    uint8_t memoryUsage;
} NodeStatusPacket;

#endif // PROTOCOL_PACKET_H
