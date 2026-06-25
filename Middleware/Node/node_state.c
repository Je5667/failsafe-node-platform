#include "node_state.h"

void NodeState_Init(NodeState *state)
{
    if (state != NULL) {
        *state = NODE_INIT;
    }
}

const char *NodeState_ToString(NodeState state)
{
    switch (state) {
        case NODE_INIT: return "NODE_INIT";
        case NODE_READY: return "NODE_READY";
        case NODE_ACTIVE: return "NODE_ACTIVE";
        case NODE_WARNING: return "NODE_WARNING";
        case NODE_ERROR: return "NODE_ERROR";
        case NODE_RECOVERY: return "NODE_RECOVERY";
        default: return "UNKNOWN";
    }
}
