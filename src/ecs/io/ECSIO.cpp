#include "ECSIO.h"
#include "../../data/math/vec4.h"

#include <iostream>
#include <fstream>
#include <json.hpp>
#include <filesystem>
#include <iostream>

using nlojson = nlohmann::json;

void ECSIO::load(World* world, const std::string& filename, ECSCore* ecsCore, SystemManager* systemManager)
{
    if (!std::filesystem::exists(filename))
    {
        std::clog << "[IO] Save file not found: " << filename << std::endl;
        return;
    }

    std::ifstream file(filename);
    if (!file.is_open()) { std::cerr << "[IO] Failed to open " << filename << std::endl; return; }

    nlojson mainJson;
    try
    {
        file >> mainJson;
    }
    catch (const std::exception& ex)
    {
        std::cerr << "[IO] Error loading JSON: " << ex.what() << std::endl; 
    }
    
    for (auto& e : mainJson["entities"])
    {
        uint32_t id = e["id"];
        std::string name = e["name"];
        uint32_t capacity = e["componentsCapacity"];
        uint32_t count = e["componentsCount"];

        ecsCore->createEntity(world, id, name, capacity);

        std::clog << "[IO] Entity loaded: id=" << id << " name=" << name << std::endl;

        for (auto& c : e["components"])
        {
            std::string type = c["type"];

            if (type == "Movement")
            {
                ecsCore->componentAttachment(world->entities.back(), systemManager->getSystemMovement()->addComponent());
                Vec4* pos = reinterpret_cast<Vec4*>(world->entities.back()->components.back()->buffer);
                Vec4* move = reinterpret_cast<Vec4*>(world->entities.back()->components.back()->buffer + sizeof(Vec4));
                pos->x = c["position"]["x"];
                pos->y = c["position"]["y"];
                pos->z = c["position"]["z"];
                pos->w = c["position"]["w"];
                move->x = c["move"]["x"];
                move->y = c["move"]["y"];
                move->z = c["move"]["z"];
                move->w = c["move"]["w"];

                std::clog << "[IO] Movement loaded for entity " << name << std::endl;
            }
            else if (type == "LifePoint")
            {
                ecsCore->componentAttachment(world->entities.back(), systemManager->getSystemCombat()->addComponent(c["life"]));
                int32_t* hit = reinterpret_cast<int32_t*>(world->entities.back()->components.back()->buffer + sizeof(int32_t));
                *hit = c["health"];
                std::clog << "[IO] LifePoint loaded for entity " << name << " life=" << c["life"] << " health=" << c["health"] << std::endl;
            }
        }
    }
}

void ECSIO::save(const World* world, const std::string& filename)
{
    nlojson mainJson;
    mainJson["entitiesCount"] = world->entitiesCount;
    mainJson["entities"] = nlojson::array();

    for (auto entity : world->entities)
    {
        nlojson entityJson = {
            {"id", entity->id},
            {"name", entity->name}, 
            {"componentsCapacity", entity->componentsCapacity},
            {"componentsCount", entity->componentsCount}
        };

        nlojson compsJson = nlojson::array();
        for (auto comp : entity->components)
        {
            nlojson compJson;
            compJson["type"] = comp->type;

            if (comp->type == "Movement")
            {
                Vec4* pos = reinterpret_cast<Vec4*>(comp->buffer);
                Vec4* move = reinterpret_cast<Vec4*>(comp->buffer + sizeof(Vec4));

                compJson["position"] = { {"x", pos->x}, {"y", pos->y}, {"z", pos->z}, {"w", pos->w} };
                compJson["move"] = { {"x", move->x}, {"y", move->y}, {"z", move->z}, {"w", move->w} };
            }
            else if (comp->type == "LifePoint")
            {
                int32_t* life = reinterpret_cast<int32_t*>(comp->buffer);
                int32_t* health  = reinterpret_cast<int32_t*>(comp->buffer + sizeof(int32_t));
                compJson["life"] = *life;
                compJson["health"]  = *health;
            }
            compsJson.push_back(compJson);
        }
        entityJson["components"] = compsJson;
        mainJson["entities"].push_back(entityJson);
    }
    std::ofstream file(filename);
    if (!file.is_open()) { std::cerr << "[IO] Failed to open " << filename << std::endl; return; }

    try 
    {
        file << mainJson.dump(4);
        std::clog << "[IO] Saved " << world->entitiesCount << " entities to " << filename << std::endl;
    } 
    catch (const std::exception& ex)
    {
        std::cerr << "[IO] Error saving JSON: " << ex.what() << std::endl;
    }
}
