#pragma once
#include <string>
#include "json.hpp"
#include <iostream>
class Entity {
public:
    std::string name;
    std::string description;

    void loadFromJson(const nlohmann::json& json);

    void printEntity() const;
};