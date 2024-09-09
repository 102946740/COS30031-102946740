// ZorkWorld.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <fstream>
#include "json.hpp"
#include <string>
#include "Inventory.h"

struct vector3 {
    int x, y, z;
};

struct location {
    vector3 coordinates;
    std::string description;
};

int main()
{
    std::ifstream rFile;
    rFile.open("adventure.json");

    nlohmann::json jsonData;

    rFile >> jsonData;
    rFile.close();

    std::cout << jsonData.dump(4) << std::endl;
}

