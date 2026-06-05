#ifndef SYSTEM_MOVEMENT_H
#define SYSTEM_MOVEMENT_H

#include "../../components/Component.h"
#include "../../entities/World.h"
#include "../../entities/Entity.h"
#include "../../../data/math/vec4.h"
#include "../../../data/math/rect_m.h"

class SystemMovement
{
public:
    Component* addComponent();
    void addMovement(Entity* entity, Vec4 move);
    void update(World* world, Rect_M rect_m);
};

#endif
