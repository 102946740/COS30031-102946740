#include <SDL.h>
#include <cstdlib>  // For rand() and srand()
#include <ctime>    // For time()

// Function to generate a random SDL_Color
SDL_Color getRandomColor() {
    SDL_Color color;
    color.r = rand() % 256;
    color.g = rand() % 256;
    color.b = rand() % 256;
    color.a = 255;  // Fully opaque
    return color;
}

int main(int argc, char* argv[]) {
    // Window dimensions as variables
    const int windowWidth = 600;
    const int windowHeight = 800;

    // Initialize SDL
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        SDL_Log("SDL could not initialize! SDL_Error: %s", SDL_GetError());
        return 1;
    }

    // Create an SDL window using variable dimensions
    SDL_Window* window = SDL_CreateWindow("SDL Random Color Change",
        SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED,
        windowHeight, windowWidth,
        SDL_WINDOW_SHOWN);
    if (!window) {
        SDL_Log("Window could not be created! SDL_Error: %s", SDL_GetError());
        SDL_Quit();
        return 1;
    }

    // Create a renderer to handle drawing
    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (!renderer) {
        SDL_Log("Renderer could not be created! SDL_Error: %s", SDL_GetError());
        SDL_DestroyWindow(window);
        SDL_Quit();
        return 1;
    }

    // Seed random number generator
    srand(static_cast<unsigned int>(time(0)));

    // Initial color: green
    SDL_Color currentColor = { 0, 255, 0, 255 };

    bool isRunning = true;
    SDL_Event event;

    // Main loop
    while (isRunning) {
        // Handle events
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                isRunning = false;
            }
            else if (event.type == SDL_KEYDOWN) {
                if (event.key.keysym.sym == SDLK_r) {
                    // Change the background color to a random color
                    currentColor = getRandomColor();
                }
            }
        }

        // Clear screen with current color
        SDL_SetRenderDrawColor(renderer, currentColor.r, currentColor.g, currentColor.b, currentColor.a);
        SDL_RenderClear(renderer);

        // Update the screen
        SDL_RenderPresent(renderer);
    }

    // Clean up resources
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}
