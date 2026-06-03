#ifndef SYSTEM_MOVEMENT_H
#define SYSTEM_MOVEMENT_H

#include "../../ecs.h"
#include "../../../data//math/vectors/rect_m.h"

enum class Plane
{
    Vec2,
    Vec3,
    Vec4,
};

class SystemMovement
{
public:
    Component* addComponent(Plane plane);
    void update(std::vector<Entity*> entities, Plane plane, Rect_M rect_m);
};

#endif
