#pragma once
#include <iostream>
#include <vector>
#include <string>
#include "json.hpp"
class GameObject {
};

struct itemStruc : public GameObject {
    std::string Identifier;
    std::string Name;
    std::string Description;
    int EffectMod = 0;
};
class Entity {
public:
    virtual ~Entity() = default;
    itemStruc Info;
    virtual void loadFromJson(const nlohmann::json& json);

    virtual void printEntity() const;
};

class Item : public Entity {
public:
    Item() = default;
    void loadFromJson(const nlohmann::json& json);
    void printEntity() const override;
};

class Inventory : public Entity {
private:
    std::vector<Item> items;

public:
    void addItem(Item ItemAdded);
    void removeItem(int index);
    void printEntity() const override;
    void printInventory() const;
};