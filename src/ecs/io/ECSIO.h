#ifndef ECSIO_H
#define ECSIO_H

#include "../core/ECSCore.h"
#include "../systems/SystemManager.h"

#include <string>

class ECSIO
{
public:
    void load(World* world, const std::string& filename, ECSCore* ecsCore, SystemManager* systemManager);
    void save(const World* world, const std::string& filename);
};

#endif
