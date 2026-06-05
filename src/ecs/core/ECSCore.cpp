#include "ECSCore.h"

#include <iostream>

void ECSCore::createEntity(World* world, std::string name, uint32_t componentsCapacity)
{
    Entity* entity = new Entity; 
    entity->id = world->entitiesCount;
    entity->name = name;
    entity->componentsCapacity = componentsCapacity;
    entity->componentsCount = 0;
        
    world->entities.push_back(entity);
    world->entitiesCount++;

    std::clog << "[CREATE ENTITY] id=" << entity->id << " name=" << entity->name << " capacity=" << componentsCapacity << std::endl;
}

void ECSCore::createEntity(World* world, uint32_t id, std::string name, uint32_t componentsCapacity)
{
    Entity* entity = new Entity; 
    entity->id = id;
    entity->name = name;
    entity->componentsCapacity = componentsCapacity;
    entity->componentsCount = 0;
        
    world->entities.push_back(entity);
    world->entitiesCount++;

    std::clog << "[CREATE ENTITY] id=" << entity->id << " name=" << entity->name << " capacity=" << componentsCapacity << std::endl;
}
    
void ECSCore::componentAttachment(Entity* entity, Component* component)
{
    if (entity->componentsCapacity > entity->componentsCount)
    {
        std::clog << "[ATTACH COMPONENT] " << component->type << " to entity=" << entity->name << " (count=" << entity->componentsCount << "/" << entity->componentsCapacity << ")" << std::endl;
        entity->components.push_back(component);
        entity->componentsCount++;
    }
    else { std::clog << "failed to attachment component " << component->type << " to " << entity->name << std::endl; }
}

void ECSCore::cascadingDeletion(World* world, uint32_t id)
{
    for (uint32_t i = 0; i < world->entitiesCount; i++)
    {
        if (world->entities[i]->id == id)
        {
            std::clog << "[DELETE ENTITY] id=" << id << " with " << world->entities[i]->componentsCount << " components" << std::endl;
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

void ECSCore::clearWorld(World* world)
{
    std::clog << "[CLEAR WORLD] deleted " << world->entitiesCount << " entities" << std::endl;
    for (auto entity : world->entities)
    {
        for (auto component : entity->components)
        {
            if (component->buffer) { delete[] component->buffer; }
            delete component;
        }
        entity->components.clear();
        entity->componentsCount = 0;

        delete entity;
    }
    world->entities.clear();
    world->entitiesCount = 0;
}
