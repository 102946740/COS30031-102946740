#include "Inventory.h"

void Item::loadFromJson(const nlohmann::json& json)
{
    if (json.contains("Name")) {
        Info.Name = json["Name"];
        Info.Identifier = json["Name"];
    }
    if (json.contains("Description")) {
        Info.Description = json["Description"];
    }
    if (json.contains("Modifier")) {
        Info.EffectMod = json["Modifier"];
    }
}
void Item::printEntity() const
{
    std::cout << Info.Name << ": " << Info.Description << ": " << Info.EffectMod << "\n";
}