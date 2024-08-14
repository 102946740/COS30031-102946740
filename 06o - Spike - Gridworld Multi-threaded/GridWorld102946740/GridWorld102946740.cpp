// GridWorld102946740.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <cctype>
#include <windows.h> 
#include <thread>


enum State {
    Alive, Dead, Win
};
State pState = Alive;

bool positionChanged = true; // Initially true to render the first frame

void renderLoop();
void input();
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

int main() {
    system("color 0a"); // to change colour of screen lol
    gameLoop();
    return 0;
}

void gameLoop() {
    bool Loop = true;

    std::thread inputThread(input);

    while (Loop) {
        if (positionChanged) {
            std::thread renderThread(renderLoop);
            renderThread.join();
            positionChanged = false; // Reset the flag after rendering
        }
        if (pState == Dead || pState == Win) {
            Loop = false;
        }
    }

    inputThread.join();
}

bool checkNextLocation(char location_contents) {
    if (location_contents == ' ') {
        return true;
    }
    if (location_contents == 'D') {
        pState = Dead;
        return true;
    }
    if (location_contents == 'G') {
        pState = Win;
        return true;
    }
    else {
        return false;
    }
}

void input() {
    while (pState == Alive) {
        if (GetAsyncKeyState('N') & 0x8000) {
            if (checkNextLocation(map[Location[0]-1][Location[1]])) {
                Location[0]--;
                positionChanged = true;
                
            }
        }
        else if (GetAsyncKeyState('S') & 0x8000) {
            if (checkNextLocation(map[Location[0] + 1][Location[1]])) {
                Location[0]++;
                positionChanged = true;
                
            }
        }
        else if (GetAsyncKeyState('W') & 0x8000) {
            if (checkNextLocation(map[Location[0]][Location[1] - 1])) {
                Location[1]--;
                positionChanged = true;
  
            }
        }
        else if (GetAsyncKeyState('E') & 0x8000) {
            if (checkNextLocation(map[Location[0]][Location[1] + 1])) {
                Location[1]++;
                positionChanged = true;
                
            }
        }
        Sleep(150);
        
    }
    
}




void renderLoop() {

    system("cls"); //win command to clear screen
    for (int i = 0; i < MAP_H; i++) {
        for (int j = 0; j < MAP_W; j++) {
            if (i == Location[0] && j == Location[1])
            {
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
    switch (pState) {
    case Alive:
        std::cout << "Use N, E, S, W to move";
        break;
    case Win:
        setConsoleColor(0x0E);
        std::cout << "You Win";
        break;
    case Dead:
        setConsoleColor(0x0C);
        std::cout << "You Lose";
        break;
    default:
        break;
    }
    while (!positionChanged) {

    }
    Sleep(16);

}
