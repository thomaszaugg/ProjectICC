#include "Organ.hpp"
#include "Application.hpp"
#include "CellsLayer.hpp"
#include <cmath>
#include "Random/Random.hpp"


Organ::Organ(bool generation)
    {if(generation) generate(); //initialize attributes!!!
}

void Organ::generate(){
    reloadConfig();      //create the grid of cellslayers
    initOrganTexture (); //initalize organTexture & initalize vertexes
    createBloodSystem(); //create blood network
    createOrgan();       //create organ fragment

    updateRepresentation(true);
}

void Organ::reloadConfig(){
    nbCells=getAppConfig().simulation_organ_nbCells;
    cellSize=getWidth()/nbCells;
    std::vector<CellsLayer*> oneCellsLayers;
    currentSubst=GLUCOSE;
    deltas={0,0,0};

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
    concentrationVertexes = generateVertexes(getAppConfig().simulation_organ["textures"], nbCells, cellSize);
    organCancerVertexes = generateVertexes(getAppConfig().simulation_organ["textures"], nbCells, cellSize);
}

void Organ::createOrgan(){
    for(int i(0); i < nbCells; ++i){
        for(int j(0); j < nbCells; ++j){
            CellCoord position(i,j);
            if (organBoundaries(position)){
                updateCellsLayer(position, Kind::Organ); //set the organCell with this function
            }
        }
    }
}

bool Organ::organBoundaries(CellCoord pos) const{
    int i = pos.x;
    int j = pos.y;
    return pow(i,2) + pow((j-nbCells),2) < pow((nbCells+1),2) && pow((i-nbCells),2) + pow(j,2) < pow((nbCells+1),2); //condition for being in organ
}

void Organ::update(){
    sf::Time dt=sf::seconds(getAppConfig().simulation_fixed_step);
    bool changed = false;
    for(int i(0); i < nbCells; ++i){
        for(int j(0); j < nbCells; ++j){
            cellsLayers[i][j]->update(dt); //function in CellsLayer does the updating of the cells, since there we have access to the cells
        }
    }
    if(getApp().isConcentrationOn()){
        changed = true;
    }
    updateRepresentation(changed);
}

void Organ::drawOn(sf::RenderTarget& target){
    sf::Sprite image(organTexture.getTexture()); // transform the image into a texture
    target.draw(image); // display the texture
}

int Organ::getWidth () const{
    return getAppConfig().simulation_organ_size;
}

int Organ::getHeight() const{
    return getAppConfig().simulation_organ_size;
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
    if(getApp().isConcentrationOn()){
            organTexture.clear(sf::Color(0,0,0));
            drawCells("concentration");
            drawCells("blood cell");
    }else { organTexture.clear(sf::Color(223,196,176));
        drawCells("blood cell");
        drawCells("organ cell");
        drawCells("cancer");
        }

    organTexture.display();
}


void Organ::drawCells(std::string name_cell){

    if(name_cell=="concentration"){     //adjusts name_cell in the case of concentration
            switch(currentSubst){
            case GLUCOSE:
                name_cell="glucose";
                break;
            case BROMOPYRUVATE:
                name_cell="bromopyruvate";
                break;
            case VGEF:
                name_cell="vgef";
                break;
             default:
                ;
            }}

    sf::RenderStates rs;
    auto textures = getAppConfig().simulation_organ["textures"];
    rs.texture = &getAppTexture(textures[name_cell].toString()); // here for the texture linked to a blood cell

    if(name_cell=="blood cell"){
        organTexture.draw(bloodVertexes.data(), bloodVertexes.size(), sf::Quads, rs);
    }else if(name_cell=="organ cell"){
        organTexture.draw(organVertexes.data(), organVertexes.size(), sf::Quads, rs);
    }else if(name_cell=="cancer"){
        organTexture.draw(organCancerVertexes.data(), organCancerVertexes.size(), sf::Quads, rs);
    } else {
         organTexture.draw(concentrationVertexes.data(), concentrationVertexes.size(), sf::Quads, rs);
        }

}

void Organ::setVertexes1(const std::vector<std::size_t>& indexes, int a_blood, int a_organ, int a_cancer, bool concentrationOn, double ratio){
    for( auto index : indexes){

        if(concentrationOn){
            concentrationVertexes[index].color.a= std::max(int(ratio * 255), 5);
        }else{
            bloodVertexes[index].color.a= a_blood;
            organVertexes[index].color.a= a_organ;
            organCancerVertexes[index].color.a = a_cancer;
        }
    }
}

