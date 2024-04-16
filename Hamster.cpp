#include "Hamster.hpp"
#include "Application.hpp"



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

double Hamster::getMaxSpeed(){
        double speed(getAppConfig().hamster_max_speed);
        if(getEnergy()< getFatigueEnergy()) speed*= getFatigueFactor();
        return speed;
    }
double Hamster::getFatigueEnergy(){ return 300;}

 double Hamster::getEnergyLoss() {
     return getAppConfig().hamster_energy_loss_factor;}

