#ifndef SLAVE_TABLE_H
#define SLAVE_TABLE_H

#include <stdint.h>
#include <stddef.h>
#include "node_state.h"

#define SLAVE_TABLE_MAX 16

typedef struct {
    uint8_t nodeId;
    SlaveState state;
    uint8_t missedCount;
    uint8_t errorCode;
    uint32_t lastHeartbeatMs;
    uint32_t uptimeSec;
} SlaveInfo;

void SlaveTable_Init(void);
int  SlaveTable_Add(uint8_t nodeId);
void SlaveTable_Remove(uint8_t nodeId);
SlaveInfo *SlaveTable_Get(uint8_t nodeId);
void SlaveTable_MarkHeartbeat(uint8_t nodeId, uint32_t uptimeSec);
void SlaveTable_CheckTimeouts(uint32_t timeoutMs, uint8_t maxMissed);
size_t SlaveTable_Count(void);
const SlaveInfo *SlaveTable_List(void);

#endif // SLAVE_TABLE_H
