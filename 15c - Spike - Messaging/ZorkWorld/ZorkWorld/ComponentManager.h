#pragma once
#include "Componants.h"
#include <iostream>
#include <memory>
#include <unordered_map>
#include <typeindex>

class ComponentManager {
public:
    // Add a component of type T
    template<typename T>
    void addComponent(const std::shared_ptr<T>& component) {
        auto key = std::type_index(typeid(T));
        components[key] = component; // Directly use the passed-in shared_ptr
    }

    // Retrieve a component of type T
    template<typename T>
    std::shared_ptr<T> getComponent() const {
        auto key = std::type_index(typeid(T));
        auto it = components.find(key);
        if (it != components.end()) {
            return std::dynamic_pointer_cast<T>(it->second);
        }
        return nullptr; // Return nullptr if the component doesn't exist
    }

private:
    std::unordered_map<std::type_index, std::shared_ptr<Component>> components;
};
