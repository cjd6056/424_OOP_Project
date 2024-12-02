#include "Fruit.h"
#include <cstdlib>
#include <Snake.h>

Fruit::Fruit() 
{
    spawn();
}

void Fruit::spawn() 
{
    x = rand() % (width - 2) + 1;
    y = rand() % (height - 2) + 1;
}
