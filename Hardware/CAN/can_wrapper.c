#include "can_wrapper.h"
#include <stddef.h>

int CAN_Send(const ProtocolPacket *packet)
{
    (void)packet;
    return 0;
}

int CAN_Receive(ProtocolPacket *packet)
{
    (void)packet;
    return 0;
}
