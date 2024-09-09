#pragma once
#include <iostream>
#include <vector>
#include <string>
class GameObject {
};

struct itemStruc {
    std::string Identifier;
    std::string Name;
    std::string Description;
    int EffectMod;
};

class item : public GameObject {
public:
    itemStruc Info;
    item(itemStruc NewItem);
};

class Inventory : public GameObject {
private:
    std::vector<item> items;

public:
    void AddItem(item ItemAdded);
    void RemoveItem(int index);
    void ShowInventory();
};