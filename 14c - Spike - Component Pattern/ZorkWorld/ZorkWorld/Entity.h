#pragma once
#include "Componants.h"
class Entity {
public:
    virtual ~Entity() = default;
    Identifier ID;
    bool Interactable = true;
    virtual void loadFromJson(const nlohmann::json& json);

    virtual void printEntity() const;
};