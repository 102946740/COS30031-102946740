#include "Command.h"

void HelpCommand::execute(const std::vector<std::string>& args)
{
    std::cout << "Available commands:\n";
    for (const auto& pair : commands) {
        std::cout << pair.first << "\n";
    }
}