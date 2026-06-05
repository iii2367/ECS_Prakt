#ifndef ECSCORE_H
#define ECSCORE_H

#include "../components/Component.h"
#include "../entities/Entity.h"
#include "../entities/World.h"

class ECSCore
{
public:
    void createEntity(World* world, std::string name, uint32_t componentsCapacity);
    void createEntity(World* world, uint32_t id, std::string name, uint32_t componentsCapacity);
    void componentAttachment(Entity* entity, Component* component);
    void cascadingDeletion(World* world, uint32_t id);
    void clearWorld(World* world);
};

#endif
