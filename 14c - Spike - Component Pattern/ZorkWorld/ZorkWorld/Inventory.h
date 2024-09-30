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
    InventoryComp Inv;
    void printEntity() const override;
    
};