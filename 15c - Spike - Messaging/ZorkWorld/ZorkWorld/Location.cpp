#include "Location.h"

void Location::loadFromJson(const nlohmann::json& json, MessageHandler& Messenger) {
    name = json.value("Name", "");
    description = json.value("Description", "");
    connections = json.value("Connections", std::vector<std::string>{});

    if (json.contains("Entities")) {
        for (const auto& entityJson : json["Entities"]) {
            auto entity = std::make_shared<Entity>();

            // Create Identifier Component
            auto identifier = std::make_shared<Identifier>();
            identifier->Name = entityJson.value("Name", "Unnamed");
            identifier->Description = entityJson.value("Description", "No description");
            entity->compManager.addComponent<Identifier>(identifier); // Add Identifier component

            // Check for inventory
            if (entityJson.contains("Inventory")) {
                auto inventoryComp = std::make_shared<InventoryComp>(); 
                inventoryComp->Interactable = false;

                for (const auto& itemJson : entityJson["Inventory"]) {
                    auto item = std::make_shared<Entity>();

                    // Create Identifier for item
                    auto itemIdentifier = std::make_shared<Identifier>();
                    itemIdentifier->Name = itemJson.value("Name", "Unnamed"); // Correctly get the item's name
                    itemIdentifier->Description = itemJson.value("Description", "No description"); // Correctly get the item's description
                    item->compManager.addComponent<Identifier>(itemIdentifier); // Add Identifier for item

                    // create and add item stats component
                    auto itemStats = std::make_shared<Attributes>();
                    itemStats->Damage = itemJson.value("Damage", 0);
                    itemStats->HP = itemJson.value("Health", 0);

                    item->compManager.addComponent<Attributes>(itemStats);

                    inventoryComp->addItem(item); // Add item to inventory


                }
                entity->compManager.addComponent<InventoryComp>(inventoryComp); // Add InventoryComp to the entity
            }
            else { //if not inventory, add item stats
                // create and add item stats component
                auto itemStats = std::make_shared<Attributes>();
                itemStats->Damage = entityJson.value("Damage", 0);
                itemStats->HP = entityJson.value("Health", 0);

                entity->compManager.addComponent<Attributes>(itemStats);
            }

            entities.push_back(entity);
            
            Messenger.Entities.insert({ identifier->Name, entity }); //adds to messenger umap
        }
    }
}

void Location::printLocation() const {
    std::cout << "You are at: " << name << "\nDescription: " << description << "\n";
    std::cout << "Connections: ";
    for (const auto& connection : connections) {
        std::cout << connection << ", ";
    }
    std::cout << "\nEntities: ";
    for (const auto& entity : entities) {
        entity->printEntity();
    }
    std::cout << "\n";
}
