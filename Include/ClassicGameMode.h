#ifndef CLASSICGAMEMODE_H
#define CLASSICGAMEMODE_H

#include "GameMode.h"
#include <iostream>

class ClassicGameMode : public GameMode {
public:
    void startGame() override {
        std::cout << "Starting Classic Game Mode!" << std::endl;
    }

    void endGame() override {
        std::cout << "Ending Classic Game Mode!" << std::endl;
    }
};

#endif // CLASSICGAMEMODE_H
