#pragma once
#include <SDL.h>
#include <unordered_map>
#include <string>
#include <filesystem>
#include <chrono>

class ControllerComponent {
public:
    ControllerComponent();
    void handleEvent(const SDL_Event& event);
    bool loadConfiguration(const std::string& configFile);
    bool reloadConfiguration(const std::string& configFile);
    void checkForReload(const std::string& configFile); 
    bool isKeyPressed(const std::string& action);

private:
    std::unordered_map<std::string, SDL_Keycode> keyBindings;
    std::unordered_map<std::string, bool> actionState;
    std::filesystem::file_time_type lastModificationTime;

    void setActionState(const std::string& action, bool state);
};
