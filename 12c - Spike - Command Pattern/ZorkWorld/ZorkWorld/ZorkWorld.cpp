#include <iostream>
#include <fstream>
#include "json.hpp"
#include <string>
#include <vector>
#include <algorithm>
#include "Inventory.h"
#include <sstream>

class Entity {
public:
    std::string name;
    std::string description;

    void loadFromJson(const nlohmann::json& json) {
        if (json.contains("Name")) {
            name = json["Name"];
        }
        if (json.contains("Description")) {
            description = json["Description"];
        }
    }

    void printEntity() const {
        std::cout << name << ": " << description << "\n";
    }
};

class Location {
public:
    std::string name;
    std::string description;
    std::vector<std::string> items;
    std::vector<std::string> connections;
    std::vector<Entity> entities;

    void loadFromJson(const nlohmann::json& json) {
        name = json.value("Name", "");
        description = json.value("Description", "");
        items = json.value("Items", std::vector<std::string>{});
        connections = json.value("Connections", std::vector<std::string>{});

        if (json.contains("Entities")) {
            for (const auto& entityJson : json["Entities"]) {
                Entity entity;
                entity.loadFromJson(entityJson);
                entities.push_back(entity);
            }
        }
    }

    void printLocation() const {
        std::cout << "You are at: " << name << "\nDescription: " << description << "\n";
        std::cout << "Items: ";
        for (const auto& item : items) {
            std::cout << item << ", ";
        }
        std::cout << "\nConnections: ";
        for (const auto& connection : connections) {
            std::cout << connection << ", ";
        }
        std::cout << "\nEntities: ";
        for (const auto& entity : entities) {
            entity.printEntity();
        }
        std::cout << "\n";
    }
};

class Command {
public:
    virtual void execute(const std::vector<std::string>& args) = 0;
    virtual ~Command() = default;
};

class GoCommand : public Command {
private:
    Location** currentLocation;
    std::vector<Location>& locations;

public:
    GoCommand(Location** currentLoc, std::vector<Location>& locs)
        : currentLocation(currentLoc), locations(locs) {}

    void execute(const std::vector<std::string>& args) override {
        if (args.empty()) {
            std::cout << "Please specify a location.\n";
            return;
        }
        std::string targetLocation = "";
        for (const auto& arg : args) {
            if (!targetLocation.empty()) {
                targetLocation += " ";
            }
            targetLocation += arg;
        }

        auto& connections = (*currentLocation)->connections;
        auto it = std::find(connections.begin(), connections.end(), targetLocation);

        if (it != connections.end()) {
            for (auto& loc : locations) {
                if (loc.name == targetLocation) {
                    *currentLocation = &loc;
                    (*currentLocation)->printLocation();
                    return;
                }
            }
        }
        else {
            std::cout << "You cannot go to \"" << targetLocation << "\". It's not a valid connection.\n";
        }
    }
};


class LookAtCommand : public Command {
private:
    Location** currentLocation;

public:
    LookAtCommand(Location** currentLoc) : currentLocation(currentLoc) {}

    void execute(const std::vector<std::string>& args) override {
        if (args.size() < 1) {
            std::cout << "Please specify an entity to look at.\n";
            return;
        }

        std::string entityName = args[0];
        for (const auto& entity : (*currentLocation)->entities) {
            if (entity.name == entityName) {
                entity.printEntity();
                return;
            }
        }

        std::cout << "Entity '" << entityName << "' not found in this location.\n";
    }
};

class AliasCommand : public Command {
private:
    std::vector<std::pair<std::string, std::string>>& aliases;

public:
    AliasCommand(std::vector<std::pair<std::string, std::string>>& aliasVec) : aliases(aliasVec) {}

    void execute(const std::vector<std::string>& args) override {
        if (args.size() < 2) {
            std::cout << "Usage: alias [NEW_COMMAND] [MAPPED_COMMAND]\n";
            return;
        }

        std::string newCmd = args[0];
        std::string mappedCmd = args[1];
        aliases.push_back({ newCmd, mappedCmd });
        std::cout << "Alias added: " << newCmd << " -> " << mappedCmd << "\n";
    }
};

class DebugTreeCommand : public Command {
private:
    std::vector<Location>& locations;

public:
    DebugTreeCommand(std::vector<Location>& locs) : locations(locs) {}

    void execute(const std::vector<std::string>& args) override {
        std::cout << "Debug Tree: \n";
        for (const auto& loc : locations) {
            std::cout << "Location: " << loc.name << "\n";
            std::cout << "Entities: ";
            for (const auto& entity : loc.entities) {
                entity.printEntity();
            }
        }
        std::cout << "\n";
    }
};

class HelpCommand : public Command {
private:
    std::vector<std::pair<std::string, std::unique_ptr<Command>>>& commands;

public:
    HelpCommand(std::vector<std::pair<std::string, std::unique_ptr<Command>>>& cmds) : commands(cmds) {}

    void execute(const std::vector<std::string>& args) override {
        std::cout << "Available commands:\n";
        for (const auto& pair : commands) {
            std::cout << pair.first << "\n";
        }
    }
};

class InventoryCommand : public Command {
private:
    Inventory& playerInventory;

public:
    InventoryCommand(Inventory& inv) : playerInventory(inv) {}

    void execute(const std::vector<std::string>& args) override {
        playerInventory.ShowInventory();
    }
};

class CommandProcessor {
private:
    std::vector<std::pair<std::string, std::unique_ptr<Command>>> commands;
    std::vector<std::pair<std::string, std::string>> aliases;

public:
    void addCommand(const std::string& name, std::unique_ptr<Command> command) {
        commands.push_back({ name, std::move(command) });
    }

    void processInput(const std::string& input) {
        std::vector<std::string> args = splitInput(input); // Split input into words

        if (args.empty()) return;

        // Combine words to check for multi-word commands
        std::string commandName = args[0];
        size_t maxWords = std::min(args.size(), static_cast<size_t>(3)); // Check for commands up to 3 words long

        for (size_t i = 1; i < maxWords; ++i) {
            std::string potentialCommand = commandName + " " + args[i];
            for (const auto& command : commands) {
                if (command.first == potentialCommand) {
                    commandName = potentialCommand;
                    args.erase(args.begin(), args.begin() + (i + 1));
                    command.second->execute(args);
                    return;
                }
            }
        }

        // Check if single-word command exists
        args.erase(args.begin());
        for (const auto& command : commands) {
            if (command.first == commandName) {
                command.second->execute(args);
                return;
            }
        }

        std::cout << "Unknown command: " << commandName << "\n";
    }


    std::vector<std::pair<std::string, std::unique_ptr<Command>>>& getCommands() {
        return commands;
    }

    std::vector<std::pair<std::string, std::string>>& getAliases() {
        return aliases;
    }

private:
    std::vector<std::string> splitInput(const std::string& input) {
        std::vector<std::string> args;
        std::istringstream iss(input);
        std::string arg;
        while (std::getline(iss, arg, ' ')) {
            args.push_back(arg);
        }
        return args;
    }
};

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