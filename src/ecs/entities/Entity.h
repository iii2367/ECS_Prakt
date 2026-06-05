#ifndef ENTITY_H
#define ENTITY_H

#include <vector>
#include <string>
#include <cstdint>

#include "../components/Component.h"

struct Entity
{
    uint32_t id;
    std::string name;
    std::vector<Component*> components;
    uint32_t componentsCount = 0;
    uint32_t componentsCapacity = 0;
};

#endif
