#include "Hamster.hpp"



Hamster::Hamster(Vec2d position)
    :   Animal(position, getAppConfig().hamster_energy_initial){
}

void Hamster::drawOn(sf::RenderTarget& target){
    sf::Sprite  entitySprite = buildSprite( getPosition(), getAppConfig().hamster_size, getAppTexture(getAppConfig().hamster_texture_brown),getOrientation()/ DEG_TO_RAD); // conversion degree to radians becauce SFML uses these units
    target.draw(entitySprite);

    drawEnergy( target);
}
sf::Time Hamster::getLongevity(){
    return getAppConfig().hamster_longevity;
}
