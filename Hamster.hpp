#ifndef HAMSTER_HPP
#define HAMSTER_HPP
#include <Utility/Utility.hpp>
#include "Animal.cpp"

class Animal;

class Hamster : public Animal
{
public:
    Hamster(Vec2d position);
    void drawOn(sf::RenderTarget& target);
};

#endif // HAMSTER_HPP
