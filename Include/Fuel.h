#ifndef FUEL_H
#define FUEL_H

#include <utility> // For std::pair

class Fuel 
{
public:
    int x, y;

    Fuel();
    void spawn();

    // Overload equality operator to compare positions of Fuel and Snake
    bool operator==(const Fuel& other) const;

    // Overload += operator to allow movement of the Fuel by a given offset
    Fuel& operator+=(const std::pair<int, int>& offset); // Fix type and include <utility>
};

#endif // Fuel_H
