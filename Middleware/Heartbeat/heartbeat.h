#ifndef HEARTBEAT_H
#define HEARTBEAT_H

#include <stdint.h>
#include "protocol_packet.h"

#define HEARTBEAT_INTERVAL_MS 1000
#define HEARTBEAT_TIMEOUT_MS  3000

void Heartbeat_Init(void);
void Heartbeat_Run(void);
void Heartbeat_ProcessIncoming(void);
void Heartbeat_Send(void);

#endif // HEARTBEAT_H
