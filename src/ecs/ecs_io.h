#ifndef ECS_IO_H
#define ECS_IO_H

#include "ecs.h"
#include "systems/system_manager.h"
#include "systems/system_movement/system_movement.h"
#include <string>

class ECS_IO
{
public:
    void load(World* world, const std::string& filename, ECS_Core* ecs_core, SystemManager* systemManager, Plane plane);
    void save(const World* world, const std::string& filename, Plane plane);
    void unload(World* world, std::string& filename);
};

#endif

