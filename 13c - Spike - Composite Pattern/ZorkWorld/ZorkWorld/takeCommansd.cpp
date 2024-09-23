#include "Command.h"
void takeCommand::execute(const std::vector<std::string>& args) {
    if (args.size() != 3) {
        std::cout << "Invalid command structure, requires 'take ITEM from CONTAINER.'\n";
        return;
    }
    if (args[1] != "from") {
        std::cout << "Invalid commandn structure.\n" << args[1];
        return;
    }
    std::string entityName = args[2];
    for (const auto& entity : (*currentLocation)->entities) {
        if (entity->Info.Name == entityName) {
            Inventory* inv = dynamic_cast<Inventory*>(entity.get()); //casts to check if entity is an inventory
            if (inv) {
                std::string itemName = args[0];
                bool found = false;
                int count = 0;
                for (const auto& item : (inv->items)) {

                    if (item.Info.Name == itemName) {
                        std::cout << "yout took: " << itemName << " From: " << entityName << ".\n";
                        found = true;
                        Item itemToAdd; //creates temp item
                        itemToAdd.Info = item.Info; //applies item info
                        playerInventory.addItem(item);
                        inv->removeItem(count);//removes item based on count index
                        return;
                    }
                    count++;
                }
                if (!found) {
                    std::cout << "Could not find item: " << args[0];
                    return;
                };
            }
            else {
                std::cout << "Entity is not an Inventory." << std::endl;
            }
            return;
        }
    }
}