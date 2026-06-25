#include "app_main.h"
#include "app_task.h"
#include "node_state.h"
#include "heartbeat.h"

void App_Init(void)
{
    NodeState_Init();
    Heartbeat_Init();
    AppTask_Init();
}

void App_Run(void)
{
    if (NodeRole_Get() == NODE_ROLE_MASTER) {
        MasterState_RunInternal();
    } else {
        SlaveState_RunInternal();
    }

    AppTask_Run();
    Heartbeat_Run();
}
