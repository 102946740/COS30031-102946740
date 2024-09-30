#include "Command.h"

void DebugTreeCommand::execute(const std::vector<std::string>& args)
{
    std::cout << "Debug Tree: \n";
    for (const auto& loc : locations) {
        std::cout << "Location: " << loc.name << "\n";
        std::cout << "Entities: ";
        for (const auto& entity : loc.entities) {
            entity->printEntity();
        }
    }
    std::cout << "\n";
}
