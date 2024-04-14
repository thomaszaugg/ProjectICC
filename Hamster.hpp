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
    virtual double getSize() const override; //3.1 const
    virtual sf::Texture& getTexture() override;
    virtual double getRadius() const override; //3.1 const

};

#endif // HAMSTER_HPP
