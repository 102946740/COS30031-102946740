#include "Inventory.h"

void Entity::loadFromJson(const nlohmann::json& json)
{
    if (json.contains("Name")) {
        Info.Name = json["Name"];
    }
    if (json.contains("Description")) {
        Info.Description = json["Description"];
    }
}

void Entity::printEntity() const
{
    std::cout << Info.Name << ": " << Info.Description << "\n";
}
