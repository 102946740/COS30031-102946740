#include "Command.h"
#include <iostream>
#include <vector>
#include <memory>

void OpenCommand::execute(const std::vector<std::string>& args) {
    if (args.size() != 3) {
        std::cout << "Invalid command structure. Requires 'open ENTITY with ITEM.'\n";
        return;
    }

    if (args[1] != "with") {
        std::cout << "Invalid command structure, expected 'with' but got: " << args[1] << std::endl;
        return;
    }

    std::string entityName = args[0];

    if (args[2] != "Key") {
        std::cout << "Must use a key to open this.\n";
        return;
    }
    std::string itemName = args[2];

    // Find the entity in the current location
    for (const auto& entity : (*currentLocation)->entities) {
        // Dynamic cast to Inventory (assuming Inventory is a base class for your entities)
        auto inventoryEntity = dynamic_cast<Inventory*>(entity.get());
        if (inventoryEntity && inventoryEntity->ID.Name == entityName) {
            if (!inventoryEntity->Inv.Interactable) {
                // Entity is not interactable, check if the item from inventory can be used
                bool itemFound = false;
                int count = 0;

                for (const auto& item : playerInventory.Inv.Items) {
                    if (item.ID.Name == itemName) {
                        itemFound = true;
                        std::cout << "You use: " << itemName << " to open: " << entityName << ".\n";
                        inventoryEntity->Inv.Interactable = true;
                        playerInventory.Inv.removeItem(count);
                        return;
                    }
                    count++;
                }

                if (!itemFound) {
                    std::cout << "Could not find item: " << itemName << " in your inventory.\n";
                }
            }
            else {
                std::cout << "Entity '" << entityName << "' is already interactable.\n";
            }
            return;
        }
    }

    std::cout << "Could not find entity: " << entityName << " in this location.\n";
}
