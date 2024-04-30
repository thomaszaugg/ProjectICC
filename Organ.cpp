#include "Organ.hpp"
#include "Application.hpp"
#include "Cellslayer.hpp"

Organ::Organ(bool generation)
    { if(generation) generate(); //initialize attributes!!!
}

void Organ::update(){
    updateRepresentation();
}

void Organ::drawOn(sf::RenderTarget& target){
    sf::Sprite image(organTexture.getTexture()); // transform the image into a texture
    target.draw(image); // display the texture

    //4.3 -> drawing this properly
}

//code to draw quads -> have to use it once for blood and once for organ cells
//vertexes = set of vertexes we want to draw
/*
    sf::RenderStates rs;
    auto textures = getAppConfig().simulation_organ["textures"];
    rs.texture = &getAppTexture(textures["blood cell"].toString()); // here for the texture linked to a blood cell

    // we draw on the image associated with Organ
    // and not directly in the window:

    organTexture_.draw(vertexes.data(), vertexes.size(), sf::Quads, rs);
*/

void Organ::generate(){
    reloadConfig();
    initOrganTexture (); //initalize organTexture & initalize vertexes
    /*createOrgan(); //create organ fragment
     createBloodSystem(); //create blood network*/
    updateRepresentation();
}

int Organ::getWidth (){
    return getAppConfig().simulation_organ_size;
}

int Organ::getHeight(){
    return getAppConfig().simulation_organ_size;
}

void Organ::reloadConfig(){
    nbCells=getAppConfig().simulation_organ_nbCells;
    cellSize=getWidth()/nbCells;
    std::vector<std::vector<CellsLayer*>> cellsLayers(nbCells, std::vector<CellsLayer*>(nbCells));

    for(int i(0); i < nbCells; ++i){
        for(int j(0); j < nbCells; ++j){
            CellCoord coord(i,j);
            CellsLayer* ptr(new CellsLayer(coord, this));
            cellsLayers[i][j]= ptr;
        }
    }
}

void Organ::initOrganTexture (){
    organTexture.create(nbCells*cellSize, nbCells*cellSize); //@tom: or put getHeight for reasons of simpicity
    //generateVertexes(getAppConfig().simulation_organ["textures"], nbCells, cellSize);
    //initalize vertexes ->  with all elements
}

/*createOrgan(); //create organ fragment
 createBloodSystem(); //create blood network*/

void Organ::updateRepresentation(){
    organTexture.clear(sf::Color(223,196,176));
    organTexture.display();
}

void Organ::updateRepresentationAt(const CellCoord&){

}

bool Organ::isOut(CellCoord position){
    for(int i(0); i < nbCells; ++i){
        for(int j(0); j < nbCells; ++j){
            if (position.x == i and position.y == j){
                return false;
            }
        }
    }
    return true;
}

CellCoord Organ::toCellCoord(const Vec2d position){
    return vec2dToCellCoord(position, nbCells, nbCells, cellSize);
}

