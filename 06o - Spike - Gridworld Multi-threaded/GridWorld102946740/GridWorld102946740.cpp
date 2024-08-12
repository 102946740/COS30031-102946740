// GridWorld102946740.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <cctype>
#include <windows.h> 
#include <thread>
#include <mutex>

enum State {
    Alive, Dead, Win
};

bool positionChanged = true; // Initially true to render the first frame


void renderLoop();
void input(State& pState);
void gameLoop();
const int MAP_H = 8;
const int MAP_W = 8;

char map[MAP_H][MAP_W] = {
    {'#','#','#','#','#','#','#','#'},
    {'#','G',' ',' ',' ',' ',' ','#'},
    {'#',' ',' ',' ','#','D',' ','#'},
    {'#','#','#',' ','#',' ','#','#'},
    {'#',' ','D',' ',' ',' ',' ','#'},
    {'#',' ',' ','#','#','#',' ','#'},
    {'#',' ',' ',' ',' ',' ',' ','#'},
    {'#','#',' ','#','#','#','#','#'}
};

void setConsoleColor(int color) {
    // Set console text color using Windows API
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole, color);
}

int Location[2] = { 7, 2 };
std::mutex mtx;  // Mutex for synchronizing input and render

int main() {
    system("color 0a"); // to change colour of screen lol
    gameLoop();
    return 0;
}

void gameLoop() {
    State pState = Alive;
    bool Loop = true;

    std::thread Input_Thread(input, std::ref(pState));

    while (Loop) {
        if (positionChanged) {
            std::thread Render_Thread(renderLoop);
            Render_Thread.join();
            positionChanged = false; // Reset the flag after rendering
        }

        switch (pState) {
        case Alive:
            break;
        case Dead:
            renderLoop();
            setConsoleColor(0x0C);
            std::cout << "You Died, Game Over \n";
            Loop = false;
            break;
        case Win:
            renderLoop();
            setConsoleColor(0x0E);
            std::cout << "YOU WIN TOP G\n";
            Loop = false;
            break;
        }
    }

    Input_Thread.detach(); // Detach the input thread at the end of the game loop
}

void input(State& pState) {
    while (pState == Alive) {
        if (GetAsyncKeyState('N') & 0x8000) {
            std::lock_guard<std::mutex> lock(mtx);
            if (Location[0] > 0 && (map[Location[0] - 1][Location[1]] == ' ' || map[Location[0] - 1][Location[1]] == 'D' || map[Location[0] - 1][Location[1]] == 'G')) {
                if (map[Location[0] - 1][Location[1]] == 'D') pState = Dead;
                if (map[Location[0] - 1][Location[1]] == 'G') pState = Win;
                Location[0]--;
                positionChanged = true;
            }
            Sleep(150); // Add delay to prevent rapid movement
        }
        if (GetAsyncKeyState('S') & 0x8000) {
            std::lock_guard<std::mutex> lock(mtx);
            if (Location[0] < MAP_H - 1 && (map[Location[0] + 1][Location[1]] == ' ' || map[Location[0] + 1][Location[1]] == 'D' || map[Location[0] + 1][Location[1]] == 'G')) {
                if (map[Location[0] + 1][Location[1]] == 'D') pState = Dead;
                if (map[Location[0] + 1][Location[1]] == 'G') pState = Win;
                Location[0]++;
                positionChanged = true;
            }
            Sleep(150);
        }
        if (GetAsyncKeyState('W') & 0x8000) {
            std::lock_guard<std::mutex> lock(mtx);
            if (Location[1] > 0 && (map[Location[0]][Location[1] - 1] == ' ' || map[Location[0]][Location[1] - 1] == 'D' || map[Location[0]][Location[1] - 1] == 'G')) {
                if (map[Location[0]][Location[1] - 1] == 'D') pState = Dead;
                if (map[Location[0]][Location[1] - 1] == 'G') pState = Win;
                Location[1]--;
                positionChanged = true;
            }
            Sleep(150);
        }
        if (GetAsyncKeyState('E') & 0x8000) {
            std::lock_guard<std::mutex> lock(mtx);
            if (Location[1] < MAP_W - 1 && (map[Location[0]][Location[1] + 1] == ' ' || map[Location[0]][Location[1] + 1] == 'D' || map[Location[0]][Location[1] + 1] == 'G')) {
                if (map[Location[0]][Location[1] + 1] == 'D') pState = Dead;
                if (map[Location[0]][Location[1] + 1] == 'G') pState = Win;
                Location[1]++;
                positionChanged = true;
            }
            Sleep(150);
        }
    }
}


void renderLoop() {
    std::lock_guard<std::mutex> lock(mtx);  // Lock mutex for synchronized access
    system("cls"); // Win command to clear screen
    for (int i = 0; i < MAP_H; i++) {
        for (int j = 0; j < MAP_W; j++) {
            if (i == Location[0] && j == Location[1]) {
                setConsoleColor(0x0B);
                std::cout << "P";
            }
            else {
                setConsoleColor(0x0A);
                std::cout << map[i][j];
            }
        }
        std::cout << "\n";
        setConsoleColor(0x0F);
        
    }
    std::cout << "Press N,S,E,W to move\n";
}
