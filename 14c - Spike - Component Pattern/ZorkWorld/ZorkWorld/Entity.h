#pragma once
#include "ComponentManager.h"
#include "json.hpp"
#include <iostream>
#include <memory>

class Entity {
public:
    virtual ~Entity() = default;
    ComponentManager compManager;

    virtual void loadFromJson(const nlohmann::json& json);
    virtual void printEntity() const;
};
