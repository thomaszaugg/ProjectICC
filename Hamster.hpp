#ifndef HAMSTER_HPP
#define HAMSTER_HPP
#include <Utility/Utility.hpp>
#include "Animal.cpp"
#pragma once

class Animal;

class Hamster : public Animal
{
public:
    Hamster(Vec2d position);
    virtual sf::Time getLongevity() override;
    virtual double getSize() override;
    virtual sf::Texture getTexture() override;
};

#endif // HAMSTER_HPP
