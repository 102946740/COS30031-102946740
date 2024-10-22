#include <SDL.h>
#include <cstdlib>  // For rand() and srand()
#include <ctime>    // For time()
#include <cmath>    // For sqrt()

// Structure to hold rectangle entity
struct Box {
    SDL_Rect rect;
    int dx, dy; // velocity

    void move() {
        rect.x += dx;
        rect.y += dy;
    }

    void render(SDL_Renderer* renderer) {
        SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255); // Red color
        SDL_RenderFillRect(renderer, &rect);
    }
};

// Structure to hold circle entity
struct Circle {
    int x, y, r; // position and radius
    int dx, dy;  // velocity

    void move() {
        x += dx;
        y += dy;
    }

    void render(SDL_Renderer* renderer) {
        SDL_SetRenderDrawColor(renderer, 0, 0, 255, 255); // Blue color
        // Draw a filled circle (simple approximation)
        for (int w = 0; w < r * 2; w++) {
            for (int h = 0; h < r * 2; h++) {
                int dx = r - w; // horizontal offset
                int dy = r - h; // vertical offset
                if ((dx * dx + dy * dy) <= (r * r)) {
                    SDL_RenderDrawPoint(renderer, x + dx, y + dy);
                }
            }
        }
    }
};

// Axis-Aligned Bounding Box collision detection
bool checkBoxCollision(const Box& a, const Box& b) {
    return (a.rect.x < b.rect.x + b.rect.w &&
        a.rect.x + a.rect.w > b.rect.x &&
        a.rect.y < b.rect.y + b.rect.h &&
        a.rect.y + a.rect.h > b.rect.y);
}

// Circle-Circle collision detection
bool checkCircleCollision(const Circle& a, const Circle& b) {
    int distSq = (a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y);
    int radiusSum = a.r + b.r;
    return distSq <= (radiusSum * radiusSum);
}

int main(int argc, char* argv[]) {
    const int windowWidth = 800;
    const int windowHeight = 600;

    // Initialize SDL
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        SDL_Log("SDL could not initialize! SDL_Error: %s", SDL_GetError());
        return 1;
    }

    SDL_Window* window = SDL_CreateWindow("SDL Collision Detection",
        SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
        windowWidth, windowHeight, SDL_WINDOW_SHOWN);

    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (!renderer) {
        SDL_Log("Renderer could not be created! SDL_Error: %s", SDL_GetError());
        SDL_DestroyWindow(window);
        SDL_Quit();
        return 1;
    }

    srand(static_cast<unsigned>(time(0)));

    // Boxes and Circles
    Box box1 = { {100, 100, 50, 50}, 2, 2 };
    Box box2 = { {300, 300, 50, 50}, 0, 0 }; // Static box

    Circle circle1 = { 100, 100, 25, 3, 3 };
    Circle circle2 = { 400, 400, 25, -2, -2 };

    bool quit = false;
    SDL_Event e;
    bool boxMode = true;  // Toggle between box and circle mode

    while (!quit) {
        while (SDL_PollEvent(&e) != 0) {
            if (e.type == SDL_QUIT) {
                quit = true;
            }
            if (e.type == SDL_KEYDOWN) {
                if (e.key.keysym.sym == SDLK_1) {
                    boxMode = true;
                }
                else if (e.key.keysym.sym == SDLK_2) {
                    boxMode = false;
                }
            }
        }

        // Move entities
        box1.move();
        circle1.move();

        // Collision Detection
        bool collision = false;
        if (boxMode) {
            collision = checkBoxCollision(box1, box2);
        }
        else {
            collision = checkCircleCollision(circle1, circle2);
        }

        // Clear screen
        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255); // White background
        SDL_RenderClear(renderer);

        // Render boxes or circles
        if (boxMode) {
            box1.render(renderer);
            box2.render(renderer);
        }
        else {
            circle1.render(renderer);
            circle2.render(renderer);
        }

        // If collision detected, change background color to red
        if (collision) {
            SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255); // Red
            SDL_RenderClear(renderer);
        }

        // Present the updated frame
        SDL_RenderPresent(renderer);

        SDL_Delay(16);  // ~60 FPS
    }

    // Clean up
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}
