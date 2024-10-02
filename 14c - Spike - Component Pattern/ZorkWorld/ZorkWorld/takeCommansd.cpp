#include "Command.h"

void TakeCommand::execute(const std::vector<std::string>& args) {
    // Check command structure
    if (!(args.size() == 1 || args.size() == 3)) {
        std::cout << "Invalid command structure. Requires 'take ITEM' or 'take ITEM from CONTAINER.'\n";
        return;
    }

    std::string itemName = args[0];

    // Case: 'take ITEM from CONTAINER'
    if (args.size() == 3) {
        if (args[1] != "from") {
            std::cout << "Invalid command structure, expected 'from' but got: " << args[1] << std::endl;
            return;
        }

        std::string containerName = args[2];

        // Search for the container in the current location
        bool containerFound = false;
        for (const auto& entity : (*currentLocation)->entities) {
            auto identifier = entity->compManager.getComponent<Identifier>();
            if (identifier->Name == containerName) {
                containerFound = true;  // Container found
                auto invComp = entity->compManager.getComponent<InventoryComp>();

                if (invComp) {
                    if (!invComp->Interactable) {
                        std::cout << "Container is locked.\n";
                        return;
                    }

                    // Look for the item inside the container
                    bool itemFound = false;
                    for (size_t count = 0; count < invComp->Items.size(); ++count) {
                        const auto& item = invComp->Items[count];
                        auto itemIdentifier = item->compManager.getComponent<Identifier>();
                        if (itemIdentifier->Name == itemName) {
                            auto itemAttributes = item->compManager.getComponent<Attributes>();
                                std::cout << "You took: " << itemName << " from: " << containerName << ".\n";

                                // Add item to player inventory
                                playerInventory.compManager.getComponent<InventoryComp>()->addItem(item);

                                // Remove item from container
                                invComp->removeItem(count);
                                itemFound = true;
                                break; // Exit the loop after item is found and removed
                            
                        }
                    }

                    if (!itemFound) {
                        std::cout << "Could not find item: " << itemName << " in " << containerName << ".\n";
                    }
                }
                else {
                    std::cout << "Entity '" << containerName << "' is not a valid container.\n";
                }
                return; // Exit after processing the container
            }
        }
        if (!containerFound) {
            std::cout << "Could not find container: " << containerName << " in this location.\n";
        }
    }

    // Case: 'take ITEM' from location
    else if (args.size() == 1) {
        bool found = false;

        // Search for the item in the current location
        for (auto it = (*currentLocation)->entities.begin(); it != (*currentLocation)->entities.end(); ) {
            auto identifier = (*it)->compManager.getComponent<Identifier>();

            if (identifier && identifier->Name == itemName) {
                found = true;

                std::cout << "You took: " << itemName << " from the location.\n";

                // Add item to player inventory
                playerInventory.compManager.getComponent<InventoryComp>()->addItem(*it);

                // Remove item from location
                it = (*currentLocation)->entities.erase(it);
            }
            else {
                ++it; // Move to the next item
            }
        }

        if (!found) {
            std::cout << "Could not find item: " << itemName << " in the current location.\n";
        }
    }
}
