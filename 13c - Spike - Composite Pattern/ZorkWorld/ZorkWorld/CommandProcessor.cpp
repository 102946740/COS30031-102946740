#include "CommandProcessor.h"

void CommandProcessor::addCommand(const std::string& name, std::unique_ptr<Command> command)
{
    commands.push_back({ name, std::move(command) });
}

void CommandProcessor::processInput(const std::string& input)
{
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

std::vector<std::pair<std::string, std::unique_ptr<Command>>>& CommandProcessor::getCommands()
{
    return commands;
}

std::vector<std::pair<std::string, std::string>>& CommandProcessor::getAliases()
{
    return aliases;
}

std::vector<std::string> CommandProcessor::splitInput(const std::string& input)
{
    std::vector<std::string> args;
    std::istringstream iss(input);
    std::string arg;
    while (std::getline(iss, arg, ' ')) {
        args.push_back(arg);
    }
    return args;
}
