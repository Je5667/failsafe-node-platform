#include "heartbeat.h"
#include "can_wrapper.h"
#include "timer_wrapper.h"
#include "protocol_packet.h"
#include "fault_manager.h"
#include <string.h>

static uint32_t lastHeartbeatMs = 0;
static uint32_t lastReceiveMs = 0;

void Heartbeat_Init(void)
{
    lastHeartbeatMs = Timer_GetTick();
    lastReceiveMs = lastHeartbeatMs;
}

void Heartbeat_Run(void)
{
    uint32_t now = Timer_GetTick();
    if ((now - lastHeartbeatMs) >= HEARTBEAT_INTERVAL_MS) {
        Heartbeat_Send();
        lastHeartbeatMs = now;
    }

    if ((now - lastReceiveMs) >= HEARTBEAT_TIMEOUT_MS) {
        FaultManager_ReportTimeout();
        lastReceiveMs = now;
    }
}

void Heartbeat_ProcessIncoming(void)
{
    ProtocolPacket packet;
    if (CAN_Receive(&packet)) {
        if (packet.id == CAN_ID_HEARTBEAT_BASE) {
            lastReceiveMs = Timer_GetTick();
            FaultManager_ClearTimeout();
        }
    }
}

void Heartbeat_Send(void)
{
    ProtocolPacket packet;
    packet.id = CAN_ID_HEARTBEAT_BASE;
    packet.length = 1;
    packet.data[0] = 0x01;
    CAN_Send(&packet);
}
