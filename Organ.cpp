#include "Organ.hpp"
#include "Application.hpp"
#include "CellsLayer.hpp"


//constructor is crashing!
Organ::Organ(bool generation)
    { if(generation) generate(); //initialize attributes!!!
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

/*
createOrgan(); //create organ fragment
createBloodSystem(); //create blood network
*/

void Organ::updateRepresentation(bool changed){
    if(changed){
        for(int i(0); i < nbCells; ++i){
            for(int j(0); j < nbCells; ++j){
                CellCoord coord(i,j);
                updateRepresentationAt(coord);
            }
        }
    }
    drawRepresentation();
}

void Organ::drawRepresentation(){
    organTexture.clear(sf::Color(223,196,176));
    drawBloodCells();
    drawOrganCells();
    organTexture.display();
}

//@tom: how to make it less redudant??
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

void Organ::updateRepresentationAt(const CellCoord& coord){
    int i = coord.x;
    int j = coord.y;
    std::vector<std::size_t> indexes = indexesForCellVertexes(i, j, nbCells);
    if (cellsLayers[i][j]->hasBloodCell()){

        bloodVertexes[indexes[0]].color.a=255;
        bloodVertexes[indexes[1]].color.a=255;
        bloodVertexes[indexes[2]].color.a=255;
        bloodVertexes[indexes[3]].color.a=255;

        organVertexes[indexes[0]].color.a=0;
        organVertexes[indexes[1]].color.a=0;
        organVertexes[indexes[2]].color.a=0;
        organVertexes[indexes[3]].color.a=0;

    }else if (cellsLayers[i][j]->hasOrganCell() && !(cellsLayers[i][j]->hasBloodCell())){

        bloodVertexes[indexes[0]].color.a=0;
        bloodVertexes[indexes[1]].color.a=0;
        bloodVertexes[indexes[2]].color.a=0;
        bloodVertexes[indexes[3]].color.a=0;

        organVertexes[indexes[0]].color.a=255;
        organVertexes[indexes[1]].color.a=255;
        organVertexes[indexes[2]].color.a=255;
        organVertexes[indexes[3]].color.a=255;

    }else{

        bloodVertexes[indexes[0]].color.a=0;
        bloodVertexes[indexes[1]].color.a=0;
        bloodVertexes[indexes[2]].color.a=0;
        bloodVertexes[indexes[3]].color.a=0;

        organVertexes[indexes[0]].color.a=0;
        organVertexes[indexes[1]].color.a=0;
        organVertexes[indexes[2]].color.a=0;
        organVertexes[indexes[3]].color.a=0;

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

CellCoord Organ::toCellCoord(const Vec2d& position) const{
    return vec2dToCellCoord(position, nbCells, nbCells, cellSize);
}

void Organ::updateCellsLayer(const CellCoord& pos, Kind kind){
    if (kind == Kind::ECM){
        cellsLayers[pos.x][pos.y]->setECMCell();
    }
    if (kind == Kind::Organ){
        cellsLayers[pos.x][pos.y]->setOrganCell();
    }
    if (kind == Kind::Artery){
        cellsLayers[pos.x][pos.y]->setBlood(ARTERY);
    }
    if (kind == Kind::Capillary){
        cellsLayers[pos.x][pos.y]->setBlood(CAPILLARY);
    }
}
