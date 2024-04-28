#include "Organ.hpp"
#include "Application.hpp"
#include "Cellslayer.hpp"

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
     cellSize=getWidth()/nbCells;

     // @lisa: initialize the following:(and my attempts to do it...
     //std::array<std::array<CellsLayer*, 10>, 10> cellsLayers_;
//cellsLayers = new std::vector<std::vector<CellsLayer*, nbCells > nbCells > ;
   /*
     for( int i(0); i < nbCells; ++i){
         for(int j(0); j < nbCells; ++j){
             CellCoord coord(i,j); //@lisa which is which ?
             CellsLayer* ptr(new CellsLayer(coord, this));
             cellsLayers[i][j]= ptr; //again the same
         }
     }*/
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
    return position.x > nbCells or position.y > nbCells;    //stats CellCord at 0?
}

CellCoord Organ::toCellCoord(const Vec2d position){
    return vec2dToCellCoord(position, nbCells, nbCells, cellSize);
}

