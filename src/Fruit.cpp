#include "Fruit.h"
#include "Snake.h"
#include <cstdlib>
#include <utility> // For std::pair

// Constructor to spawn the fruit at a random position
Fruit::Fruit() 
{
    spawn();
}

// Spawns the fruit at a random position within the game grid
void Fruit::spawn() 
{
    x = rand() % (width - 2) + 1;
    y = rand() % (height - 2) + 1;
}

// Overload the equality operator to compare positions of Fruit and another Fruit
bool Fruit::operator==(const Fruit& other) const
{
    return x == other.x && y == other.y;
}

// Overload the += operator to move the fruit by a given offset (e.g., for random movement)
Fruit& Fruit::operator+=(const std::pair<int, int>& offset)
{
    x += offset.first;
    y += offset.second;
    return *this;
}
