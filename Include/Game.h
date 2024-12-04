#ifndef GAME_H
#define GAME_H

#include "Snake.h"
#include "Fuel.h"
#include "PlayerData.h"
#include "GameMode.h"  // Include the base class for game modes
#include <string>

class Game 
{
private:
    Snake snake;
    Fuel Fuel;
    int score, highScore, lives;
    bool isGameOver, isPaused, funMode;
    int speedDelay;
    std::string playerName;
    int* gamesPlayed;  // Pointer to track the number of games played
    PlayerData playerData;

    GameMode* currentGameMode;  // Pointer to GameMode class to handle different game modes

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
    void saveHighScore();
    void logError(const std::string& message);

    void setGameMode(bool isEndless);  // Function to set the game mode
    void startGame();  // Function to start the game based on the selected game mode
    void endGame();  // Function to end the game based on the selected game mode
};

#endif // GAME_H
