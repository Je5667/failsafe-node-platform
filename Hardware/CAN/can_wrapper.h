#ifndef CAN_WRAPPER_H
#define CAN_WRAPPER_H

#include <stdint.h>

/* Hardware-level CAN frame */
typedef struct {
    uint32_t id;      /* CAN identifier */
    uint8_t extended; /* 0 = standard, 1 = extended */
    uint8_t dlc;      /* data length code */
    uint8_t data[8];  /* payload bytes */
} CAN_Frame;

/* Send/receive operate on hardware CAN frames. Middleware should encode/decode
   between ProtocolPacket and CAN_Frame. */
int CAN_Send(const CAN_Frame *frame);
int CAN_Receive(CAN_Frame *frame);

#endif // CAN_WRAPPER_H
