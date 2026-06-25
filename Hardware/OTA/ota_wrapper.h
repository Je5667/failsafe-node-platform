#ifndef OTA_WRAPPER_H
#define OTA_WRAPPER_H

#include "protocol_packet.h"

int OTA_StartUpdate(const ProtocolPacket *controlPacket);
int OTA_CheckStatus(void);

#endif // OTA_WRAPPER_H
