#include "app_task.h"
#include "heartbeat.h"
#include "fault_manager.h"
#include "node_state.h"

void AppTask_Init(void)
{
    FaultManager_Init();
}

void AppTask_Run(void)
{
    Heartbeat_ProcessIncoming();
    FaultManager_Run();
}
