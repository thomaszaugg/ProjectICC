#include "Hamster.hpp"
#include "Application.hpp"



Hamster::Hamster(Vec2d position)
    :Animal(position, getAppConfig().hamster_energy_initial){
}

sf::Time Hamster::getLongevity() const{
    return getAppConfig().hamster_longevity;
}

double Hamster::getSize() const{
    return getAppConfig().hamster_size;
}

sf::Texture& Hamster::getTexture() const{
    if(isSick()){return getAppTexture(getAppConfig().hamster_texture_sick);}
    else {return getAppTexture(getAppConfig().hamster_texture_brown);}
}

double Hamster::getMaxSpeed() const{
    if(isSick()){return 0.6*getAppConfig().hamster_max_speed;}
    return getAppConfig().hamster_max_speed;
}

double Hamster::getFatigueEnergy() const{
    return 300;
}

double Hamster::getEnergyLoss() const{
    return getAppConfig().hamster_energy_loss_factor;
}

bool Hamster::canConsume(Entity const* entity) const {
    return entity->consumableBy(this);
}

bool Hamster::consumableBy(Pellets const*)const{
    return false;
}

bool Hamster::consumableBy(Hamster const*) const {
    return false;
}

bool Hamster::consumableBy(Cheese const*) const{
    return false;
}

double Hamster::getMass()const{
    return getAppConfig().hamster_mass ;
}

double Hamster::getDeceleration() const {
    return getAppConfig().hamster_deceleration;
}

double Hamster::getEnergyBite() const{
    return getAppConfig().hamster_energy_bite*0.01;
}

