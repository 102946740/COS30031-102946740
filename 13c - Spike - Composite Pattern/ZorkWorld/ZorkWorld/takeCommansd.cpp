#include "Command.h"

void takeCommand::execute(const std::vector<std::string>& args) {
    if (!(args.size() == 1 || args.size() == 3)) {
        std::cout << "Invalid command structure. Requires 'take ITEM' or 'take ITEM from CONTAINER.'\n SIZE:" << args.size();
        return;
    }

    std::string itemName = args[0];

    if (args.size() == 3) {  // Case: 'take ITEM from CONTAINER'
        if (args[1] != "from") {
            std::cout << "Invalid command structure, expected 'from' but got: " << args[1] << std::endl;
            return;
        }
        std::string entityName = args[2];

        for (const auto& entity : (*currentLocation)->entities) {
            if (entity->Info.Name == entityName) {
                Inventory* inv = dynamic_cast<Inventory*>(entity.get()); // Check if entity is an inventory
                if (inv) {
                    if (!inv->Interactable) {
                        std::cout << "Container is locked\n";
                        return;
                    };
                    bool found = false;
                    int count = 0;
                    for (const auto& item : inv->items) {
                        if (item.Info.Name == itemName && item.Interactable) {
                            std::cout << "You took: " << itemName << " from: " << entityName << ".\n";
                            found = true;
                            playerInventory.addItem(item); // Add to player inventory
                            inv->removeItem(count); // Remove from container inventory
                            return;
                        }
                        count++;
                    }
                    if (!found) {
                        std::cout << "Could not find item: " << itemName << " in " << entityName << ".\n";
                    }
                }
                else {
                    std::cout << "Entity '" << entityName << "' is not a valid container.\n";
                }
                return;
            }
        }
        std::cout << "Could not find container: " << entityName << " in this location.\n";
    }
    else if (args.size() == 1) {  // Case: 'take ITEM'
        // Take the item directly from the location
        bool found = false;
        int count = 0;
        for (auto it = (*currentLocation)->entities.begin(); it != (*currentLocation)->entities.end(); ++it) {
            if ((*it)->Info.Name == itemName) {
                Item* item = dynamic_cast<Item*>((*it).get()); // Check if it's a direct item
                if (item && item->Interactable) {
                    std::cout << "You took: " << itemName << " from the location.\n";
                    playerInventory.addItem(*item); // Add item to player inventory
                    (*currentLocation)->entities.erase(it); // Remove item from location
                    found = true;
                    return;
                }
            }
            count++;
        }
        if (!found) {
            std::cout << "Could not find item: " << itemName << " in the current location.\n";
        }
    }
}
