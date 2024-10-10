#pragma once
#include <vector>
#include <string>
#include <iostream>
#include "Location.h"

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

class TakeCommand : public Command {
private:
    Location** currentLocation;
    Entity& playerInventory;

public:
    TakeCommand(Location** currentLoc, Entity& pInventory) : currentLocation(currentLoc), playerInventory(pInventory) {}

    void execute(const std::vector<std::string>& args) override;
};

class OpenCommand : public Command {
private:
    Location** currentLocation;
    Entity& playerInventory;

public:
    OpenCommand(Location** currentLoc, Entity& pInventory) : currentLocation(currentLoc), playerInventory(pInventory) {}

    void execute(const std::vector<std::string>& args) override;
};

class PutCommand : public Command {
private:
    Location** currentLocation;
    Entity& playerInventory;

public:
    PutCommand(Location** currentLoc, Entity& pInventory) : currentLocation(currentLoc), playerInventory(pInventory) {}

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
    Entity& playerInventory;

public:
    InventoryCommand(Entity& inv) : playerInventory(inv) {}

    void execute(const std::vector<std::string>& args) override;
};
