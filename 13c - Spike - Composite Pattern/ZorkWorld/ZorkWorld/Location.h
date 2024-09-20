#pragma once
#include <iostream>
#include "json.hpp"
#include "Inventory.h"
#include <memory>
class Location {
public:
    std::string name;
    std::string description;
    std::vector<std::string> items;
    std::vector<std::string> connections;
    std::vector<std::shared_ptr<Entity>> entities;

    void loadFromJson(const nlohmann::json& json);

    void printLocation() const;
};