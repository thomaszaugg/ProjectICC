#include "Pellets.hpp"
#include "Application.hpp"

Pellets::Pellets(Vec2d position)
    : Entity(position, getAppConfig().food_initial_energy)
{}

Quantity Pellets::provideEnergy(Quantity qte){
    if(qte>getEnergy()){qte=getEnergy();}
    substractEnergy(qte);
    return qte;
}

double Pellets::getSize() const{
    return getEnergy();
}

sf::Texture& Pellets::getTexture(){
    return getAppTexture(getAppConfig().food_texture);
}


