#ifndef SYSTEM_MANAGER_H
#define SYSTEM_MANAGER_H

#include "system_combat/system_combat.h"
#include "system_movement/system_movement.h"
class SystemManager
{
public:
    SystemMovement systemMovement;
    SystemCombat systemCombat;
};

#endif
