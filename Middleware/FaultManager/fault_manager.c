#include "fault_manager.h"
#include <stddef.h>

static int timeoutFault = 0;

void FaultManager_Init(void)
{
    timeoutFault = 0;
}

void FaultManager_ReportTimeout(void)
{
    timeoutFault = 1;
}

void FaultManager_ClearTimeout(void)
{
    timeoutFault = 0;
}

void FaultManager_Run(NodeState *state)
{
    if (state == NULL) {
        return;
    }

    if (timeoutFault) {
        *state = NODE_ERROR;
    } else if (*state == NODE_INIT) {
        *state = NODE_READY;
    } else if (*state == NODE_READY) {
        *state = NODE_ACTIVE;
    }
}
