#ifndef ECS_H
#define ECS_H

#include <string>
#include <vector>

struct Component
{
    std::string type;
    char* buffer;
};

struct Entity
{
    uint32_t id;
    std::string name;
    std::vector<Component*> components;
    uint32_t componentsCount = 0;
    uint32_t componentsCapacity = 0;
};

struct World
{
    std::vector<Entity*> entities;
    uint32_t entitiesCount = 0;
};

class ECS_Core
{
public:
    void createEntity(World* world, uint32_t id, std::string name, uint32_t componentsCapacity);
    void componentAttachment(Entity* entity, Component* component);
    void cascadingDeletion(World* world, uint32_t id);
};

#endif

