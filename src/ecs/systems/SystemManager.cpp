#include "SystemManager.h"
#include "system_combat/SystemCombat.h"
#include "system_movement/SystemMovement.h"
#include <memory>

void SystemManager::createSystemMovement()
{
    this->systemMovement = std::make_unique<SystemMovement>();
}

void SystemManager::createSystemCombat()
{
    this->systemCombat = std::make_unique<SystemCombat>();
}

SystemMovement* SystemManager::getSystemMovement() const { return systemMovement.get(); }
SystemCombat* SystemManager::getSystemCombat() const { return systemCombat.get(); }
