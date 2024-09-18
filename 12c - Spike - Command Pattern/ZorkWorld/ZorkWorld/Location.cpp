#include "Location.h"

void Location::loadFromJson(const nlohmann::json& json)
{
    name = json.value("Name", "");
    description = json.value("Description", "");
    items = json.value("Items", std::vector<std::string>{});
    connections = json.value("Connections", std::vector<std::string>{});

    if (json.contains("Entities")) {
        for (const auto& entityJson : json["Entities"]) {
            Entity entity;
            entity.loadFromJson(entityJson);
            entities.push_back(entity);
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
        entity.printEntity();
    }
    std::cout << "\n";
}