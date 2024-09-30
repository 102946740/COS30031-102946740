#include "Command.h"

void AliasCommand::execute(const std::vector<std::string>& args)
{
    if (args.size() < 2) {
        std::cout << "Usage: alias [NEW_COMMAND] [MAPPED_COMMAND]\n";
        return;
    }

    std::string newCmd = args[0];
    std::string mappedCmd = args[1];
    aliases.push_back({ newCmd, mappedCmd });
    std::cout << "Alias added: " << newCmd << " -> " << mappedCmd << "\n";
}