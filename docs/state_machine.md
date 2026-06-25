# Node State Machine

## States

```c
typedef enum {
    NODE_INIT,
    NODE_READY,
    NODE_ACTIVE,
    NODE_WARNING,
    NODE_ERROR,
    NODE_RECOVERY
} NodeState;
```

## Transitions

- `NODE_INIT` -> `NODE_READY`: system initialization complete
- `NODE_READY` -> `NODE_ACTIVE`: node is fully operational
- `NODE_ACTIVE` -> `NODE_WARNING`: minor issue detected
- `NODE_ACTIVE` -> `NODE_ERROR`: critical fault detected
- `NODE_ERROR` -> `NODE_RECOVERY`: recovery actions triggered
- `NODE_RECOVERY` -> `NODE_READY`: recovery complete
