#ifndef PELLETS_HPP
#define PELLETS_HPP
#include <Utility/Utility.hpp>
#include "Application.hpp"
#include "Entity.hpp"
#include <SFML/Graphics.hpp>
#pragma once

class Pellets : public Entity
{
public:
    Pellets(Vec2d position);
    Quantity provideEnergy(Quantity qte);

    virtual double getSize() override;
    virtual sf::Texture getTexture() override;
};

#endif // PELLETS_HPP
