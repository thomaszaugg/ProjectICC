#ifndef ANIMAL_HPP
#define ANIMAL_HPP
#include <Utility/Utility.hpp>
#include "Env/Entity.hpp"
#pragma once

class Animal : public Entity
{
public:
    Animal(const Vec2d& position, double energy)
        : Entity(position, energy){}
    virtual   ~Animal() {}

    //3.1
    bool isAnimal() override {return true;}
/*
    bool canBeConfined(Cage* cage) override;
*/
};


#endif // ANIMAL_HPP
