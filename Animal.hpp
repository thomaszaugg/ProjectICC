#ifndef ANIMAL_HPP
#define ANIMAL_HPP
#include <Utility/Utility.hpp>
#include "Env/Entity.hpp"

class Animal : public Entity
{
public:
    Animal(const Vec2d& position, double energy);
};

#endif // ANIMAL_HPP
