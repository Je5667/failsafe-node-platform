#ifndef NODE_STATE_H
#define NODE_STATE_H

#include <stdint.h>
#include "node_role.h"

typedef enum {
    NODE_INIT,
    NODE_READY,
    NODE_ACTIVE,
    NODE_WARNING,
    NODE_ERROR,
    NODE_RECOVERY
} NodeState; /* legacy single-node state (kept for compatibility) */

/* Master state machine */
typedef enum {
    MASTER_INIT,
    MASTER_READY,
    MASTER_MONITORING,
    MASTER_FAULT_MANAGEMENT,
    MASTER_OTA_UPDATE,
    MASTER_ERROR
} MasterState;

/* Slave state machine */
typedef enum {
    SLAVE_INIT,
    SLAVE_READY,
    SLAVE_ACTIVE,
    SLAVE_WARNING,
    SLAVE_ERROR,
    SLAVE_RECOVERY,
    SLAVE_OTA
} SlaveState;

/* Node role and state management API */
void NodeState_Init(void);
NodeRole NodeRole_Get(void);
void NodeRole_Set(NodeRole role);

/* Master state API */
void MasterState_Init(MasterState *state);
void MasterState_Run(MasterState *state);
const char *MasterState_ToString(MasterState state);
/* Internal-run and accessors for repository-wide state objects */
void MasterState_RunInternal(void);
MasterState MasterState_Get(void);
void MasterState_Set(MasterState s);

/* Slave state API */
void SlaveState_Init(SlaveState *state);
void SlaveState_Run(SlaveState *state);
const char *SlaveState_ToString(SlaveState state);
void SlaveState_RunInternal(void);
SlaveState SlaveState_Get(void);
void SlaveState_Set(SlaveState s);

#endif // NODE_STATE_H
