#include "system_combat.h"

Component* SystemCombat::addComponent(int32_t basicLifePoint)
{
    Component* comp = new Component();
    comp->type = "LifePoint";
    comp->buffer = new char[sizeof(int32_t) * 2];
        
    new (comp->buffer) int32_t(basicLifePoint);
    new (comp->buffer + sizeof(int32_t)) int32_t(0);
    
    return comp;
}

void SystemCombat::update(World* world, ECS_Core* ecs_core)
{
    for (auto entity : world->entities)
    {
        for (auto comp : entity->components)
        {
            if (comp->type == "LifePoint")
            {
                int32_t* life = reinterpret_cast<int32_t*>(comp->buffer);
                int32_t* hit = reinterpret_cast<int32_t*>(comp->buffer + sizeof(int32_t));
                
                *life -= *hit;
                *hit = 0;

                if (*life <= 0) { ecs_core->cascadingDeletion(world, entity->id); }
            }
        }
    }
}
