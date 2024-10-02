#pragma once
#include <memory>
#include "Componants.h"
class ComponentManager {
public:
    // Add component by type, dynamically checking the type using typeid
    template <typename T>
    void addComponent(std::shared_ptr<T> component) {
        components[typeid(T)] = component;
    }

    // Get a component by type
    template <typename T>
    std::shared_ptr<T> getComponent() {
        auto it = components.find(typeid(T));
        if (it != components.end()) {
            return std::static_pointer_cast<T>(it->second);
        }
        return nullptr;
    }

    // Execute all components
    void executeAll() {
        for (auto& pair : components) {
            pair.second->execute();  // Calls execute of each component
        }
    }

private:
    std::unordered_map<std::type_index, std::shared_ptr<Component>> components;
};

