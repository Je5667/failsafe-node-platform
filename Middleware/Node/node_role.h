#ifndef NODE_ROLE_H
#define NODE_ROLE_H

typedef enum {
    NODE_ROLE_MASTER,
    NODE_ROLE_SLAVE
} NodeRole;

/* Role management API - implemented in node_state.c */
void NodeRole_Init(void);
NodeRole NodeRole_Get(void);
void NodeRole_Set(NodeRole role);

#endif // NODE_ROLE_H
#ifndef NODE_ROLE_H
#define NODE_ROLE_H

typedef enum
{
    NODE_ROLE_MASTER,
    NODE_ROLE_SLAVE
} NodeRole;

#endif // NODE_ROLE_H
