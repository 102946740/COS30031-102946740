#include <iostream>
#include <fstream>
#include "json.hpp"
#include <string>
#include <vector>
#include <algorithm>
#include "Inventory.h"

class Location {
public:
    std::string name;
    std::string description;
    std::vector<std::string> items; //doesnt need item class yet, just testing
    std::vector<std::string> connections;

    // Function to load data from JSON into this object
    void loadFromJson(const nlohmann::json& json) {
        if (json.contains("Name")) {
            name = json["Name"];
        }
        if (json.contains("Description")) {
            description = json["Description"];
        }
        if (json.contains("Items")) {
            items = json["Items"].get<std::vector<std::string>>();
        }
        if (json.contains("Connections")) {
            connections = json["Connections"].get<std::vector<std::string>>();
        }
    }

    // Function to print location details
    void printLocation() const {
        std::cout << "You are at: " << name << "\n";
        std::cout << "Description: " << description << "\n";
        std::cout << "Items: ";
        for (const auto& item : items) {
            std::cout << item << ", ";
        }
        std::cout << "\nConnections: ";
        for (const auto& connection : connections) {
            std::cout << connection << ", ";
        }
        std::cout << "\n";
    }
};

int main()
{
    std::ifstream rFile("adventure.json");

    if (!rFile.is_open()) {
        std::cerr << "Failed to open file!" << std::endl;
        return 1;
    }

    nlohmann::json jsonData;
    rFile >> jsonData;
    rFile.close();

    // Vector to store all locations
    std::vector<Location> locations;

    // Parse the Rooms from the JSON
    if (jsonData.contains("Rooms")) {
        for (const auto& room : jsonData["Rooms"]) {
            Location location;
            location.loadFromJson(room);
            locations.push_back(location);
        }
    }

    // Starting location
    Location* currentLocation = &locations[0];
    currentLocation->printLocation();

    std::string input;

    while (true) {
        std::cout << "\nEnter a command (e.g., go [Location]): ";
        std::getline(std::cin, input);

        // Check for the "go" command
        if (input.substr(0, 3) == "go ") {
            std::string targetLocation = input.substr(3);  // Extract the location name

            // Check if the target location is a valid connection
            auto it = std::find(currentLocation->connections.begin(), currentLocation->connections.end(), targetLocation);
            if (it != currentLocation->connections.end()) {
                // Find the new location in the list of all locations
                for (auto& loc : locations) {
                    if (loc.name == targetLocation) {
                        currentLocation = &loc;
                        currentLocation->printLocation();
                        break;
                    }
                }
            }
            else {
                std::cout << "You cannot go to " << targetLocation << ". It's not a valid connection.\n";
            }
        }
        else if (input == "quit") {
            std::cout << "Exiting the game.\n";
            break;
        }
        else {
            std::cout << "Invalid command. Try 'go [Location]' or 'quit'.\n";
        }
    }

    return 0;
}
