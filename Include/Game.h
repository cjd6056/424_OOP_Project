#ifndef GAME_H
#define GAME_H

#include "Snake.h"
#include "Fruit.h"
#include <string>

class Game 
{
private:
    Snake snake;
    Fruit fruit;
    int score, highScore, lives;
    bool isGameOver, isPaused, funMode;
    int speedDelay;
    std::string playerName;
    int* gamesPlayed;  // Pointer to track the number of games played

public:
    Game(int* gamesPtr);  // Constructor with pointer to gamesPlayed
    void init();
    void render();
    void setDifficulty();
    void handleInput();
    void update();
    void play();
    bool playAgain();
    void incrementGamesPlayed();  // Function to update games played
};

#endif // GAME_H
