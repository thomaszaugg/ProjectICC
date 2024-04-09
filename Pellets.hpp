#ifndef PELLETS_HPP
#define PELLETS_HPP
#include <Utility/Utility.hpp>
#include "Application.hpp"
#include "Entity.hpp"
#include <SFML/Graphics.hpp>

class Pellets : public Entity
{
public:
    Pellets(Vec2d position);
    void drawOn(sf::RenderTarget& target);
};

#endif // PELLETS_HPP
