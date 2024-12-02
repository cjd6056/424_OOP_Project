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

public:
    Game();
    void init();
    void render();
    void setDifficulty();
    void handleInput();
    void update();
    void play();
    bool playAgain();
};

#endif // GAME_H
