#include "ecs_io.h"
#include "ecs.h"
#include "../data/math/vectors/vec2.h"
#include "../data/math/vectors/vec3.h"
#include "../data/math/vectors/vec4.h"

#include <string>
#include <fstream>
#include <json.hpp>

using nlojson = nlohmann::json;

void ECS_IO::load(World* world, const std::string& filename, ECS_Core* ecs_core, SystemManager* systemManager, Plane plane)
{
    std::ifstream file(filename);
    nlojson json;
    file >> json;

    if (!file.is_open()) { return; }

     for (auto& e : json["entities"])
    {
        uint32_t id = e["id"];
        std::string name = e["name"];
        uint32_t capacity = e["componentsCapacity"];
        uint32_t count = e["componentsCount"];
        
        ecs_core->createEntity(world, id, name, capacity);

        for (auto& c : e["components"])
        {
            std::string type = c["type"];

            if (type == "Movement")
            {
                ecs_core->componentAttachment(world->entities.back(), systemManager->systemMovement.addComponent(plane));

                if (plane == Plane::Vec2)
                {
                    Vec2* pos = reinterpret_cast<Vec2*>(world->entities.back()->components.back()->buffer);
                    Vec2* vel = reinterpret_cast<Vec2*>(world->entities.back()->components.back()->buffer + sizeof(Vec2));
                    pos->x = c["position"]["x"];
                    pos->y = c["position"]["y"];
                    vel->x = c["velocity"]["x"];
                    vel->y = c["velocity"]["y"];
                }
                else if (plane == Plane::Vec3)
                {
                    Vec3* pos = reinterpret_cast<Vec3*>(world->entities.back()->components.back()->buffer);
                    Vec3* vel = reinterpret_cast<Vec3*>(world->entities.back()->components.back()->buffer + sizeof(Vec3));
                    pos->x = c["position"]["x"];
                    pos->y = c["position"]["y"];
                    pos->z = c["position"]["z"];
                    vel->x = c["velocity"]["x"];
                    vel->y = c["velocity"]["y"];
                    vel->z = c["velocity"]["z"];
                }
                else if (plane == Plane::Vec4)
                {
                    Vec4* pos = reinterpret_cast<Vec4*>(world->entities.back()->components.back()->buffer);
                    Vec4* vel = reinterpret_cast<Vec4*>(world->entities.back()->components.back()->buffer + sizeof(Vec4));
                    pos->x = c["position"]["x"];
                    pos->y = c["position"]["y"];
                    pos->z = c["position"]["z"];
                    pos->w = c["position"]["w"];
                    vel->x = c["velocity"]["x"];
                    vel->y = c["velocity"]["y"];
                    vel->z = c["velocity"]["z"];
                    vel->w = c["velocity"]["w"];
                }
            }
            else if (type == "LifePoint")
            {
                ecs_core->componentAttachment(world->entities.back(), systemManager->systemCombat.addComponent(c["life"]));
                int32_t* hit = reinterpret_cast<int32_t*>(world->entities.back()->components.back()->buffer + sizeof(int32_t));
                *hit = c["hit"];
            }
          
        }
    }
}

void ECS_IO::save(const World* world, const std::string& filename, Plane plane)
{
    nlojson savejson;
    savejson["entitiesCount"] = world->entitiesCount;
    savejson["entities"] = nlojson::array();

    for (auto entity : world->entities)
    {
        nlojson entityjson = {
            {"id", entity->id},
            {"name", entity->name}, 
            {"componentsCapacity", entity->componentsCapacity},
            {"componentsCount", entity->componentsCount}
        };

        nlojson compsjson = nlojson::array();
        for (auto comp : entity->components)
        {
            nlojson compjson;
            compjson["type"] = comp->type;

            if (comp->type == "Movement")
            {
                if (plane == Plane::Vec2)
                {
                    Vec2* pos = reinterpret_cast<Vec2*>(comp->buffer);
                    Vec2* vel = reinterpret_cast<Vec2*>(comp->buffer + sizeof(Vec2));
                    compjson["plane"] = "Vec2";
                    compjson["position"] = { {"x", pos->x}, {"y", pos->y} };
                    compjson["velocity"] = { {"x", vel->x}, {"y", vel->y} };
                }
                else if (plane == Plane::Vec3)
                {
                    Vec3* pos = reinterpret_cast<Vec3*>(comp->buffer);
                    Vec3* vel = reinterpret_cast<Vec3*>(comp->buffer + sizeof(Vec3));
                    compjson["plane"] = "Vec3";
                    compjson["position"] = { {"x", pos->x}, {"y", pos->y}, {"z", pos->z} };
                    compjson["velocity"] = { {"x", vel->x}, {"y", vel->y}, {"z", vel->z} };
                }
                else if (plane == Plane::Vec4)
                {
                    Vec4* pos = reinterpret_cast<Vec4*>(comp->buffer);
                    Vec4* vel = reinterpret_cast<Vec4*>(comp->buffer + sizeof(Vec4));
                    compjson["plane"] = "Vec4";
                    compjson["position"] = { {"x", pos->x}, {"y", pos->y}, {"z", pos->z}, {"w", pos->w} };
                    compjson["velocity"] = { {"x", vel->x}, {"y", vel->y}, {"z", vel->z}, {"w", vel->w} };
                }
            }
            else if (comp->type == "LifePoint")
            {
                int32_t* life = reinterpret_cast<int32_t*>(comp->buffer);
                int32_t* hit  = reinterpret_cast<int32_t*>(comp->buffer + sizeof(int32_t));
                compjson["life"] = *life;
                compjson["hit"]  = *hit;
            }

            compsjson.push_back(compjson);
        }

        entityjson["components"] = compsjson;
        savejson["entities"].push_back(entityjson);
    }

    std::ofstream file(filename);
    file << savejson.dump(4);
}

void ECS_IO::unload(World* world, std::string& felename)
{

}

