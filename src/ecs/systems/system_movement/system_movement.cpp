#include "./system_movement.h"
#include "../../../data/math/vectors/vec2.h"
#include "../../../data/math/vectors/vec3.h"
#include "../../../data/math/vectors/vec4.h"

Component* SystemMovement::addComponent(Plane plane)
{
    if (plane == Plane::Vec2)
    {
        Component* comp = new Component();
        comp->type = "Movement";
        comp->buffer = new char[sizeof(Vec2) * 2];

        new (comp->buffer) Vec2;
        new (comp->buffer + sizeof(Vec2)) Vec2;

        return comp;
    }
    else if (plane == Plane::Vec3)
    {
        Component* comp = new Component();
        comp->type = "Movement";
        comp->buffer = new char[sizeof(Vec3) * 2];

        new (comp->buffer) Vec3;
        new (comp->buffer + sizeof(Vec3)) Vec3;

        return comp;
    }
    else if (plane == Plane::Vec4)
    {
        Component* comp = new Component();
        comp->type = "Movement";
        comp->buffer = new char[sizeof(Vec4) * 2];

        new (comp->buffer) Vec4;
        new (comp->buffer + sizeof(Vec4)) Vec4;

        return comp;
    }

    return nullptr; 
}

void SystemMovement::update(std::vector<Entity*> entities, Plane plane, Rect_M rect_m)
{
    for (auto entity : entities)
    {
        for (auto comp : entity->components)
        {
            if (comp->type == "Movement")
            {
                if (plane == Plane::Vec2)
                {
                    Vec2* pos = reinterpret_cast<Vec2*>(comp->buffer);
                    Vec2 npos = *pos + *(reinterpret_cast<Vec2*>(comp->buffer + sizeof(Vec2))); 

                    if (npos.x > rect_m.xmax || npos.x < rect_m.xmin ||
                        npos.y > rect_m.ymax || npos.y < rect_m.ymin) { continue; }
                    else { *pos = npos; }
                }
                else if (plane == Plane::Vec3)
                {
                    Vec3* pos = reinterpret_cast<Vec3*>(comp->buffer);
                    Vec3 npos = *pos + *(reinterpret_cast<Vec3*>(comp->buffer + sizeof(Vec3)));

                    if (npos.x > rect_m.xmax || npos.x < rect_m.xmin ||
                        npos.y > rect_m.ymax || npos.y < rect_m.ymin ||
                        npos.z > rect_m.zmax || npos.z < rect_m.zmin) { continue; }
                    else { *pos = npos; }
                }
                else if (plane == Plane::Vec4)
                {
                    Vec4* pos = reinterpret_cast<Vec4*>(comp->buffer);
                    Vec4 npos = *pos + *(reinterpret_cast<Vec4*>(comp->buffer + sizeof(Vec4)));

                    if (npos.x > rect_m.xmax || npos.x < rect_m.xmin ||
                        npos.y > rect_m.ymax || npos.y < rect_m.ymin ||
                        npos.z > rect_m.zmax || npos.z < rect_m.zmin ||
                        npos.w > rect_m.wmax || npos.w < rect_m.wmin) { continue; }
                    else { *pos = npos; }
                }
                
            }
        }
    }
}
