#include <iostream>
#include <memory>

#include "ecs/core/ECSCore.h"
#include "ecs/entities/World.h"
#include "ecs/systems/SystemManager.h"
#include "ecs/io/ECSIO.h"
#include "data/math/rect_m.h"

int main()
{
    std::srand(time(0));

    // Main structure
    std::unique_ptr<ECSCore> ecsCore = std::make_unique<ECSCore>(); 
    std::unique_ptr<SystemManager> sysManager = std::make_unique<SystemManager>();
    std::unique_ptr<ECSIO> ecsio = std::make_unique<ECSIO>();

    // Created component managers
    sysManager->createSystemMovement();
    sysManager->createSystemCombat();

    // Game structure
    std::unique_ptr<World> world = std::make_unique<World>();
    Rect_M border = {-20.0, 20.0, -20.0, 20.0, -0.1, 1.0, -1.0, 1.0};

    // Used ECSIO load
    ecsio->load(world.get(), "save.json", ecsCore.get(), sysManager.get());

    // Created player
    std::string playerName = "Player";
    playerName += std::to_string(rand());
    ecsCore->createEntity(world.get(), time(0)-1780671344, playerName, 2);

    // Attachment component
    ecsCore->componentAttachment(world->entities.back(), sysManager->getSystemMovement()->addComponent());
    ecsCore->componentAttachment(world->entities.back(), sysManager->getSystemCombat()->addComponent(100));

    // Components update
    sysManager->getSystemMovement()->update(world.get(), border);
    sysManager->getSystemCombat()->update(world.get(), ecsCore.get());

    // Used ECSIO save
    ecsio->save(world.get(), "save.json");

    // Clear world
    ecsCore->clearWorld(world.get());

    return 0;
}
