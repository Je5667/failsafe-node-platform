#include "can_wrapper.h"
#include <stddef.h>

int CAN_Send(const CAN_Frame *frame)
{
    (void)frame;
    return 0;
}

int CAN_Receive(CAN_Frame *frame)
{
    (void)frame;
    return 0;
}
