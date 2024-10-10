#pragma once
#include "Command.h"
#include "ComponentManager.h"
#include "Componants.h"
void AttackCommand::execute(const std::vector<std::string>& args) {
    if (args.size() != 3) {
        std::cout << "Invalid command structure, must use 'attack ENTITYNAME with INVENTORYITEMNAME' \n";
        return;
    }
    else if (args[1] != "with") {
        std::cout << "Invalid command structure, must use 'attack ENTITYNAME with INVENTORYITEMNAME' \n";
        return;
    }

    std::string itemName = args[2];

    auto playerInventoryComp = playerInventory.compManager.getComponent<InventoryComp>();
    if (!playerInventoryComp) {
        std::cout << "Player inventory not found.\n";
        return;
    }
    for (size_t count = 0; count < playerInventoryComp->Items.size(); ++count) {
        const auto& item = playerInventoryComp->Items[count];
        auto itemIdentifier = item->compManager.getComponent<Identifier>();
        if (itemIdentifier && itemIdentifier->Name == itemName) {

            if (messenger.attack(args[0], itemName)) {
                std::cout << "Atatcked: " << args[0] << " With: " << itemName << "\n";
            }
            else {
                std::cout << "Attack failed, target not valid\n";
            }
            
            return;
        }
    }
    std::cout << "Could not find item in inventory\n";
    return;
}
