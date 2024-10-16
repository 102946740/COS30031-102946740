#include <SDL.h>
#include "ControllerComponent.hpp"
#include <iostream>

int main(int argc, char* argv[]) {
    SDL_Init(SDL_INIT_VIDEO | SDL_INIT_GAMECONTROLLER);

    SDL_Window* window = SDL_CreateWindow("SDL Input Mapping", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 800, 600, 0);
    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

    ControllerComponent controller;

    if (!controller.loadConfiguration("input_mapping.txt")) {
        std::cerr << "Failed to load input configuration." << std::endl;
        return -1;
    }

    bool isRunning = true;
    SDL_Event event;

    while (isRunning) {
        // Poll events
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                isRunning = false;
            }

            // Handle input
            controller.handleEvent(event);
        }

        // Live Check if the config file has been edited
        controller.checkForReload("input_mapping.txt");

        // Events that could be added to a player class
        if (controller.isKeyPressed("Move_Up")) {
            std::cout << "Moving Up!" << std::endl;
        }
        if (controller.isKeyPressed("Move_Down")) {
            std::cout << "Moving Down!" << std::endl;
        }
        if (controller.isKeyPressed("Move_Right")) {
            std::cout << "Moving Right!" << std::endl;
        }
        if (controller.isKeyPressed("Move_Left")) {
            std::cout << "Moving Left!" << std::endl;
        }
        if (controller.isKeyPressed("Jump")) {
            std::cout << "Jumping!" << std::endl;
        }
        SDL_RenderClear(renderer);
        SDL_RenderPresent(renderer);
    }

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;
}
