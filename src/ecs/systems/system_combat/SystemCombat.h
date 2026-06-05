#ifndef SYSTEM_COMBAT_H
#define SYSTEM_COMBAT_H

#include "../../core/ECSCore.h"

class SystemCombat
{
public:
    Component* addComponent(int32_t basicLifePoint);
    void addHealth(Entity* entity, int32_t health);
    void update(World* world, ECSCore* ecsCore);
};

#endif
