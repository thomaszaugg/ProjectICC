#include "Organ.hpp"
#include "Application.hpp"

Organ::Organ(bool generation)
    {
if(generation) generate(); //initialize attributes!!!
}

void Organ::update(){
    updateRepresentation();
}
void Organ::drawOn(sf::RenderTarget& target){
    sf::Sprite image(organTexture.getTexture()); // transform the image into a texture
    target.draw(image); // display the texture
}


void Organ::generate(){
     reloadConfig();
   initOrganTexture (); //initalize organTexture
    /*createOrgan(); //create organ fragment
     createBloodSystem(); //create blood network*/
   updateRepresentation();
}

int Organ::getWidth (){
    return getAppConfig().simulation_organ_size;}

int Organ::getHeight(){
    return getAppConfig().simulation_organ_size;
}

void Organ::reloadConfig(){
     nbCells=getAppConfig().simulation_organ_nbCells;
     cellSize=getAppConfig().simulation_organ_size;
}

void Organ::initOrganTexture (){
        organTexture.create(nbCells*cellSize, nbCells*cellSize);
  }

/*createOrgan(); //create organ fragment
 createBloodSystem(); //create blood network*/

void Organ::updateRepresentation(){
    organTexture.clear(sf::Color(223,196,176));
    organTexture.display();
}

/*void Organ::updateRepresentationAt(const CellCoord&){

}
*/

bool Organ::isOut(CellCoord position){
    return position.x > nbCells or position.y > nbCells;
}

CellCoord Organ::toCellCoord(const Vec2d position){
    return vec2dToCellCoord(position, nbCells, nbCells, cellSize);
}

