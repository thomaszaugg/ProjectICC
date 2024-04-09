#ifndef HAMSTER_HPP
#define HAMSTER_HPP
#include <Utility/Utility.hpp>
#include "Env/Animal.hpp"
#include "Application.hpp"

class Hamster : public Animal
{
public:
    Hamster(Vec2d position);
    void drawOn(sf::RenderTarget& target);
};

#endif // HAMSTER_HPP
