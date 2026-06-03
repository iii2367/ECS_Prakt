#ifndef SYSTEM_COMBAT_H
#define SYSTEM_COMBAT_H

#include "../../ecs.h"

class SystemCombat
{
public:
    Component* addComponent(int32_t basicLifePoint);
    void update(World* world, ECS_Core* ecs_core);
};

#endif
