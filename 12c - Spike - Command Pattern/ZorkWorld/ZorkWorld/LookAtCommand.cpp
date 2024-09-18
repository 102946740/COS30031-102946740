#include "Command.h"

void LookAtCommand::execute(const std::vector<std::string>& args)
{
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
