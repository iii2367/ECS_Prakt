#ifndef SYSTEM_MANAGER_H
#define SYSTEM_MANAGER_H

#include "system_combat/SystemCombat.h"
#include "system_movement/SystemMovement.h"

#include <memory>

class SystemManager
{
public:
    void createSystemMovement();
    void createSystemCombat();

    SystemMovement* getSystemMovement() const;
    SystemCombat* getSystemCombat() const;
private:
    std::unique_ptr<SystemMovement> systemMovement;
    std::unique_ptr<SystemCombat> systemCombat;
};

#endif
