#include "heartbeat.h"
#include "node_state.h"

int main(void)
{
    NodeState state;
    NodeState_Init(&state);
    Heartbeat_Init();
    Heartbeat_Run();
    return 0;
}
