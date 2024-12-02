#include "Snake.h"

Snake::Snake() 
{
    reset();
}

void Snake::reset() 
{
    x = width / 2;
    y = height / 2;
    tailLen = 0;
    direction = RIGHT;
    memset(tailX, 0, sizeof(tailX));
    memset(tailY, 0, sizeof(tailY));
}

void Snake::updatePosition() 
{
    for (int i = tailLen - 1; i > 0; i--) 
    {
        tailX[i] = tailX[i - 1];
        tailY[i] = tailY[i - 1];
    }
    if (tailLen > 0) 
    {
        tailX[0] = x;
        tailY[0] = y + 1; // Adjust for visual effect
    }
    switch (direction) 
    {
        case LEFT: x--; break;
        case RIGHT: x++; break;
        case UP: y--; break;
        case DOWN: y++; break;
    }
}

bool Snake::checkCollision() const 
{
    for (int i = 0; i < tailLen; i++) 
    {
        if (tailX[i] == x && tailY[i] == y + 1) // Adjust for visual effect
        {
            return true;
        }
    }
    return false;
}

void Snake::grow() 
{
    tailLen++;
}

