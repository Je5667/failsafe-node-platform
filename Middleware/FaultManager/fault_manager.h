#ifndef FAULT_MANAGER_H
#define FAULT_MANAGER_H

#include "node_state.h"

void FaultManager_Init(void);
void FaultManager_Run(void); /* role-aware runner */
void FaultManager_ReportTimeout(void);
void FaultManager_ClearTimeout(void);

#endif // FAULT_MANAGER_H
