#include "Fuel.h"
#include "Snake.h"
#include <cstdlib>
#include <utility> // For std::pair

// Constructor to spawn the Fuel at a random position
Fuel::Fuel() 
{
    spawn();
}

// Spawns the Fuel at a random position within the game grid
void Fuel::spawn() 
{
    x = rand() % (width - 2) + 1;
    y = rand() % (height - 2) + 1;
}

// Overload the equality operator to compare positions of Fuel and another Fuel
bool Fuel::operator==(const Fuel& other) const
{
    return x == other.x && y == other.y;
}

// Overload the += operator to move the Fuel by a given offset (e.g., for random movement)
Fuel& Fuel::operator+=(const std::pair<int, int>& offset)
{
    x += offset.first;
    y += offset.second;
    return *this;
}
