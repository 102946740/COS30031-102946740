#include "Command.h"

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
        std::cout << "Must use a key to open this \n;";
    }
    std::string itemName = args[2];
    

    // Find the entity in the current location
    for (const auto& entity : (*currentLocation)->entities) {
        if (entity->Info.Name == entityName) {
            if (!entity->Interactable) {
                // Entity is not interactable, check if the item from inventory can be used
                bool itemFound = false;
                int count = 0;

                for (const auto& item : playerInventory.items) {
                    if (item.Info.Name == itemName) {
                        itemFound = true;
                        std::cout << "You use: " << itemName << " to open: " << entityName << ".\n";
                        entity->Interactable = true;
                        playerInventory.removeItem(count);

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
