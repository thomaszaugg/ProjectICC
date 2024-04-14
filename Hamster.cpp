#include "Hamster.hpp"



Hamster::Hamster(Vec2d position)
    :   Animal(position, getAppConfig().hamster_energy_initial){
}

sf::Time Hamster::getLongevity(){
    return getAppConfig().hamster_longevity;
}

double Hamster::getSize() const{
    return getAppConfig().hamster_size;
}

sf::Texture& Hamster::getTexture(){
    return getAppTexture(getAppConfig().hamster_texture_brown);
}

double Hamster::getRadius() const{
    return getSize()/2;
}
