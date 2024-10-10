#pragma once

#include <iostream>
#include <memory>
#include <vector>
#include "json.hpp"   
#include "Entity.h"  
#include "MessageHandler.h"

class Location {
public:
    std::string name;
    std::string description;
    std::vector<std::string> items;
    std::vector<std::string> connections;
    std::vector<std::shared_ptr<Entity>> entities;  

    void loadFromJson(const nlohmann::json& json, MessageHandler& Messenger);
    void printLocation() const;
};
