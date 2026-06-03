#include "./ecs.h"

#include <stdexcept>


void ECS_Core::createEntity(World* world, uint32_t id, std::string name, uint32_t componentsCapacity) 
{
    Entity* entity = new Entity; 
    entity->id = id;
    entity->name = name;
    entity->componentsCapacity = componentsCapacity;
    entity->componentsCount = 0;
        
    world->entities.push_back(entity);
    world->entitiesCount++;
}
    
void ECS_Core::componentAttachment(Entity* entity, Component* component)
{
    if (entity->componentsCapacity > entity->componentsCount)
    {
        entity->components.push_back(component);
        entity->componentsCount++;
    }
    else { throw std::logic_error("insufficient capacity to add a component in the " + entity->name); }
}

void ECS_Core::cascadingDeletion(World* world, uint32_t id)
{
    for (uint32_t i = 0; i < world->entitiesCount; i++)
    {
        if (world->entities[i]->id == id)
        {
            for (auto component :world->entities[i]->components)
            {
                if (component->buffer) { delete[] component->buffer; }
                delete component;
            }
            world->entities[i]->components.clear();
            world->entities[i]->componentsCount = 0;
                
            delete world->entities[i];

            world->entities.erase(world->entities.begin() + i);
            world->entitiesCount--;
            break;
        }
    }
}
