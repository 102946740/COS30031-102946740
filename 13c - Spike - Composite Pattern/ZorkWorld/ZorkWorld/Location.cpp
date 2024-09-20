#include "Location.h"

void Location::loadFromJson(const nlohmann::json& json)
{
    name = json.value("Name", "");
    description = json.value("Description", "");
    items = json.value("Items", std::vector<std::string>{});
    connections = json.value("Connections", std::vector<std::string>{});

    if (json.contains("Entities")) {
        for (const auto& entityJson : json["Entities"]) {
            if (entityJson.contains("Inventory")) {  // Checks json if its inventory

                auto inventory = std::make_shared<Inventory>();
                inventory->loadFromJson(entityJson);

                for (const auto& inventoryJson : entityJson["Inventory"]) {
                    auto item = std::make_shared<Item>();
                    item->loadFromJson(inventoryJson);
                    inventory->addItem(*item);
                }
                entities.push_back(inventory);
            }
            else {  // Regular item
                auto item = std::make_shared<Item>();
                item->loadFromJson(entityJson);
                entities.push_back(item);
            }
        }
    }
}

void Location::printLocation() const
{
    std::cout << "You are at: " << name << "\nDescription: " << description << "\n";
    std::cout << "Items: ";
    for (const auto& item : items) {
        std::cout << item << ", ";
    }
    std::cout << "\nConnections: ";
    for (const auto& connection : connections) {
        std::cout << connection << ", ";
    }
    std::cout << "\nEntities: ";
    for (const auto& entity : entities) {
        entity->printEntity();  // Call the appropriate printEntity() based on the actual type
    }
    std::cout << "\n";
}
