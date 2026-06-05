#include "SystemCombat.h"

#include <iostream>

Component* SystemCombat::addComponent(int32_t basicLifePoint)
{
    Component* comp = new Component();
    comp->type = "LifePoint";
    comp->buffer = new int8_t[sizeof(int32_t) * 2];
        
    new (comp->buffer) int32_t(basicLifePoint);
    new (comp->buffer + sizeof(int32_t)) int32_t(0);

    std::clog << "[COMBAT] Added LifePoint component with life=" << basicLifePoint << std::endl;

    return comp;
}

void SystemCombat::addHealth(Entity* entity, int32_t health)
{
    for (auto comp : entity->components)
    {
        if (comp->type == "LifePoint")
        {
            int32_t* addHealth = reinterpret_cast<int32_t*>(comp->buffer + sizeof(int32_t));
            *addHealth = health;
        }
    }
    std::clog << "[COMBAT] Entity " << entity->name << " received +" << health << " health" << std::endl;
}

void SystemCombat::update(World* world, ECSCore* ecsCore)
{
    std::vector<uint32_t> toDelete;
    for (auto entity : world->entities)
    {
        for (auto comp : entity->components)
        {
            if (comp->type == "LifePoint")
            {
                int32_t* life = reinterpret_cast<int32_t*>(comp->buffer);
                int32_t* health = reinterpret_cast<int32_t*>(comp->buffer + sizeof(int32_t));
                
                *life += *health;
                *health = 0;
                
                std::clog << "[COMBAT] Entity " << entity->name << " life=" << *life << " after update" << std::endl;

                if (*life <= 0) { toDelete.push_back(entity->id); }
            }
        }
    }
    for (auto id : toDelete)
    {
        ecsCore->cascadingDeletion(world, id);
    }
}

