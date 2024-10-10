#include "Entity.h"
#include <iostream>

void Entity::loadFromJson(const nlohmann::json& json) {
    // Load components based on JSON data
    if (json.contains("Identifier")) {
        auto identifier = std::make_shared<Identifier>();
        identifier->Name = json["Identifier"].value("Name", "Unnamed Entity");
        identifier->Description = json["Identifier"].value("Description", "No Description");
        compManager.addComponent(identifier);
    }

    // You can add more component loading here based on your needs
}

void Entity::printEntity() const {
    // Print details of the entity
    auto identifier = compManager.getComponent<Identifier>();
    if (identifier) {
        std::cout << "Entity Name: " << identifier->Name << "\n";
        std::cout << "Description: " << identifier->Description << "\n";
    }
    auto stats = compManager.getComponent<Attributes>();
    if (stats) {
        std::cout << "HP: " << stats->HP << "\n";
        std::cout << "Damage: " << stats->Damage << "\n";
    }
}
