// GridWorld102946740.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>

enum State
{
    Alive, Dead, Win
};

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



int Location[2] = {7 , 2};

int main()
{
    gameLoop();
    return 0;
}

void gameLoop() {
    State pState = Alive;
    bool Loop = true;

    while (Loop) {
    
        switch (pState)
        {
        case Alive:
            renderLoop();
            input(pState);
            break;
        case Dead:
            renderLoop();
            std::cout << "You Died, Game Over \n";
            Loop = false;
            break;
        case Win:
            renderLoop();
            std::cout << "YOU WIN TOP G\n";
            Loop = false;
            break;
        }

    }
    
}

void input(State& pState) {
    char direction;
    std::cout << "What direction to move?" << "\n" << "N (north) S (south) E (east) W (west): \n";
    std::cin >> direction;

    if (std::toupper(direction) == 'N') { //location 1 for left right location 0 for up down
        if (map[Location[0]-1][Location[1]] == ' ') {
            Location[0]--; //-- for moving up
        } else if (map[Location[0] - 1][Location[1]] == 'D') {
            pState=Dead;
            Location[0]--;
        }
        else if (map[Location[0] - 1][Location[1]] == 'G') {
            pState = Win;
            Location[0]--;
        }
    }
    else if (std::toupper(direction) == 'S') {
        if (map[Location[0] + 1][Location[1]] == ' ') {
            Location[0]++; //++ for moving down
        }
        else if (map[Location[0] + 1][Location[1]] == 'D') {
            pState = Dead;
            Location[0]++;
        }
        else if (map[Location[0] + 1][Location[1]] == 'G') {
            pState = Win;
            Location[0]++;
        }
    }
    else if (std::toupper(direction) == 'W') {
        if (map[Location[0]][Location[1] - 1] == ' ') {
            Location[1]--; //-- for moving left
        }
        else if (map[Location[0]][Location[1] - 1] == 'D') {
            pState = Dead;
            Location[1]--;
        }
        else if (map[Location[0]][Location[1] - 1] == 'G') {
            pState = Win;
            Location[1]--;
        }
    }
    else if (std::toupper(direction) == 'E') {
        if (map[Location[0]][Location[1] + 1] == ' ') {
            Location[1]++; //++ for moving right
        }
        else if (map[Location[0]][Location[1] + 1] == 'D') {
            pState = Dead;
            Location[1]++;
        }
        else if (map[Location[0]][Location[1] + 1] == 'G') {
            pState = Win;
            Location[1]++;
        }
    }
}

void renderLoop() {
    system("cls"); //win command to clear screen
    for (int i = 0; i < MAP_H; i++) {
        for (int j = 0; j < MAP_W; j++) {
            if (i == Location[0] && j == Location[1])
            {
                std::cout << "p";
            }
            else {
                std::cout << map[i][j];
            }
            
        }
        std::cout << "\n";
    }
}
