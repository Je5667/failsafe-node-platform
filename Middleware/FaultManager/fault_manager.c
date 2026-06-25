#include "fault_manager.h"
#include <stddef.h>
#include "node_state.h"

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

void FaultManager_Run(void)
{
    NodeRole role = NodeRole_Get();
    if (role == NODE_ROLE_MASTER) {
        MasterState ms = MasterState_Get();
        if (timeoutFault) {
            MasterState_Set(MASTER_FAULT_MANAGEMENT);
        } else if (ms == MASTER_INIT) {
            MasterState_Set(MASTER_READY);
        } else if (ms == MASTER_READY) {
            MasterState_Set(MASTER_MONITORING);
        }
    } else {
        SlaveState ss = SlaveState_Get();
        if (timeoutFault) {
            SlaveState_Set(SLAVE_ERROR);
        } else if (ss == SLAVE_INIT) {
            SlaveState_Set(SLAVE_READY);
        } else if (ss == SLAVE_READY) {
            SlaveState_Set(SLAVE_ACTIVE);
        }
    }
}
