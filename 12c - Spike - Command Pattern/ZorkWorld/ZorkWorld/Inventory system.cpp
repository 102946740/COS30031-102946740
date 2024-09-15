// Inventory system.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
#include "Inventory.h"
#include <iostream>
#include <vector>

class GameObject {

};



class item : public GameObject { // we make a class to store the item struct so we can add individual method overides for things like USE(), using a sword vs using a Potion will act differently
    
public:
    itemStruc Info;

};


class Inventory : public GameObject{
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

