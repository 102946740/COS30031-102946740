#include "Inventory.h"

void Inventory::addItem(Item ItemAdded)
{
    items.push_back(ItemAdded);
}

void Inventory::removeItem(int index)
{
    std::cout << "Removed: " << items[index].ID.Name << "\n";
    items.erase(items.begin() + index);
}

void Inventory::printEntity() const
{
    std::cout << ID.getIdentifiers() << stats.getDetails() << "\n";
}

void Inventory::printInventory() const
{
    std::cout << "Showing Inventory of " << ID.Name << "\n";
    int count = 1;
    for (Item item : items) {
        std::cout << "Name: " << ID.Name << ", Description" << ID.Description << ", " << item.stats.getDetails();

        count++;
    }
    std::cout << "\nEnd of inventory\n\n";
}
