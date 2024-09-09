#include "Inventory.h"

item::item(itemStruc NewItem){
    Info = NewItem;
}

void Inventory::AddItem(item ItemAdded)
{
    items.push_back(ItemAdded);
    std::cout << "Added: " << ItemAdded.Info.Name << "\n";
}

void Inventory::RemoveItem(int index)
{
    std::cout << "Removed: " << items[index].Info.Name << "\n";
    items.erase(items.begin() + index);
}

void Inventory::ShowInventory()
{
    std::cout << "Showing Inventory \n";
    int count = 1;
    for (auto& item : items) {
        std::cout << count << ": " << item.Info.Name << ": Desctiption - " << item.Info.Description << "\n";

        count++;
    }
    std::cout << "\nEnd of inventory\n\n";
}
