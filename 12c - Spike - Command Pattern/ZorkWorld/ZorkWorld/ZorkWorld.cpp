#include "ZorkWorld.h"




int main() {
    std::ifstream rFile("adventure.json");
    if (!rFile.is_open()) {
        std::cerr << "Failed to open file!" << std::endl;
        return 1;
    }

    nlohmann::json jsonData;
    rFile >> jsonData;
    rFile.close();

    std::vector<Location> locations;
    if (jsonData.contains("Rooms")) {
        for (const auto& room : jsonData["Rooms"]) {
            Location location;
            location.loadFromJson(room);
            locations.push_back(location);
        }
    }

    Location* currentLocation = &locations[0];
    currentLocation->printLocation();

    CommandProcessor cmdProcessor;
    Inventory playerInventory;

    // Register commands
    cmdProcessor.addCommand("go to", std::make_unique<GoCommand>(&currentLocation, locations));
    cmdProcessor.addCommand("look at", std::make_unique<LookAtCommand>(&currentLocation));
    cmdProcessor.addCommand("alias", std::make_unique<AliasCommand>(cmdProcessor.getAliases()));
    cmdProcessor.addCommand("debug tree", std::make_unique<DebugTreeCommand>(locations));
    cmdProcessor.addCommand("help", std::make_unique<HelpCommand>(cmdProcessor.getCommands()));
    cmdProcessor.addCommand("inventory", std::make_unique<InventoryCommand>(playerInventory));

    std::string input;
    while (true) {
        std::cout << "\nEnter a command: ";
        std::getline(std::cin, input);

        if (input == "quit" || input == "exit") {
            std::cout << "Exiting the game.\n";
            break;
        }

        cmdProcessor.processInput(input);
    }

    return 0;
}