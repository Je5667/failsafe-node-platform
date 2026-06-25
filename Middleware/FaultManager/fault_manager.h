#ifndef FAULT_MANAGER_H
#define FAULT_MANAGER_H

#include "node_state.h"

void FaultManager_Init(void);
void FaultManager_Run(NodeState *state);
void FaultManager_ReportTimeout(void);
void FaultManager_ClearTimeout(void);

#endif // FAULT_MANAGER_H
