#ifndef CAN_WRAPPER_H
#define CAN_WRAPPER_H

#include "protocol_packet.h"

int CAN_Send(const ProtocolPacket *packet);
int CAN_Receive(ProtocolPacket *packet);

#endif // CAN_WRAPPER_H
