#include "Command.h"

void InventoryCommand::execute(const std::vector<std::string>& args) {
    // Check if the player inventory component exists
    auto playerInventoryComp = playerInventory.compManager.getComponent<InventoryComp>();
    if (playerInventoryComp) {
        playerInventoryComp->printInventory("Player"); 
    }
    else {
        std::cout << "Player inventory not found.\n";
    }
}
