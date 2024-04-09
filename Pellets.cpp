#include "Pellets.hpp"


Pellets::Pellets(Vec2d position)
    : Entity(position, getAppConfig().food_initial_energy)
{}

void Pellets::drawOn(sf::RenderTarget& target){
    sf::Sprite  entitySprite = buildSprite( getPosition(), energy, getAppTexture(getAppConfig().hamster_texture_brown),getOrientation()/ DEG_TO_RAD); // conversion degree to radians becauce SFML uses these units
    target.draw(entitySprite);
}
