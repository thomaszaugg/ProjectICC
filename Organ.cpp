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
    bloodVertexes = generateVertexes(getAppConfig().simulation_organ["textures"], nbCells, cellSize);
    organVertexes = generateVertexes(getAppConfig().simulation_organ["textures"], nbCells, cellSize);
    //enonce: not more than four lines, this is only 3. What is missing?
}

void Organ::drawBloodCells(){
    sf::RenderStates rs;
    auto textures = getAppConfig().simulation_organ["textures"];
    rs.texture = &getAppTexture(textures["blood cell"].toString()); // here for the texture linked to a blood cell
    organTexture.draw(bloodVertexes.data(), bloodVertexes.size(), sf::Quads, rs);
}

void Organ::drawOrganCells(){
    sf::RenderStates rs;
    auto textures = getAppConfig().simulation_organ["textures"];
    rs.texture = &getAppTexture(textures["organ cell"].toString()); // here for the texture linked to a blood cell
    organTexture.draw(organVertexes.data(), organVertexes.size(), sf::Quads, rs);
}

/*
createOrgan(); //create organ fragment
createBloodSystem(); //create blood network
*/

void Organ::updateRepresentation(){
    //zuerst noch alles checken, dann erst zeichnen!
    organTexture.clear(sf::Color(223,196,176));
    drawBloodCells();
    drawOrganCells();
    organTexture.display();
}

void Organ::updateRepresentationAt(const CellCoord&){
    for(int i(0); i < nbCells; ++i){
        for(int j(0); j < nbCells; ++j){
            Cell* drawableCell = cellsLayers[i][j]->topCell();
            //make the cell in the corresponding vector drawable and in the other transparent
        }
    }
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

