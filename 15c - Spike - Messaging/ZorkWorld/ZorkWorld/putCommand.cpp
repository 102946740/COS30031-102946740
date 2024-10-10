#include "Command.h"

void PutCommand::execute(const std::vector<std::string>& args) {
    if (args.size() != 3) {
        std::cout << "Invalid command structure, requires 'put ITEM in CONTAINER.'\n";
        return;
    }

    if (args[1] != "in") {
        std::cout << "Invalid command structure, expected 'in' but got: " << args[1] << "\n";
        return;
    }

    std::string itemName = args[0];
    std::string containerName = args[2];

    // Find the container in the current location
    for (const auto& entity : (*currentLocation)->entities) {
        auto identifier = entity->compManager.getComponent<Identifier>();
        if (identifier && identifier->Name == containerName) {
            // Try to get the InventoryComp from the container entity
            auto containerInventory = entity->compManager.getComponent<InventoryComp>();
            if (containerInventory) {
                // Get the player's inventory component
                auto playerInventoryComp = playerInventory.compManager.getComponent<InventoryComp>();
                if (!playerInventoryComp) {
                    std::cout << "Player inventory not found.\n";
                    return;
                }

                // Search for the item in the player's inventory
                bool found = false;
                for (size_t count = 0; count < playerInventoryComp->Items.size(); ++count) {
                    // Access the item as a shared pointer
                    const auto& item = playerInventoryComp->Items[count];
                    auto itemIdentifier = item->compManager.getComponent<Identifier>();

                    if (itemIdentifier && itemIdentifier->Name == itemName) {
                        // Item found, move it to the container
                        std::cout << "You put: " << itemName << " in: " << containerName << ".\n";
                        found = true;

                        // Use shared_ptr to manage item ownership
                        containerInventory->addItem(item); // Add item to container

                        // Remove the item from player inventory using the correct index
                        playerInventoryComp->removeItem(count);
                        return;
                    }
                }

                if (!found) {
                    std::cout << "Could not find item: " << itemName << " in your inventory.\n";
                }
            }
            else {
                std::cout << "Entity '" << containerName << "' is not a valid container.\n";
            }
            return;
        }
    }

    std::cout << "Could not find container: " << containerName << " in this location.\n";
}
