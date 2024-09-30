#include "Inventory.h"

void Entity::loadFromJson(const nlohmann::json& json)
{
    if (json.contains("Name")) {
        ID.Name = json["Name"];
    }
    if (json.contains("Description")) {
        ID.Description = json["Description"];
    }
}

void Entity::printEntity() const
{
    std::cout << ID.Name << ": " << ID.Description << "\n";
}
