#include "app_main.h"
#include "app_task.h"
#include "node_state.h"
#include "heartbeat.h"

static NodeState currentState = NODE_INIT;

void App_Init(void)
{
    NodeState_Init(&currentState);
    Heartbeat_Init();
    AppTask_Init();
}

void App_Run(void)
{
    AppTask_Run(&currentState);
    Heartbeat_Run();
}
