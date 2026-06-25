#ifndef NODE_INFO_H
#define NODE_INFO_H

#include <stdint.h>
#include "node_state.h"

typedef struct
{
    uint8_t nodeId;
    NodeState state;
    uint8_t errorCode;
    uint32_t uptime;
} NodeInfo;

void NodeInfo_Init(NodeInfo *nodeInfo, uint8_t nodeId);
const char *NodeInfo_ToString(const NodeInfo *nodeInfo);

#endif // NODE_INFO_H