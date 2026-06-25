#include "slave_table.h"
#include "timer_wrapper.h"
#include "fault_manager.h"
#include <string.h>

static SlaveInfo table[SLAVE_TABLE_MAX];
static size_t table_count = 0;

void SlaveTable_Init(void)
{
    memset(table, 0, sizeof(table));
    for (size_t i = 0; i < SLAVE_TABLE_MAX; ++i) {
        table[i].nodeId = 0xFF;
        table[i].state = SLAVE_INIT;
    }
    table_count = 0;
}

static int find_index(uint8_t nodeId)
{
    for (size_t i = 0; i < SLAVE_TABLE_MAX; ++i) {
        if (table[i].nodeId == nodeId) return (int)i;
    }
    return -1;
}

int SlaveTable_Add(uint8_t nodeId)
{
    int idx = find_index(nodeId);
    if (idx >= 0) return idx;
    for (size_t i = 0; i < SLAVE_TABLE_MAX; ++i) {
        if (table[i].nodeId == 0xFF) {
            table[i].nodeId = nodeId;
            table[i].state = SLAVE_INIT;
            table[i].missedCount = 0;
            table[i].errorCode = 0;
            table[i].lastHeartbeatMs = Timer_GetTick();
            table[i].uptimeSec = 0;
            table_count++;
            return (int)i;
        }
    }
    return -1; /* full */
}

void SlaveTable_Remove(uint8_t nodeId)
{
    int idx = find_index(nodeId);
    if (idx >= 0) {
        table[idx].nodeId = 0xFF;
        table[idx].state = SLAVE_INIT;
        table[idx].missedCount = 0;
        table[idx].errorCode = 0;
        table[idx].lastHeartbeatMs = 0;
        table[idx].uptimeSec = 0;
        if (table_count > 0) table_count--;
    }
}

SlaveInfo *SlaveTable_Get(uint8_t nodeId)
{
    int idx = find_index(nodeId);
    if (idx >= 0) return &table[idx];
    return NULL;
}

void SlaveTable_MarkHeartbeat(uint8_t nodeId, uint32_t uptimeSec)
{
    int idx = find_index(nodeId);
    if (idx < 0) idx = SlaveTable_Add(nodeId);
    if (idx < 0) return; /* table full */
    table[idx].lastHeartbeatMs = Timer_GetTick();
    table[idx].missedCount = 0;
    table[idx].uptimeSec = uptimeSec;
    if (table[idx].state == SLAVE_INIT || table[idx].state == SLAVE_READY) {
        table[idx].state = SLAVE_ACTIVE;
    }
}

void SlaveTable_CheckTimeouts(uint32_t timeoutMs, uint8_t maxMissed)
{
    uint32_t now = Timer_GetTick();
    for (size_t i = 0; i < SLAVE_TABLE_MAX; ++i) {
        if (table[i].nodeId == 0xFF) continue;
        if ((now - table[i].lastHeartbeatMs) >= timeoutMs) {
            table[i].missedCount++;
            if (table[i].missedCount >= maxMissed) {
                table[i].state = SLAVE_ERROR;
                FaultManager_ReportTimeout();
            }
        }
    }
}

size_t SlaveTable_Count(void)
{
    return table_count;
}

const SlaveInfo *SlaveTable_List(void)
{
    return table;
}
