#ifndef ANIMAL_HPP
#define ANIMAL_HPP
#include <Utility/Utility.hpp>
#include "Entity.hpp"
#include "Cage.hpp"
#pragma once

class Animal : public Entity
{
public:
    Animal(const Vec2d& position, double energy)
        : Entity(position, energy){}

    //3.1
    bool isAnimal() override;

    bool canBeConfined(Cage* cage) override;

    virtual ~Animal() {}

};

bool addOccupant(Cage* cage, Animal* a);

#endif // ANIMAL_HPP
