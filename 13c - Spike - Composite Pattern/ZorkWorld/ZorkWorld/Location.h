#pragma once
#include <iostream>
#include "json.hpp"
#include "Entity.h"
class Location {
public:
    std::string name;
    std::string description;
    std::vector<std::string> items;
    std::vector<std::string> connections;
    std::vector<Entity> entities;

    void loadFromJson(const nlohmann::json& json);

    void printLocation() const;
};