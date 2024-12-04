#ifndef GAMEMODE_H
#define GAMEMODE_H


class GameMode //created for use of inheritance
{
public:
    virtual void startGame() = 0;  // Pure virtual function to start the game
    virtual void endGame() = 0;    // Pure virtual function to end the game
};

#endif // GAMEMODE_H
