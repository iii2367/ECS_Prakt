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

                bool clamped = false;
                if (npos.x > rect_m.xmax) { npos.x = rect_m.xmax; clamped = true; }
                if (npos.x < rect_m.xmin) { npos.x = rect_m.xmin; clamped = true; }
                if (npos.y > rect_m.ymax) { npos.y = rect_m.ymax; clamped = true; }
                if (npos.y < rect_m.ymin) { npos.y = rect_m.ymin; clamped = true; }
                if (npos.z > rect_m.zmax) { npos.z = rect_m.zmax; clamped = true; }
                if (npos.z < rect_m.zmin) { npos.z = rect_m.zmin; clamped = true; }
                if (npos.w > rect_m.wmax) { npos.w = rect_m.wmax; clamped = true; }
                if (npos.w < rect_m.wmin) { npos.w = rect_m.wmin; clamped = true; }

                *pos = npos;

                if (clamped) { std::clog << "[MOVEMENT] Entity " << entity->name << " tried to move out of bounds, clamped to pos=(" << pos->x << "," << pos->y << "," << pos->z << "," << pos->w << ")" << std::endl; }
                else { std::clog << "[MOVEMENT] Entity " << entity->name << " new pos=(" << pos->x << "," << pos->y << "," << pos->z << "," << pos->w << ")" << std::endl; }
            }
        }
    }
}
