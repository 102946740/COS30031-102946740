#include "Command.h"
void putCommand::execute(const std::vector<std::string>& args) {
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
        if (entity->ID.Name == containerName) {
            Inventory* container = dynamic_cast<Inventory*>(entity.get());
            if (container) {
                // Search for the item in the player's inventory
                bool found = false;
                int count = 0;
                for (const auto& item : playerInventory.Inv.Items) {
                    if (item.ID.Name == itemName) {
                        // Item found, move it to the container
                        std::cout << "You put: " << itemName << " in: " << containerName << ".\n";
                        found = true;
                        Item itemToMove; // Creates temp item
                        itemToMove.ID = item.ID; // Applies item info
                        container->Inv.addItem(itemToMove);
                        playerInventory.Inv.removeItem(count); // Removes item from player inventory
                        return;
                    }
                    count++;
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
