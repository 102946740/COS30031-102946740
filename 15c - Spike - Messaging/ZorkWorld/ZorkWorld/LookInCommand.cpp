#include "Command.h"
#include "Entity.h"

void LookInCommand::execute(const std::vector<std::string>& args) {
    if (args.size() < 1) {
        std::cout << "Please specify an entity to look in.\n";
        return;
    }

    std::string entityName = args[0];

    if (currentLocation == nullptr || *currentLocation == nullptr) {
        std::cout << "Current location is not set.\n";
        return;
    }

    for (const auto& entity : (*currentLocation)->entities) {
        auto identifier = entity->compManager.getComponent<Identifier>(); 
        if (identifier && identifier->Name == entityName) {
            auto inv = entity->compManager.getComponent<InventoryComp>();
            if (inv) {
                if (inv->Interactable) {
                    inv->printInventory(identifier->Name);
                }
                else {
                    std::cout << "This container is locked.\n";
                }
                return;
            }
            else {
                std::cout << "Entity is not an Inventory.\n";
                return;
            }
        }
    }

    std::cout << "Entity '" << entityName << "' not found in this location.\n";
}
