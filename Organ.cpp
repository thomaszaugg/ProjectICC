#include "Organ.hpp"
#include "Application.hpp"
#include "CellsLayer.hpp"
#include <cmath>
#include "Random/Random.hpp"


Organ::Organ(bool generation)
    { if(generation) generate(); //initialize attributes!!!
}

//5.1
void Organ::update(){
    for(int i(0); i < nbCells; ++i){
        for(int j(0); j < nbCells; ++j){
            cellsLayers[i][j]->updateCells(); //function in CellsLayer does the updating of the cells, since there we habe access to the cells
        }
    }
    updateRepresentation();
}

void Organ::drawOn(sf::RenderTarget& target){
    sf::Sprite image(organTexture.getTexture()); // transform the image into a texture
    target.draw(image); // display the texture
}

void Organ::generate(){
    reloadConfig();
    initOrganTexture (); //initalize organTexture & initalize vertexes
    createOrgan(); //create organ fragment
     //createBloodSystem(); //create blood network
    updateRepresentation(true);
}

int Organ::getWidth () const{
    return getAppConfig().simulation_organ_size;
}

int Organ::getHeight() const{
    return getAppConfig().simulation_organ_size;
}

void Organ::reloadConfig(){
    nbCells=getAppConfig().simulation_organ_nbCells;
    cellSize=getWidth()/nbCells;
    std::vector<CellsLayer*> oneCellsLayers;

    for(int i(0); i < nbCells; ++i){
        oneCellsLayers.clear();
         for(int j(0); j < nbCells; ++j){
            CellCoord coord(i,j);
            CellsLayer* ptr(new CellsLayer(coord, this));
            oneCellsLayers.push_back(ptr);
        }
    cellsLayers.push_back(oneCellsLayers);
    }
}

void Organ::initOrganTexture (){
    organTexture.create(getWidth(), getHeight());
    bloodVertexes = generateVertexes(getAppConfig().simulation_organ["textures"], nbCells, cellSize);
    organVertexes = generateVertexes(getAppConfig().simulation_organ["textures"], nbCells, cellSize);
    //enonce: not more than four lines, this is only 3. What is missing?
}


void Organ::createBloodSystem(bool generateCapillaries){
    generateArtery();

    if(generateCapillaries) generateArtery();
}

void Organ::generateArtery(){
    int SIZE_ARTERY=1;
    //SIZE_ARTERY=max(1, 0.03*nbCells) how to use max function
    unsigned int startPoint((nbCells-SIZE_ARTERY)/2);
       for(int i(0); i < SIZE_ARTERY; ++i){
            int m(i+startPoint);
            CellCoord pos(0,m);
           for(int n(0); n < nbCells ; ++n){
               pos.x=n;
               updateCellsLayer(pos, Kind::Artery);
       }
   }}

void Organ::generateCapillary(){
    int LENGTH_CAPILLARY = ((nbCells/2) - 4);
    CellCoord dirCapillaryLeft(-1,0);
    CellCoord dirCapillaryRight(1,0);

    CellCoord current_position; //somehow generate starting points
    generateCapillaryFromPosition(current_position,dirCapillaryLeft);
}

void Organ::generateCapillaryOneStep(CellCoord& current_position , const CellCoord& dir, int& nbCells, const int& maxLength){
    if(nbCells==maxLength) return;



     //possibly changing direction
  std::vector<int> ballot(6, 0); //default=straight
  ballot[0]=1;  //down
  ballot[1]=2;  //up

  bool foundEmptyNeighbor(false);
         do{
      switch (uniform(ballot)){
      case 0:
         // current_position-(1,1);
          break;
      case 1:

          break;
      case 2:

          break;
     }
    //checking whether there is a cell there already and possibly continuing the drawing process
         }while (!foundEmptyNeighbor);
             updateCellsLayer(current_position, Kind::Capillary);


}

void Organ::generateCapillaryFromPosition(CellCoord &current_position , CellCoord dir){
    updateCellsLayer(current_position, Kind::Capillary);
    int nbCells(1);
    int LENGTH_CAPILLARY = ((nbCells/2) - 4);

    generateCapillaryOneStep(current_position,dir,nbCells, LENGTH_CAPILLARY);
}

//5.1
void Organ::createOrgan(){
    for(int i(0); i < nbCells; ++i){
        for(int j(0); j < nbCells; ++j){
            if (pow(i,2) + pow((j-nbCells),2) < pow((nbCells+1),2) && pow((i-nbCells),2) + pow(j,2) < pow((nbCells+1),2)){ //condition for being in organ
                CellCoord position(i,j);
                updateCellsLayer(position, Kind::Organ); //set the organCell with this function
            }
        }
    }
}


void Organ::updateRepresentation(bool changed){
    if(changed){                                //only if the organ changed
        for(int i(0); i < nbCells; ++i){        //iterates through the cells and updates them
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
    drawCells("blood cell");
    drawCells("organ cell");
    organTexture.display();
}


void Organ::drawCells(std::string name_cell){
    sf::RenderStates rs;
    auto textures = getAppConfig().simulation_organ["textures"];
    rs.texture = &getAppTexture(textures[name_cell].toString()); // here for the texture linked to a blood cell
   if(name_cell=="blood cell"){
        organTexture.draw(bloodVertexes.data(), bloodVertexes.size(), sf::Quads, rs);
   }else if(name_cell=="organ cell"){
        organTexture.draw(organVertexes.data(), organVertexes.size(), sf::Quads, rs);

   }}

void Organ::setVertexes1(const std::vector<std::size_t>& indexes, int a_blood, int a_organ){
    for( auto index : indexes){
        bloodVertexes[index].color.a= a_blood;
        organVertexes[index].color.a=a_organ;
    }
}

void Organ::updateRepresentationAt(const CellCoord& coord){
    int i = coord.x;
    int j = coord.y;
    //cellsLayers[i][j]->updateCells();
    std::vector<std::size_t> indexes = indexesForCellVertexes(i, j, nbCells);
    if (cellsLayers[i][j]->hasBloodCell()){
        setVertexes1(indexes, 255, 0);
    }else if (cellsLayers[i][j]->hasOrganCell()){
        setVertexes1(indexes, 0, 255);
    }else{
        setVertexes1(indexes, 0, 0);
    }
}

bool Organ::isOut(CellCoord position){
    return position.x<0 or position.x>=nbCells
        or position.y<0 or position.y>=nbCells;
}

CellCoord Organ::toCellCoord(const Vec2d& position) const{
    return  vec2dToCellCoord(position, getWidth(), getHeight(), cellSize);
}

void Organ::updateCellsLayer(const CellCoord& pos, Kind kind){
    switch(kind){
    case Kind::ECM:
        cellsLayers[pos.x][pos.y]->setECMCell();
        break;
    case Kind::Organ:
        cellsLayers[pos.x][pos.y]->setOrganCell();
        break;
    case Kind::Artery:
        cellsLayers[pos.x][pos.y]->setBlood(ARTERY);
        break;
    case Kind::Capillary:
        cellsLayers[pos.x][pos.y]->setBlood(CAPILLARY);
        break;
}}

