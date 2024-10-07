#include <SDL.h>
#include <SDL_mixer.h>
#include <iostream>
#include <cstdlib>
#include <ctime>

// Function to initialize SDL and SDL_mixer
bool init(SDL_Window** window, SDL_Renderer** renderer, const int width, const int height) {
    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) < 0) {
        std::cerr << "SDL could not initialize! SDL_Error: " << SDL_GetError() << std::endl;
        return false;
    }

    // Initialize SDL_mixer with support for MP3 and OGG
    if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0) {
        std::cerr << "SDL_mixer could not initialize! SDL_mixer Error: " << Mix_GetError() << std::endl;
        return false;
    }

    // Create window and renderer
    *window = SDL_CreateWindow("SDL Game with Background and Tiles", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, SDL_WINDOW_SHOWN);
    if (!*window) {
        std::cerr << "Window could not be created! SDL_Error: " << SDL_GetError() << std::endl;
        return false;
    }

    *renderer = SDL_CreateRenderer(*window, -1, SDL_RENDERER_ACCELERATED);
    if (!*renderer) {
        std::cerr << "Renderer could not be created! SDL_Error: " << SDL_GetError() << std::endl;
        return false;
    }

    return true;
}

// Function to load images as textures
SDL_Texture* loadTexture(const char* path, SDL_Renderer* renderer) {
    SDL_Surface* tempSurface = SDL_LoadBMP(path);
    if (!tempSurface) {
        std::cerr << "Unable to load image " << path << "! SDL Error: " << SDL_GetError() << std::endl;
        return nullptr;
    }
    SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, tempSurface);
    SDL_FreeSurface(tempSurface);
    return texture;
}

int main(int argc, char* argv[]) {
    const int windowWidth = 600;
    const int windowHeight = 800;

    // Initialize SDL, SDL_mixer, and SDL window/renderer
    SDL_Window* window = nullptr;
    SDL_Renderer* renderer = nullptr;
    if (!init(&window, &renderer, windowWidth, windowHeight)) {
        return 1;
    }

    // Load sound effects
    Mix_Chunk* sound1 = Mix_LoadWAV("sound1.wav");
    Mix_Chunk* sound2 = Mix_LoadWAV("sound2.wav");
    Mix_Chunk* sound3 = Mix_LoadWAV("sound3.wav");
    if (!sound1 || !sound2 || !sound3) {
        Mix_CloseAudio();
        SDL_Quit();
        return 1;
    }

    // Load background image and tileset
    SDL_Texture* background = loadTexture("background.bmp", renderer);
    SDL_Texture* tileset = loadTexture("tileset.bmp", renderer);  // This image should contain the tiles

    // Define the tile subregions
    SDL_Rect tile1 = { 0, 0, 64, 64 };     // First tile
    SDL_Rect tile2 = { 64, 0, 64, 64 };    // Second tile
    SDL_Rect tile3 = { 128, 0, 64, 64 };   // Third tile

    // Set up random positions for the tiles
    srand(static_cast<unsigned int>(time(0)));
    SDL_Rect dstTile1 = { rand() % (windowWidth - 64), rand() % (windowHeight - 64), 64, 64 };
    SDL_Rect dstTile2 = { rand() % (windowWidth - 64), rand() % (windowHeight - 64), 64, 64 };
    SDL_Rect dstTile3 = { rand() % (windowWidth - 64), rand() % (windowHeight - 64), 64, 64 };

    bool isRunning = true;
    SDL_Event event;
    bool isBackgroundVisible = true;
    bool isTile1Visible = false, isTile2Visible = false, isTile3Visible = false;

    bool isPaused = false;
    int currentChannel = -1;

    // Main loop
    while (isRunning) {
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                isRunning = false;
            }
            else if (event.type == SDL_KEYDOWN) {
                switch (event.key.keysym.sym) {
                case SDLK_1: // Toggle tile 1
                    isTile1Visible = !isTile1Visible;
                    if (currentChannel != -1) Mix_HaltChannel(currentChannel);
                    currentChannel = Mix_PlayChannel(-1, sound1, 0);
                    isPaused = false;
                    break;

                case SDLK_2: // Toggle tile 2
                    isTile2Visible = !isTile2Visible;
                    if (currentChannel != -1) Mix_HaltChannel(currentChannel);
                    currentChannel = Mix_PlayChannel(-1, sound2, 0);
                    isPaused = false;
                    break;

                case SDLK_3: // Toggle tile 3
                    isTile3Visible = !isTile3Visible;
                    if (currentChannel != -1) Mix_HaltChannel(currentChannel);
                    currentChannel = Mix_PlayChannel(-1, sound3, 0);
                    isPaused = false;
                    break;

                case SDLK_0: // Toggle background visibility
                    isBackgroundVisible = !isBackgroundVisible;
                    if (currentChannel != -1) {
                        if (!isPaused) {
                            Mix_Pause(currentChannel);
                            isPaused = true;
                        }
                        else {
                            Mix_Resume(currentChannel);
                            isPaused = false;
                        }
                    }
                    break;
                }
            }
        }

        // Clear screen
        SDL_RenderClear(renderer);

        // Render background if visible
        if (isBackgroundVisible && background) {
            SDL_RenderCopy(renderer, background, NULL, NULL);
        }

        // Render tiles if visible
        if (isTile1Visible && tileset) {
            SDL_RenderCopy(renderer, tileset, &tile1, &dstTile1);
        }
        if (isTile2Visible && tileset) {
            SDL_RenderCopy(renderer, tileset, &tile2, &dstTile2);
        }
        if (isTile3Visible && tileset) {
            SDL_RenderCopy(renderer, tileset, &tile3, &dstTile3);
        }

        // Update screen
        SDL_RenderPresent(renderer);
    }

    // Clean up resources
    Mix_FreeChunk(sound1);
    Mix_FreeChunk(sound2);
    Mix_FreeChunk(sound3);
    Mix_CloseAudio();
    SDL_DestroyTexture(background);
    SDL_DestroyTexture(tileset);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}
