#ifndef FRUIT_H
#define FRUIT_H

#include <utility> // For std::pair

class Fruit 
{
public:
    int x, y;

    Fruit();
    void spawn();

    // Overload equality operator to compare positions of Fruit and Snake
    bool operator==(const Fruit& other) const;

    // Overload += operator to allow movement of the fruit by a given offset
    Fruit& operator+=(const std::pair<int, int>& offset); // Fix type and include <utility>
};

#endif // FRUIT_H
