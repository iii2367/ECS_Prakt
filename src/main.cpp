#include <iostream>
#include "data/math/vectors/rect_m.h"
#include "ecs/ecs.h"
#include "ecs/ecs_io.h"
#include "ecs/systems/system_manager.h"
#include "ecs/systems/system_movement/system_movement.h"

int main()
{
    std::srand(time(0));
    World world;
    puts("world is created");

    ECS_Core ecs_core;
    puts("ecs_core is created");

    ECS_IO ecs_io;
    puts("ecs_io is created");

    SystemManager systemManager;
    puts("systemManager is created");

    Plane plane = Plane::Vec2;
    Rect_M rect_m = {-10, 10, -10, 10, -10, 10, -10, 10};

    ecs_io.load(&world, "save.json", &ecs_core, &systemManager, plane);
    puts("load save");

    std::string name = "Player:";
    name += rand();
    ecs_core.createEntity(&world, rand(), name, 2);
    puts("add entity");

    ecs_core.componentAttachment(world.entities.back(), systemManager.systemMovement.addComponent(plane));
    puts("add component movement");

    ecs_core.componentAttachment(world.entities.back(), systemManager.systemCombat.addComponent(100));
    puts("add component combat");

    systemManager.systemMovement.update(world.entities, plane, rect_m);
    puts("movement update");

    //systemManager.systemCombat.update(&world, &ecs_core);
    //puts("combat update");


    ecs_io.save(&world, "save.json", plane);
    puts("save");
    
    return 0;
}
