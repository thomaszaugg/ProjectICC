#include "Cage.hpp"
#include "Application.hpp"


Cage::Cage(Vec2d position, double width, double height, double wallWidth)
    : position(position), width(width), height(height), wallWidth(wallWidth), occupied(false){

    initializeOneWall(position, width/2-wallWidth, -height/2+wallWidth, -width/2, -height/2);   //top
    initializeOneWall(position, width/2, height/2-wallWidth, width/2-wallWidth, -height/2);      //right
    initializeOneWall(position, width/2, height/2,-width/2+wallWidth, height/2-wallWidth);       //bottom
    initializeOneWall(position, -width/2+wallWidth, height/2, -width/2, -height/2+wallWidth);   //left
}

void Cage::initializeOneWall(Vec2d position, double h1_x, double h1_y, double h2_x, double h2_y){
    walls.push_back( Wall(Vec2d(h1_x, h1_y)+position,Vec2d(h2_x, h2_y)+position));
}

Vec2d Cage::getCenter()const{
    return position;
}

double Cage::getWidth()const{
    return width;
}

double Cage::getHeight()const{
    return height;
}

double Cage::getWallWidth()const{
    return wallWidth;
}

Wall Cage::getTop()const{
    return walls[0];
}

Wall Cage::getRight()const{
    return walls[1];
}

Wall Cage::getBottom()const{
    return walls[2];
}

Wall Cage::getLeft()const{
    return walls[3];
}

double Cage::getLeftLimit(bool intern)const{
        return position.x()-width/2+getWallWidthIf(intern);
}

double Cage::getRightLimit(bool intern)const{
        return position.x()+width/2-getWallWidthIf(intern);
}

double Cage::getTopLimit(bool intern)const{
        return position.y()-height/2+getWallWidthIf(intern);
}

double Cage::getBottomLimit(bool intern)const{
        return position.y()+height/2-getWallWidthIf(intern);
}

double Cage::getWallWidthIf(bool width)const{
    if(width) return wallWidth;
    return 0.;
}

bool Cage::isPositionInside(const Vec2d& position, double radius)const{

    return (position.x() - radius > getLeftLimit(true) && position.x() + radius < getRightLimit(true) &&
        position.y() - radius > getTopLimit(true) && position.y() + radius < getBottomLimit(true));
}

bool Cage::isPositionOnWall(const Vec2d& position)const{
     return (position.x() >= getLeftLimit(false) && position.x() <= getRightLimit(false) &&
        position.y() >= getTopLimit(false) && position.y() <= getBottomLimit(false) && isPositionInside(position) == false);
}

void Cage::drawOn(sf::RenderTarget& targetWindow) const{

    //draw the four walls individually

    sf::RectangleShape top = buildRectangle(this->getTop().second, this->getTop().first, &getAppTexture(getAppConfig().simulation_lab_fence));
    targetWindow.draw(top);

    sf::RectangleShape right = buildRectangle(this->getRight().second, this->getRight().first, &getAppTexture(getAppConfig().simulation_lab_fence));
    targetWindow.draw(right);

    sf::RectangleShape bottom = buildRectangle(this->getBottom().second, this->getBottom().first, &getAppTexture(getAppConfig().simulation_lab_fence));
    targetWindow.draw(bottom);

    sf::RectangleShape left = buildRectangle(this->getLeft().second, this->getLeft().first, &getAppTexture(getAppConfig().simulation_lab_fence));
    targetWindow.draw(left);
}

void Cage::addOccupant(){
    occupied=true;
}

void Cage::reset(){
    occupied = false;
}

bool Cage::isEmpty()const{
    return !occupied;
}
