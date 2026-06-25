#include "heartbeat.h"
#include "can_wrapper.h"
#include "timer_wrapper.h"
#include "protocol_packet.h"
#include "fault_manager.h"
#include "node_role.h"
#include "slave_table.h"
#include <string.h>

static uint32_t lastHeartbeatMs = 0;
static uint32_t lastReceiveMs = 0;

void Heartbeat_Init(void)
{
    lastHeartbeatMs = Timer_GetTick();
    lastReceiveMs = lastHeartbeatMs;
    SlaveTable_Init();
}

void Heartbeat_Run(void)
{
    uint32_t now = Timer_GetTick();
    if ((now - lastHeartbeatMs) >= HEARTBEAT_INTERVAL_MS) {
        Heartbeat_Send();
        lastHeartbeatMs = now;
    }

    /* Check slave table timeouts only on master */
    if (NodeRole_Get() == NODE_ROLE_MASTER) {
        SlaveTable_CheckTimeouts(HEARTBEAT_TIMEOUT_MS, 3);
    }
}

void Heartbeat_ProcessIncoming(void)
{
    CAN_Frame frame;
    if (CAN_Receive(&frame)) {
        if (frame.id == CAN_ID_HEARTBEAT_BASE) {
            lastReceiveMs = Timer_GetTick();
            FaultManager_ClearTimeout();

            /* If running as master, update slave table using payload */
            if (NodeRole_Get() == NODE_ROLE_MASTER) {
                uint8_t nodeId = 0xFF;
                uint32_t uptime = 0;
                if (frame.dlc >= 1) nodeId = frame.data[0];
                if (frame.dlc >= 5) {
                    /* uptime: bytes 1..4 (big-endian) */
                    uptime = ((uint32_t)frame.data[1] << 24) |
                             ((uint32_t)frame.data[2] << 16) |
                             ((uint32_t)frame.data[3] << 8)  |
                             ((uint32_t)frame.data[4]);
                }
                if (nodeId != 0xFF) {
                    SlaveTable_MarkHeartbeat(nodeId, uptime);
                }
            }
        }
    }
}

void Heartbeat_Send(void)
{
    CAN_Frame frame;
    frame.id = CAN_ID_HEARTBEAT_BASE;
    frame.extended = 0;
    frame.dlc = 1;
    frame.data[0] = 0x01; /* TODO: set real nodeId */
    CAN_Send(&frame);
}