void Organ::updateRepresentationAt(const CellCoord& coord){
    int i = coord.x;
    int j = coord.y;
    std::vector<std::size_t> indexes = indexesForCellVertexes(i, j, nbCells);

    //is this the right place?
    if (cellsLayers[i][j]->hasBloodCell()){
        setVertexes1(indexes, 255, 0, 0);
    }else if (cellsLayers[i][j]->hasOrganCell() && cellsLayers[i][j]->hasCancer()){
        setVertexes1(indexes, 0, 0, 255);
    }else if (cellsLayers[i][j]->hasOrganCell() && !cellsLayers[i][j]->hasCancer()){
        setVertexes1(indexes, 0, 255, 0);
    }else{
        setVertexes1(indexes, 0, 0, 0);
    }
    if(getApp().isConcentrationOn() && !cellsLayers[i][j]->hasBloodCell()){
        double ratio= (getConcentrationAt(coord,currentSubst))/getAppConfig().substance_max_value;
        setVertexes1(indexes, 0, 0, 0, true, ratio);
    }
}

void Organ::updateCellsLayerAt(const CellCoord& pos, const Substance& diffusedSubst){
    cellsLayers[pos.x][pos.y]->updateSubstance(diffusedSubst); //which one is y and which one x?

}

bool Organ::isOut(CellCoord position)const{
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


void Organ::createBloodSystem(bool generateCapillaries){
    int leftColumn(0);
    int rightColumn(0);

    this->generateArtery(leftColumn, rightColumn);

    --leftColumn;   //transform the value from where the artery begins
                    //to where the capillary starts

    if(generateCapillaries) this->generateCapillary(leftColumn, rightColumn);

}

void Organ::generateArtery(int& leftColumn, int& rightColumn){
    int SIZE_ARTERY=1;
    SIZE_ARTERY=std::max(1., 0.03*nbCells);

    leftColumn=((nbCells-SIZE_ARTERY)/2);
    rightColumn=leftColumn+SIZE_ARTERY;

    for(int i(leftColumn); i < rightColumn; ++i){
        CellCoord pos(i,0);
        for(int j(0); j < nbCells ; ++j){
            pos.y=j;
            updateCellsLayer(pos, Kind::Artery);
        }
    }}

void Organ::generateCapillary(int const& leftColumn, int const& rightColumn){

    generateOneSideCapillary({-1,0},  leftColumn);
    generateOneSideCapillary({1,0},  rightColumn);
}

void Organ::generateOneSideCapillary(CellCoord const& direction, int const& column){
    std::vector<CellCoord> starting_points(generateStartingPositions(column));
    for(auto starting_point: starting_points){
        generateCapillaryFromPosition(starting_point,direction);
    }
}
std::vector<CellCoord> const Organ::generateStartingPositions(int const& column){
    std::vector<CellCoord> starting_points;

    int minDistance=getAppConfig().blood_capillary_min_dist;
    int START_CREATION_FROM(getAppConfig().blood_creation_start);
    unsigned int maxNB_CAPILLARY=(nbCells-START_CREATION_FROM)/3;
    int random_nb(0);
    int lastValue(START_CREATION_FROM); //initialized as big enough value

    for(int i(START_CREATION_FROM); i < nbCells-START_CREATION_FROM; ++i){

        random_nb= uniform(1,3);
        int variable  (i - lastValue);              //doesn't seem to work
        if(random_nb==2 and (minDistance <=variable)){  //only creates new starting point with 1/3 probability
            starting_points.push_back({column, i});                     // and after cecking that the last starting point is far enough
            lastValue=i;
        }
        if(starting_points.size() == maxNB_CAPILLARY) return starting_points;

    }

    return starting_points;
}


void Organ::checkStep(bool& direction_step_possible, bool& empty_neighboor_found, CellCoord current_position, CellCoord dir){

    direction_step_possible = (!isOut(dir+current_position) and !cellsLayers[current_position.x+dir.x][current_position.y+dir.y]->hasBloodCell());
    empty_neighboor_found = direction_step_possible;
}

bool Organ::generateCapillaryOneStep(CellCoord& current_position, const CellCoord& dir, int& nbCells, const int& maxLength){
    if(nbCells==maxLength) return false;    //stops process if maxLength reached

    CellCoord direction_step=dir;
    bool straight_step_possible(true);
    bool up_step_possible(true);
    bool down_step_possible(true);
    bool empty_neighboor_found(false);
    int random_nb(0);

    do{                                     //following algorithm chooses a direction to next grow into
        random_nb=uniform(1,6);   //first, it draws a int out of 6, the probility to go up, down and straight is 1/6,1/6, 4/6 respectively
            //then, it checks whether this step is possible using the stepCheck function:
            //if yes, empty_neighboor_found indicates to stop the while loop
            //if no, the corresponding direction_step_variable marks the direction as not possible
            //if all the directions have been marked as not possible, the function return false
        if(random_nb==1 and up_step_possible){            //up
            direction_step={0,-1};
            checkStep(up_step_possible, empty_neighboor_found, current_position, direction_step);
        }else if (random_nb==2 and down_step_possible){   //down
            direction_step={0,1};
            checkStep(down_step_possible, empty_neighboor_found, current_position, direction_step);
        }else if (straight_step_possible){                //straight
            direction_step=dir;
            checkStep(straight_step_possible, empty_neighboor_found, current_position, direction_step);
        } else if (!(up_step_possible and down_step_possible and straight_step_possible)){                                          //no step possible
            return false;
        }

    }while (!empty_neighboor_found);

    // here, a step is possible
    current_position+=direction_step;
    updateCellsLayer(current_position, Kind::Capillary);
    ++nbCells;
    return true;
}

void Organ::generateCapillaryFromPosition(CellCoord &current_position , CellCoord dir){
    //generate the first cell
    updateCellsLayer(current_position, Kind::Capillary);
    int nbCells(1);
    int LENGTH_CAPILLARY = ((Organ::nbCells/2)-4);

    //genereate the rest
    while(generateCapillaryOneStep(current_position,dir,nbCells, LENGTH_CAPILLARY));
}


double Organ::getConcentrationAt(const CellCoord& pos, SubstanceId id){
    return cellsLayers[pos.x][pos.y]->getECMQuantity(id);
}

void  Organ::nextSubstance(){
   currentSubst = (SubstanceId)((currentSubst+1)%NB_SUBST);

}

void Organ::changeDeltaSubstance(bool minus){
    double deltaSubstance(0);
    switch (currentSubst) {
        case GLUCOSE:
            deltaSubstance = getAppConfig().delta_glucose;
            break;
        case BROMOPYRUVATE:
            deltaSubstance = getAppConfig().delta_bromo;
            break;
        case VGEF:
            deltaSubstance = getAppConfig().delta_vgef;
            break;
        default:
            // Handle the default case if necessary
            break;
    }

    if(minus) deltaSubstance*=(-1);

    deltas[currentSubst]+=deltaSubstance;

    deltas[currentSubst]= std::max(-getAppConfig().substance_max_value, deltas[currentSubst]);
    deltas[currentSubst]= std::min(getAppConfig().substance_max_value, deltas[currentSubst]);
}

double Organ::getDelta(SubstanceId id) {
    return deltas[id];
}

SubstanceId Organ::getCurrentSubst(){
return currentSubst;
}

void Organ::setCancerAt(const Vec2d& position){
    CellCoord pos = toCellCoord(position);
    cellsLayers[pos.x][pos.y]->setCancer();
}

bool Organ::requestToDivide(CellCoord pos, bool hasCancer){
    std::vector<CellCoord> possiblePositions= getPossiblePositions(pos, hasCancer);

    int numberOfPositions=possiblePositions.size();
    if(numberOfPositions==0) return false;

    CellCoord choosenPos=possiblePositions[uniform(0,numberOfPositions-1)];

    if(hasCancer){
        setCancerAt(choosenPos);
    }else{
        cellsLayers[choosenPos.x][choosenPos.y]->setOrganCell();
    }

    return true;

}

std::vector<CellCoord> Organ::getPossiblePositions(CellCoord pos, bool hasCancer) const{
    std::vector<CellCoord> possiblePositions;
    int x=pos.x;
    int y=pos.y;
    if(isDivisonPossible(x-1,y-1, hasCancer)) possiblePositions.push_back(CellCoord(x-1,y-1));
    if(isDivisonPossible(x+1,y-1, hasCancer)) possiblePositions.push_back(CellCoord(x+1,y-1));
    if(isDivisonPossible(x-1,y+1, hasCancer)) possiblePositions.push_back(CellCoord(x-1,y+1));
    if(isDivisonPossible(x+1,y+1, hasCancer)) possiblePositions.push_back(CellCoord(x+1,y+1));

    return possiblePositions;
}

bool Organ::isDivisonPossible(int x, int y, bool hasCancer)const{
    return (!isOut(CellCoord(x,y))) and
            (hasCancer or (!cellsLayers[x][y]->hasOrganCell() and isInsideLiver(CellCoord(x,y))));
}

bool Organ::isInsideLiver(CellCoord pos) const{
    return organBoundaries(pos); //this should return true if it is inside the initial bounderies
}
