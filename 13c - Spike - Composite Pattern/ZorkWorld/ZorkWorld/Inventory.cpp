#include "Inventory.h"

void Inventory::addItem(Item ItemAdded)
{
    items.push_back(ItemAdded);
}

void Inventory::removeItem(int index)
{
    std::cout << "Removed: " << items[index].Info.Name << "\n";
    items.erase(items.begin() + index);
}

void Inventory::printEntity() const
{
    std::cout << Info.Name << ": " << Info.Description << ": CONTAINER" << "\n";
}

void Inventory::printInventory() const
{
    std::cout << "Showing Inventory of " << Info.Name << "\n";
    int count = 1;
    for (auto& item : items) {
        std::cout << count << ": " << item.Info.Name << ": Desctiption - " << item.Info.Description << ": Modifier - " << item.Info.EffectMod << "\n";

        count++;
    }
    std::cout << "\nEnd of inventory\n\n";
}
