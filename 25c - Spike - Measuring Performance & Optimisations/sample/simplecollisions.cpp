#include <random>
#include <iostream>
#include <fstream>
#include <chrono>
#include "sdl/SDL.h"

#define RENDER false  // Disable rendering for performance measurement

const int SCREEN_WIDTH = 800;
const int SCREEN_HEIGHT = 600;
const int BOX_WIDTH = 50;
const int BOX_HEIGHT = 50;
const int BOX_SPEED = 10;
const int TEST_TIME = 10 * 1000; // 10 seconds

enum BoxState { CONTACT_NO, CONTACT_YES };

struct CrashBox {
    int x, y, dx, dy, w, h;
    int right, bottom;  // Cached right and bottom edges
    BoxState state;

    // Optimized update_position: Combined position update and wrap-around
    void update_position() {
        x = (x + dx + SCREEN_WIDTH) % SCREEN_WIDTH;
        y = (y + dy + SCREEN_HEIGHT) % SCREEN_HEIGHT;
        right = x + w;
        bottom = y + h;
    }
};

// Global variables.
SDL_Window* window = NULL;
SDL_Renderer* renderer = NULL;

int BOX_COUNT;
CrashBox* boxes;
void (*crash_test_all_ptr)();

// Initialize boxes with random positions, sizes, and velocities
void init_boxes() {
    srand(9999);
    for (int i = 0; i < BOX_COUNT; i++) {
        boxes[i].x = rand() % SCREEN_WIDTH;
        boxes[i].y = rand() % SCREEN_HEIGHT;
        boxes[i].w = (rand() % BOX_WIDTH) + 1;
        boxes[i].h = (rand() % BOX_HEIGHT) + 1;
        boxes[i].dx = (rand() % (BOX_SPEED * 2)) - (BOX_SPEED / 2);
        boxes[i].dy = (rand() % (BOX_SPEED * 2)) - (BOX_SPEED / 2);
        boxes[i].right = boxes[i].x + boxes[i].w;
        boxes[i].bottom = boxes[i].y + boxes[i].h;
        boxes[i].state = CONTACT_NO;
    }
}

// Most optimized collision detection method based on previous measurement
bool optimal_crash_test(const CrashBox& A, const CrashBox& B) {
    return !(A.bottom <= B.y || A.y >= B.bottom || A.right <= B.x || A.x >= B.right);
}

// Check for collisions using the optimal collision detection function
void optimized_crash_test_all() {
    for (int i = 0; i < BOX_COUNT; i++) {
        boxes[i].state = CONTACT_NO;
        for (int j = i + 1; j < BOX_COUNT; j++) {
            if (optimal_crash_test(boxes[i], boxes[j])) {
                boxes[i].state = boxes[j].state = CONTACT_YES;
            }
        }
    }
}

// Update box positions and check for collisions
void update_boxes() {
    for (int i = 0; i < BOX_COUNT; i++) {
        boxes[i].update_position();
    }
    optimized_crash_test_all();  // Using optimized collision detection function
}

int run_test(const char* title) {
    // Disable SDL rendering setup since we are not rendering for performance testing

    // Redirect console output to file
    std::ofstream outFile("results.txt", std::ios::app);
    std::ofstream errFile("results.txt", std::ios::app);
    if (outFile.is_open() && errFile.is_open()) {
        std::cout.rdbuf(outFile.rdbuf());
        std::cerr.rdbuf(errFile.rdbuf());
    }
    else {
        std::cerr << "Error opening results.txt for logging." << std::endl;
        return 1;
    }

    std::cout << "-- New Test: \t" << title << std::endl;
    init_boxes();  // Initialize all boxes for testing

    Uint32 loop_count = 0;
    auto start = std::chrono::high_resolution_clock::now();
    auto target = std::chrono::milliseconds(TEST_TIME);

    while (std::chrono::high_resolution_clock::now() - start < target) {
        update_boxes();
        loop_count++;
    }

    auto end = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();

    // Display and log results
    std::cout << "Loops: \t" << loop_count << std::endl;
    std::cout << "Time (ms): \t" << duration << std::endl;
    std::cout << "Loops/Second: \t" << (float(loop_count) / duration * 1000.0) << std::endl;
    std::cout << "Num boxes: \t" << BOX_COUNT << std::endl;

    return 0;
}

int main(int argc, char* args[]) {
    for (BOX_COUNT = 2; BOX_COUNT <= 50; ++BOX_COUNT) {
        boxes = new CrashBox[BOX_COUNT];
        for (int i = 0; i < 5; ++i) {
            run_test("Optimized Collision Detection Test");
        }
        delete[] boxes;
    }
    return 0;
}
