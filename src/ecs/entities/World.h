#ifndef WORLD_H
#define WORLD_H

#include <cstdint>
#include <vector>

#include "../entities/Entity.h"

struct World
{
    std::vector<Entity*> entities;
    uint32_t entitiesCount = 0;
};

#endif
