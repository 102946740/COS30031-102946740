#pragma once
#include <iostream>
#include <vector>
#include <memory> 
#include <string>

// Forward declaration of Entity class
class Entity;

class Component {
public:
    virtual ~Component() = default;
};

class Attributes : public Component {
public:
    int HP = 0;
    int Damage = 0;
    bool Interactable = true;
    bool Alive = true;

    bool dealDamage(int Dmg);
    std::string getDetails() const;
};

class Identifier : public Component {
public:
    std::string Name = "";
    std::string Description = "";
    std::string getIdentifiers() const;
};

class InventoryComp : public Component {
public:
    bool Interactable = true;
    std::vector<std::shared_ptr<Entity>> Items; 

    void addItem(std::shared_ptr<Entity> ItemAdded); 
    void removeItem(int index);
    void printInventory(const std::string& name) const;
};

