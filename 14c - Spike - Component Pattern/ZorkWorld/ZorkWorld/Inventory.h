#pragma once
#include <iostream>
#include <vector>
#include <string>
#include "json.hpp"
#include "Entity.h"
#include "Componants.h"

class Item : public Entity{
public:
    Item() = default;

    Attributes stats; //Attributes componant
    void loadFromJson(const nlohmann::json& json);
    void printEntity() const override;
};

class Inventory : public Entity{

public:
    Attributes stats; //Attributes componants
    std::vector<Item> items;
    void addItem(Item ItemAdded);
    void removeItem(int index);
    void printEntity() const override;
    void printInventory() const;
    
};