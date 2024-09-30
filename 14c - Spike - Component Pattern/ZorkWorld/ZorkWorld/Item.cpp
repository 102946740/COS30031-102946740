#include "Inventory.h"


void Item::loadFromJson(const nlohmann::json& json)
{
    if (json.contains("Name")) {
        ID.Name = json["Name"];
    }
    if (json.contains("Description")) {
        ID.Description = json["Description"];
    }
    if (json.contains("Modifier")) {
        stats.Damage = json["Modifier"];
    }
}
void Item::printEntity() const
{
    std::cout << ID.getIdentifiers() << stats.getDetails() << "\n";
}