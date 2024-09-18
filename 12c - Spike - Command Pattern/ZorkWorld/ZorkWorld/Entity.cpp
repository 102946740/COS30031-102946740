#include "Entity.h"

void Entity::loadFromJson(const nlohmann::json& json)
{
    if (json.contains("Name")) {
        name = json["Name"];
    }
    if (json.contains("Description")) {
        description = json["Description"];
    }
}

void Entity::printEntity() const
{
    std::cout << name << ": " << description << "\n";
}
