#include "Command.h"

void InventoryCommand::execute(const std::vector<std::string>& args)
{
    playerInventory.Inv.printInventory(playerInventory.ID.Name);
}
