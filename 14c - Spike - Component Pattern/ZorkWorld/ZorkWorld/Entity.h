#pragma once
#include <vector>
#include <memory>
#include "Components.h"
#include "json.hpp"  // Include nlohmann JSON

class Entity {
public:
    virtual ~Entity() = default;

    // Store components as pointers to base Component class
    std::vector<std::shared_ptr<Component>> Components;

    virtual void loadFromJson(const nlohmann::json& json);
    virtual void printEntity() const;

    // Add components dynamically
    void addComponent(std::shared_ptr<Component> component) {
        Components.push_back(component);
    }

    // Get component by type (simplified lookup)
    template<typename T>
    std::shared_ptr<T> getComponent() const {
        for (const auto& component : Components) {
            if (auto casted = std::dynamic_pointer_cast<T>(component)) {
                return casted;
            }
        }
        return nullptr;
    }