#ifndef PROTOCOL_PACKET_H
#define PROTOCOL_PACKET_H

#include <stdint.h>

#define CAN_ID_HEARTBEAT_BASE 0x100
#define CAN_ID_FAULT_REPORT   0x200
#define CAN_ID_OTA_CONTROL    0x300

#define PROTOCOL_MAX_DATA_LENGTH 8

typedef struct {
    uint32_t id;
    uint8_t length;
    uint8_t data[PROTOCOL_MAX_DATA_LENGTH];
} ProtocolPacket;

#endif // PROTOCOL_PACKET_H
