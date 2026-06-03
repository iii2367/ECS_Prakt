#include "ecs_io.h"
#include "ecs.h"
#include "systems/system_movement/system_movement.h"
#include "../data/math/vectors/vec4.h"
#include "../data/math/vectors/vec3.h"
#include "../data/math/vectors/vec2.h"

#include <iostream>
#include <fstream>
#include <string>

void ECS_IO::load(World* world, const std::string& filename, ECS_Core* ecs_core)
{
    std::fstream file;
    file.open(filename, std::ios::in);
    if (file.peek() == std::fstream::traits_type::eof()) { return; }
    
    std::vector<std::string> lines;
    std::string line;
    for (;std::getline(file, line);)
    {
        lines.push_back(line);
        
        if (lines.size() == 4)
        {
            uint32_t id = static_cast<uint32_t>(std::stoul(lines[0]));
            std::string name = lines[1];
            uint32_t componentsCount = static_cast<uint32_t>(std::stoul(lines[2]));
            uint32_t componentsCapacity = static_cast<uint32_t>(std::stoul(lines[3]));

            ecs_core->createEntity(world, id, name, componentsCapacity);

            lines.clear();

            for (int i = 0; i < componentsCount; i++)
            {
                std::string compName;
                std::getline(file, compName);

                if (compName == "Movement")
                { 
                    std::string pla;
                    std::getline(file, pla);
                    uint32_t planenum = static_cast<uint32_t>(std::stoul(pla));
                    Plane planeenu;

                    Vec4 vec4;
                    if (planenum == 0) 
                    { 
                        planeenu = Plane::Vec2;

                        std::getline(file, pla);
                        vec4.x = static_cast<float>(std::stof(pla));

                        std::getline(file, pla);
                        vec4.y = static_cast<float>(std::stof(pla));

                        for (int i = 0; i < 2; i++) { std::getline(file, pla); }
                    }
                    else if (planenum == 1) 
                    { 
                        planeenu = Plane::Vec3;

                        std::getline(file, pla);
                        vec4.x = static_cast<float>(std::stof(pla));

                        std::getline(file, pla);
                        vec4.y = static_cast<float>(std::stof(pla));

                        std::getline(file, pla);
                        vec4.z = static_cast<float>(std::stof(pla));

                        for (int i = 0; i < 3; i++) { std::getline(file, pla); }
                    }
                    else 
                    { 
                        planeenu = Plane::Vec4;

                        std::getline(file, pla);
                        vec4.x = static_cast<float>(std::stof(pla));

                        std::getline(file, pla);
                        vec4.y = static_cast<float>(std::stof(pla));

                        std::getline(file, pla);
                        vec4.z = static_cast<float>(std::stof(pla));

                        std::getline(file, pla);
                        vec4.w = static_cast<float>(std::stof(pla));

                        for (int i = 0; i < 4; i++) { std::getline(file, pla); }
                    }

                    ecs_core->componentAttachment(world->entities.back(), systemMovement.addComponent(planeenu)); 
                    
                    if (planeenu == Plane::Vec2) 
                    { 
                        Vec2* pos = reinterpret_cast<Vec2*>(world->entities.back()->components.back()->buffer);
                        pos->x = vec4.x;
                        pos->y = vec4.y;
                    }
                    else if (planeenu == Plane::Vec3)
                    {
                        Vec3* pos = reinterpret_cast<Vec3*>(world->entities.back()->components.back()->buffer);
                        pos->x = vec4.x;
                        pos->y = vec4.y;
                        pos->z = vec4.z;
                    }
                    else
                    {
                        Vec4* pos = reinterpret_cast<Vec4*>(world->entities.back()->components.back()->buffer);
                        *pos = vec4;
                    }

                }
                else if (compName == "LifePoint")
                {
                    std::string lifepoint;
                    std::getline(file, lifepoint);
                    uint32_t lifese = static_cast<uint32_t>(std::stoul(lifepoint));
                    
                    ecs_core->componentAttachment(world->entities.back(), systemCombat.addComponent(lifese));

                    std::getline(file, lifepoint);
                }

            }
        
        }
    }
    file.close();
}

void ECS_IO::save(const World* world, const std::string& filename)
{
    // TODO: Реалізація збереження стану світу
    // 1. Відкрити файл для запису
    // 2. Пройти по всіх сутностях
    // 3. Записати їхні параметри
    // 4. Записати всі компоненти та їхні дані
}

void ECS_IO::unload(World* world, std::string& felename)
{

}

