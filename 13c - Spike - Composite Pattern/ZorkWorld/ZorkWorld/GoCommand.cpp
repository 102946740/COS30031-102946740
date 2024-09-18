#include "Command.h"

void GoCommand::execute(const std::vector<std::string>& args)
{
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
