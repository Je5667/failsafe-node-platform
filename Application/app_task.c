#include "app_task.h"
#include "heartbeat.h"
#include "fault_manager.h"

void AppTask_Init(void)
{
    FaultManager_Init();
}

void AppTask_Run(NodeState *state)
{
    Heartbeat_ProcessIncoming();
    FaultManager_Run(state);
}
