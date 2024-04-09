#include "Pellets.hpp"

Pellets::Pellets(Vec2d position)
    : Entity(position, getAppConfig().food_initial_energy)
{}

void Pellets::drawOn(sf::RenderTarget& target){
    sf::Sprite  entitySprite = buildSprite( getPosition(), getEnergy(), getAppTexture(getAppConfig().food_texture),getOrientation()/ DEG_TO_RAD); // conversion degree to radians becauce SFML uses these units
    target.draw(entitySprite);
     drawEnergy( target);
}

Quantity Pellets::provideEnergy(Quantity qte){
    if(qte>getEnergy()){qte=getEnergy();}
    substractEnergy(qte);
    return qte;
}
