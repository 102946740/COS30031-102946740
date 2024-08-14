// GridWorld102946740.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <cctype>
#include <windows.h> 

enum State
{
    Alive, Dead, Win
};

void renderLoop(State pState);
State input();
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


int Location[2] = {7 , 2};

int main()
{
    system("color 0a"); // to change colour of screen lol
    gameLoop();
    return 0;
}

void gameLoop() {
    State pState = Alive;
    bool Loop = true;

    while (Loop) {
        renderLoop(pState);
        if (pState == Alive) {
            pState = input();
        }
        else {
            Loop = false;
        }
        

    }
    
}



bool checkNextLocation(char location_contents, State &returnState) {
    if (location_contents == ' ') {
        return true;
    }
    if (location_contents == 'D') {
        returnState = Dead;
        return true;
    }
    if (location_contents == 'G') {
        returnState = Win;
        return true;
    }
    else {
        return false;
    }
}

State input() {
    char direction;
    State NewState = Alive;
    std::cout << "What direction to move?" << "\n" << "N (north) S (south) E (east) W (west): \n";
    std::cin >> direction;


    if (std::toupper(direction) == 'N') {
        if (checkNextLocation(map[Location[0] - 1][Location[1]],NewState)) {
            Location[0]--;

        }
    }
    if (std::toupper(direction) == 'S') {
        if (checkNextLocation(map[Location[0] + 1][Location[1]], NewState)) {
            Location[0]++;
 
        }
    }
    else if (std::toupper(direction) == 'W') {
        if (checkNextLocation(map[Location[0]][Location[1] - 1], NewState)) {
            Location[1]--;

        }
    }
    else if (std::toupper(direction) == 'E') {
        if (checkNextLocation(map[Location[0]][Location[1] + 1], NewState)) {
            Location[1]++;

        }
    }


    return NewState;
}

void renderLoop(State pstate) {

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
    switch (pstate) {
    case Alive:
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
    
}
