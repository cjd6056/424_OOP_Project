#include "Fruit.h"
#include "Snake.h"
#include <cstdlib>

Fruit::Fruit() 
{
    spawn();
}

void Fruit::spawn() 
{
    x = rand() % (width - 2) + 1;
    y = rand() % (height - 2) + 1;
}
