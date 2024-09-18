#pragma once
#include <string>
#include <vector>
#include <algorithm>
#include "Command.h"
#include "iostream"
#include <fstream>
#include <sstream>

class CommandProcessor {
private:
    std::vector<std::pair<std::string, std::unique_ptr<Command>>> commands;
    std::vector<std::pair<std::string, std::string>> aliases;

public:
    void addCommand(const std::string& name, std::unique_ptr<Command> command);

    void processInput(const std::string& input);


    std::vector<std::pair<std::string, std::unique_ptr<Command>>>& getCommands();

    std::vector<std::pair<std::string, std::string>>& getAliases();

private:
    std::vector<std::string> splitInput(const std::string& input);
};