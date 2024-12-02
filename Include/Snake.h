#ifndef SNAKE_H
#define SNAKE_H

#include <cstring>

const int width = 60;
const int height = 10;

enum snakesDirection { STOP = 0, LEFT, RIGHT, UP, DOWN };

class Snake 
{
public:
    int x, y;
    int tailX[100], tailY[100];
    int tailLen;
    snakesDirection direction;

    Snake();
    void reset();
    void updatePosition();
    bool checkCollision() const;
    void grow();
};

#endif // SNAKE_H
