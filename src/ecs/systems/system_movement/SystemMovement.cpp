#include "SystemMovement.h"

#include <iostream>

Component* SystemMovement::addComponent()
{
    Component* comp = new Component();
    comp->type = "Movement";
    comp->buffer = new int8_t[sizeof(Vec4) * 2];

    new (comp->buffer) Vec4;
    new (comp->buffer + sizeof(Vec4)) Vec4;

    std::clog << "[MOVEMENT] Added Movement component to entity" << std::endl;

    return comp;
}

void SystemMovement::addMovement(Entity* entity, Vec4 move)
{
    for (auto comp : entity->components)
    {
        if (comp->type == "Movement")
        {
            Vec4* vec4 = reinterpret_cast<Vec4*>(comp->buffer + sizeof(Vec4));
            *vec4 = move;
        }
    }
    std::clog << "[MOVEMENT] Entity " << entity->name << " move=(" << move.x << "," << move.y << "," << move.z << "," << move.w << ")" << std::endl;
}

void SystemMovement::update(World* world, Rect_M rect_m)
{
    for (auto entity : world->entities)
    {
        for (auto comp : entity->components)
        {
            if (comp->type == "Movement")
            {
                Vec4* pos = reinterpret_cast<Vec4*>(comp->buffer);
                Vec4* move = reinterpret_cast<Vec4*>(comp->buffer + sizeof(Vec4));
                Vec4 npos = *pos + *move; 
                *move = {0.0, 0.0, 0.0, 0.0};


                if (npos.x > rect_m.xmax || npos.x < rect_m.xmin ||
                    npos.y > rect_m.ymax || npos.y < rect_m.ymin ||
                    npos.z > rect_m.zmax || npos.z < rect_m.zmin ||
                    npos.w > rect_m.wmax || npos.w < rect_m.wmin) 
                {
                    std::clog << "[MOVEMENT] Entity " << entity->name << " tried to move out of bounds to pos=(" << npos.x << "," << npos.y << "," << npos.z << "," << npos.w << ")" << std::endl;
                    continue;
                }
                else { *pos = npos; std::clog << "[MOVEMENT] Entity " << entity->name << " new pos=(" << pos->x << "," << pos->y << "," << pos->z << "," << pos->w << ")" << std::endl; }
            }
        }
    }
}
