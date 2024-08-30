// Inventory system.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <vector>

enum ItemType
{
    Weapon, Consumeable, Other
};

struct itemStruc {
    std::string Identifier;
    std::string Name;
    std::string Description;
    int EffectMod;
};

class item {
    
public:
    itemStruc Info;
    item(itemStruc NewItem) {
        Info = NewItem;
    }
};


class Inventory {
private:
    std::vector<item> items;

public:
    void AddItem(item ItemAdded) {
        items.push_back(ItemAdded);
        std::cout << "Added: " << ItemAdded.Info.Name << "\n";
    }
    void RemoveItem(int index) {
        std::cout << "Removed: " << items[index].Info.Name << "\n";
        items.erase(items.begin() + index);
    }
    void ShowInventory() {
        std::cout << "Showing Inventory \n";
        int count = 1;
        for (auto &item : items) {
            std::cout << count << ": " << item.Info.Name << ": Desctiption - " << item.Info.Description << "\n";

            count++;
        }
        std::cout << "\nEnd of inventory\n\n";
    }
};


int main()
{
    Inventory Test;
    item Sword({"Sword", "BroadSword", "This blade made of steel is a broadsword", 10});
    item Potion({ "Potion", "Healing Potion", "This potion when consumes, will heal you for 10 hp", 10});
    Test.AddItem(Sword);
    Test.AddItem(Potion);
    Test.ShowInventory();
    Test.RemoveItem(0);
    Test.ShowInventory();
}

