#include "Pellets.hpp"

Pellets::Pellets(Vec2d position)
    : Entity(position, getAppConfig().food_initial_energy)
{}

Quantity Pellets::provideEnergy(Quantity qte){
    if(qte>getEnergy()){qte=getEnergy();}
    substractEnergy(qte);
    return qte;
}

double Pellets::getSize(){
    return getEnergy();
}

sf::Texture Pellets::getTexture(){
    return getAppTexture(getAppConfig().food_texture);
}
