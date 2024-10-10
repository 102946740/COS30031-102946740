#include "Command.h"
#include <iostream>
#include <vector>
#include <memory>

void OpenCommand::execute(const std::vector<std::string>& args) {
    // Validate command structure: 'open ENTITY with ITEM'
    if (args.size() != 3) {
        std::cout << "Invalid command structure. Requires 'open ENTITY with ITEM.'\n";
        return;
    }

    if (args[1] != "with") {
        std::cout << "Invalid command structure, expected 'with' but got: " << args[1] << std::endl;
        return;
    }

    std::string entityName = args[0]; // ENTITY
    std::string itemName = args[2];   // ITEM (e.g., "Key")

    // Check if the item is supposed to be a "Key"
    if (itemName != "Key") {
        std::cout << "You can only open this with a key.\n";
        return;
    }

    // Search for the entity in the current location
    for (const auto& entity : (*currentLocation)->entities) {
        auto identifier = entity->compManager.getComponent<Identifier>();
        if (identifier && identifier->Name == entityName) {
            // Check if the entity has an InventoryComp
            auto invComp = entity->compManager.getComponent<InventoryComp>();
            if (invComp) {
                // Check if the entity is interactable (e.g., locked or unlocked)
                if (!invComp->Interactable) {
                    // Entity is locked, check if the player has the "Key"
                    bool itemFound = false;

                    // Get the player's inventory component
                    auto playerInventoryComp = playerInventory.compManager.getComponent<InventoryComp>();
                    if (!playerInventoryComp) {
                        std::cout << "Player inventory not found.\n";
                        return;
                    }

                    // Search for the key in the player's inventory
                    for (size_t count = 0; count < playerInventoryComp->Items.size(); ++count) {
                        const auto& item = playerInventoryComp->Items[count];
                        auto itemIdentifier = item->compManager.getComponent<Identifier>();
                        if (itemIdentifier && itemIdentifier->Name == itemName) {
                            itemFound = true;
                            std::cout << "You use: " << itemName << " to open: " << entityName << ".\n";

                            // Make the entity interactable (unlock it)
                            invComp->Interactable = true;

                            // Remove the key from player's inventory
                            playerInventoryComp->removeItem(count);
                            return;
                        }
                    }

                    if (!itemFound) {
                        std::cout << "Could not find item: " << itemName << " in your inventory.\n";
                    }
                }
                else {
                    std::cout << "Entity '" << entityName << "' is already interactable.\n";
                }
            }
            else {
                std::cout << "Entity '" << entityName << "' does not have an inventory component.\n";
            }
            return;
        }
    }

    // If no matching entity is found in the current location
    std::cout << "Could not find entity: " << entityName << " in this location.\n";
}
