#ifndef NODE_STATE_H
#define NODE_STATE_H

#include <stdint.h>

typedef enum {
    NODE_INIT,
    NODE_READY,
    NODE_ACTIVE,
    NODE_WARNING,
    NODE_ERROR,
    NODE_RECOVERY
} NodeState;

void NodeState_Init(NodeState *state);
const char *NodeState_ToString(NodeState state);

#endif // NODE_STATE_H
