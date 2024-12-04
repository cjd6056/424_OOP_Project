#ifndef ENDLESSGAMEMODE_H
#define ENDLESSGAMEMODE_H

#include "GameMode.h"
#include <iostream>

class EndlessGameMode : public GameMode {
public:
    void startGame() override {
        std::cout << "Starting Endless Game Mode!" << std::endl;
    }

    void endGame() override {
        std::cout << "Ending Endless Game Mode!" << std::endl;
    }
};

#endif // ENDLESSGAMEMODE_H
