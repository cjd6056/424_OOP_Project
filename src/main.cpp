
/*
AERSP 424 Final Project
Authors: Conor Dowdell, Gabrielle Dowdell, Shanon Hyde
Sources: https://www.geeksforgeeks.org/snake-code-cpp/
Video: https://www.youtube.com/watch?v=E_-lMZDi7Uw

OOP style: 3 main classes divided into their own header and cpp files (what vs. how)
{ 
    1. Snake
    2. Fuel
    3. Game
}
*/ 

#include <conio.h>
#include <windows.h> //Windows API
#include "Game.h"
#include <iostream>
#include <algorithm>
#include <cstring>
#include <limits>
#include <string>
using namespace std;

int main() 
{
    srand(static_cast<unsigned int>(time(0)));

    // Create a variable to track the number of games played
    int gamesPlayed = 0;
    
    //Code that helps with rendering issues. Found here: https://www.youtube.com/watch?v=PSoLD9mVXTA&t=2s 
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SMALL_RECT windowSize = { 0, 0, static_cast<SHORT>(width), static_cast<SHORT>(height) };
    SetConsoleWindowInfo(hConsole, TRUE, &windowSize);
    COORD bufferSize = { static_cast<SHORT>(width), static_cast<SHORT>(height) };
    SetConsoleScreenBufferSize(hConsole, bufferSize);

    // Pass the address of gamesPlayed to the Game constructor
    Game game(&gamesPlayed);
    game.play();

    return 0;
}

