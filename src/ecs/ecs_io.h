#ifndef ECS_IO_H
#define ECS_IO_H

#include "ecs.h"
#include <string>
#include "systems/system_movement/system_movement.h"
#include "systems/system_combat/system_combat.h"

class ECS_IO
{
public:
    void load(World* world, const std::string& filename, ECS_Core* ecs_core);
    void save(const World* world, const std::string& filename);
    void unload(World* world, std::string& filename);

    SystemMovement systemMovement;
    SystemCombat systemCombat;
};

#endif

