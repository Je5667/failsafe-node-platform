#include "node_state.h"
#include <stdlib.h>
#include <stdio.h>

static NodeRole currentRole = NODE_ROLE_SLAVE;
static MasterState masterState = MASTER_INIT;
static SlaveState slaveState = SLAVE_INIT;

void NodeState_Init(void)
{
    currentRole = NODE_ROLE_SLAVE;
    MasterState_Init(&masterState);
    SlaveState_Init(&slaveState);
}

NodeRole NodeRole_Get(void)
{
    return currentRole;
}

void NodeRole_Set(NodeRole role)
{
    currentRole = role;
}

/* Master state implementation (simple skeleton) */
void MasterState_Init(MasterState *state)
{
    if (state) *state = MASTER_INIT;
}

void MasterState_Run(MasterState *state)
{
    if (state == NULL) return;
    switch (*state) {
        case MASTER_INIT:
            *state = MASTER_READY;
            break;
        case MASTER_READY:
            *state = MASTER_MONITORING;
            break;
        case MASTER_MONITORING:
            /* monitoring logic handled by Heartbeat module */
            break;
        case MASTER_FAULT_MANAGEMENT:
            /* fault handling logic */
            break;
        case MASTER_OTA_UPDATE:
            /* OTA orchestration */
            break;
        case MASTER_ERROR:
            /* error handling */
            break;
        default:
            *state = MASTER_ERROR;
            break;
    }
}

const char *MasterState_ToString(MasterState state)
{
    switch (state) {
        case MASTER_INIT: return "MASTER_INIT";
        case MASTER_READY: return "MASTER_READY";
        case MASTER_MONITORING: return "MASTER_MONITORING";
        case MASTER_FAULT_MANAGEMENT: return "MASTER_FAULT_MANAGEMENT";
        case MASTER_OTA_UPDATE: return "MASTER_OTA_UPDATE";
        case MASTER_ERROR: return "MASTER_ERROR";
        default: return "MASTER_UNKNOWN";
    }
}

/* Internal accessors and runners */
void MasterState_RunInternal(void)
{
    MasterState_Run(&masterState);
}

MasterState MasterState_Get(void)
{
    return masterState;
}

void MasterState_Set(MasterState s)
{
    masterState = s;
}

/* Slave state implementation (simple skeleton) */
void SlaveState_Init(SlaveState *state)
{
    if (state) *state = SLAVE_INIT;
}

void SlaveState_Run(SlaveState *state)
{
    if (state == NULL) return;
    switch (*state) {
        case SLAVE_INIT:
            *state = SLAVE_READY;
            break;
        case SLAVE_READY:
            /* wait for master connection */
            break;
        case SLAVE_ACTIVE:
            /* normal operation */
            break;
        case SLAVE_WARNING:
            /* minor issues */
            break;
        case SLAVE_ERROR:
            /* error handling */
            break;
        case SLAVE_RECOVERY:
            /* recovery actions */
            break;
        case SLAVE_OTA:
            /* OTA handling */
            break;
        default:
            *state = SLAVE_ERROR;
            break;
    }
}

const char *SlaveState_ToString(SlaveState state)
{
    switch (state) {
        case SLAVE_INIT: return "SLAVE_INIT";
        case SLAVE_READY: return "SLAVE_READY";
        case SLAVE_ACTIVE: return "SLAVE_ACTIVE";
        case SLAVE_WARNING: return "SLAVE_WARNING";
        case SLAVE_ERROR: return "SLAVE_ERROR";
        case SLAVE_RECOVERY: return "SLAVE_RECOVERY";
        case SLAVE_OTA: return "SLAVE_OTA";
        default: return "SLAVE_UNKNOWN";
    }
}

void SlaveState_RunInternal(void)
{
    SlaveState_Run(&slaveState);
}

SlaveState SlaveState_Get(void)
{
    return slaveState;
}

void SlaveState_Set(SlaveState s)
{
    slaveState = s;
}
