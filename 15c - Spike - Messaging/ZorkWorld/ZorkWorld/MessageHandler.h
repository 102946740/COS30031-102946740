#pragma once
#include <vector>
#include <iostream>
#include <memory>   
#include "Entity.h"  
#include <unordered_map>


class MessageHandler
{
public:
	std::unordered_map<std::string, std::shared_ptr<Entity>> Entities;

	bool attack(std::string itemA, std::string itemB);
};

