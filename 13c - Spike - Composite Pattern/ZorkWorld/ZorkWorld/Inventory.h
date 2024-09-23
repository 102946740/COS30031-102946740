#pragma once
#include <iostream>
#include <vector>
#include <string>
#include "json.hpp"
#include "Entity.h"

class Item : public Entity {
public:
    Item() = default;
    void loadFromJson(const nlohmann::json& json);
    void printEntity() const override;
};

class Inventory : public Entity {

public:
    void addItem(Item ItemAdded);
    void removeItem(int index);
    void printEntity() const override;
    void printInventory() const;
    std::vector<Item> items;
};