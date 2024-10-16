#include "ControllerComponent.hpp"
#include <iostream>
#include <fstream>
#include <sstream>
#include <filesystem>

ControllerComponent::ControllerComponent() {
    // Initialize all actions as not pressed
    actionState["Move_Up"] = false;
    actionState["Move_Down"] = false;
    actionState["Move_Left"] = false;
    actionState["Move_Right"] = false;
    actionState["Jump"] = false;

    lastModificationTime = std::filesystem::file_time_type::min(); 
}

void ControllerComponent::handleEvent(const SDL_Event& event) {
    if (event.type == SDL_KEYDOWN || event.type == SDL_KEYUP) {
        for (const auto& [action, key] : keyBindings) {
            if (event.key.keysym.sym == key) {
                setActionState(action, event.type == SDL_KEYDOWN);
            }
        }
    }
}

void ControllerComponent::setActionState(const std::string& action, bool state) {
    actionState[action] = state;
}

bool ControllerComponent::isKeyPressed(const std::string& action) {
    return actionState[action];
}

bool ControllerComponent::loadConfiguration(const std::string& configFile) {
    std::ifstream file(configFile);
    if (!file.is_open()) {
        std::cerr << "Could not open configuration file: " << configFile << std::endl;
        return false;
    }

    std::string line;
    while (std::getline(file, line)) {
        std::istringstream iss(line);
        std::string action;
        std::string keyStr;

        if (iss >> action >> keyStr) {
            SDL_Keycode key = SDL_GetKeyFromName(keyStr.c_str());
            if (key == SDLK_UNKNOWN) {
                std::cerr << "Invalid key: " << keyStr << std::endl;
                continue;
            }
            // Add key mapping to the keyBindings map
            keyBindings[action] = key;
            std::cout << "Mapped action: " << action << " to key: " << keyStr << std::endl;  // Debugging log
        }
    }
    file.close();

    // Set the last modification time after loading the file
    lastModificationTime = std::filesystem::last_write_time(configFile);
    return true;
}

bool ControllerComponent::reloadConfiguration(const std::string& configFile) {
    std::cout << "Reloading configuration file: " << configFile << std::endl;
    return loadConfiguration(configFile);
}

// Check if the file has been modified and reload if necessary
void ControllerComponent::checkForReload(const std::string& configFile) {
    std::filesystem::file_time_type currentModificationTime = std::filesystem::last_write_time(configFile);

    if (currentModificationTime != lastModificationTime) {
        // If the file was modified, reload the configuration
        reloadConfiguration(configFile);
    }
}
