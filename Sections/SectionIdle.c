#include "SectionIdle.h"


bool isRoot = false;









void IdleStart()
{
    isRoot = true;
}

void IdleOnButton(uint8_t button)
{
    
}

bool IdleIsRoot()
{
    return isRoot;
}