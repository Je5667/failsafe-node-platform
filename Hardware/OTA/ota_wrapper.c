#include "ota_wrapper.h"
#include <stddef.h>

int OTA_StartUpdate(const ProtocolPacket *controlPacket)
{
    (void)controlPacket;
    return 0;
}

int OTA_CheckStatus(void)
{
    return 0;
}
