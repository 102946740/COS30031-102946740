#include "Command.h"
#include "Inventory.h"
void LookInCommand::execute(const std::vector<std::string>& args)
{
    if (args.size() < 1) {
        std::cout << "Please specify an entity to look in.\n";
        return;
    }

    std::string entityName = args[0];
    for (const auto& entity : (*currentLocation)->entities) {
        if (entity->ID.Name == entityName) {
            Inventory* inv = dynamic_cast<Inventory*>(entity.get()); //casts to check if entity is an inventory
            if (inv->Interactable) {
                if (inv) {
                    inv->printInventory();
                }
                else {
                    std::cout << "Entity is not an Inventory.\n";
                }
                return;
            }
            else {
                std::cout << "This Container is Locked.\n";
                return;
            }
        }

    }

    std::cout << "Entity '" << entityName << "' not found in this location.\n";
}