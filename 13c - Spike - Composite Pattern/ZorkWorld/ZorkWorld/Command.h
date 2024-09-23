#pragma once
#include <vector>
#include <string>
#include <iostream>
#include "location.h"
#include "Inventory.h"
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

    void execute(const std::vector<std::string>& args) override;
};

class LookAtCommand : public Command {
private:
    Location** currentLocation;

public:
    LookAtCommand(Location** currentLoc) : currentLocation(currentLoc) {}

    void execute(const std::vector<std::string>& args) override;
};

class LookInCommand : public Command {
private:
    Location** currentLocation;

public:
    LookInCommand(Location** currentLoc) : currentLocation(currentLoc) {}

    void execute(const std::vector<std::string>& args) override;
};

class takeCommand : public Command {
private:
    Location** currentLocation;
    Inventory& playerInventory;

public:
    takeCommand(Location** currentLoc, Inventory& pInventory) : currentLocation(currentLoc), playerInventory(pInventory) {}

    void execute(const std::vector<std::string>& args) override;
};


class AliasCommand : public Command {
private:
    std::vector<std::pair<std::string, std::string>>& aliases;

public:
    AliasCommand(std::vector<std::pair<std::string, std::string>>& aliasVec) : aliases(aliasVec) {}

    void execute(const std::vector<std::string>& args) override;
};

class DebugTreeCommand : public Command {
private:
    std::vector<Location>& locations;

public:
    DebugTreeCommand(std::vector<Location>& locs) : locations(locs) {}

    void execute(const std::vector<std::string>& args) override;
};

class HelpCommand : public Command {
private:
    std::vector<std::pair<std::string, std::unique_ptr<Command>>>& commands;

public:
    HelpCommand(std::vector<std::pair<std::string, std::unique_ptr<Command>>>& cmds) : commands(cmds) {}

    void execute(const std::vector<std::string>& args) override;
};

class InventoryCommand : public Command {
private:
    Inventory& playerInventory;

public:
    InventoryCommand(Inventory& inv) : playerInventory(inv) {}

    void execute(const std::vector<std::string>& args) override;
};

