#include "heartbeat.h"
#include "node_state.h"

int main(void)
{
    NodeState_Init();
    Heartbeat_Init();
    Heartbeat_Run();
    return 0;
}
