#include "Cage.hpp"
#include "Application.hpp"
//#include "Lab.hpp"

Cage::Cage(Vec2d position, double width, double height, double wallWidth)
    : position(position), width(width), height(height), wallWidth(wallWidth), occupied(false){

    Vec2d h2(-width/2, -height/2);
    h2+=position;
    Vec2d h1(width/2-wallWidth, -height/2+wallWidth);
    h1+=position;
    Wall top(h1, h2);
    walls.push_back(top);

    Vec2d h4(width/2-wallWidth, -height/2);
    h4+=position;
    Vec2d h3(width/2, height/2-wallWidth);
    h3+=position;
    Wall right(h3,h4);
    walls.push_back(right);

    Vec2d h6(-width/2+wallWidth, height/2-wallWidth);
    h6+=position;
    Vec2d h5(width/2, height/2);
    h5+=position;
    Wall bottom(h5,h6);
    walls.push_back(bottom);

    Vec2d h8(-width/2, -height/2+wallWidth);
    h8+=position;
    Vec2d h7(-width/2+wallWidth, height/2);
    h7+=position;
    Wall left(h7,h8);
    walls.push_back(left);

}

Vec2d Cage::getCenter(){
    return position;
}

double Cage::getWidth(){
    return width;
}

double Cage::getHeight(){
    return height;
}

double Cage::getWallWidth(){
    return wallWidth;
}

Wall Cage::getTop(){
    return walls[0];
}

Wall Cage::getRight(){
    return walls[1];
}

Wall Cage::getBottom(){
    return walls[2];
}

Wall Cage::getLeft(){
    return walls[3];
}

double Cage::getLeftLimit(bool intern){
    if (intern){
        return position.x()-width/2+wallWidth;
    }else{
        return position.x()-width/2;
    }
}

double Cage::getRightLimit(bool intern){
    if (intern){
        return position.x()+width/2-wallWidth;
    }else{
        return position.x()+width/2;
    }
}

double Cage::getTopLimit(bool intern){
    if (intern){
        return position.y()-height/2+wallWidth;
    }else{
        return position.y()-height/2;
    }
}

double Cage::getBottomLimit(bool intern){
    if (intern){
        return position.y()+height/2-wallWidth;
    }else{
        return position.y()+height/2;
    }
}

bool Cage::isPositionInside(const Vec2d& position, double radius){

    if (position.x() - radius > getLeftLimit(true) && position.x() + radius < getRightLimit(true) &&
        position.y() - radius > getTopLimit(true) && position.y() + radius < getBottomLimit(true)){
        return true;
    }else{
        return false;
    }
}

bool Cage::isPositionOnWall(const Vec2d& position){
    if (position.x() >= getLeftLimit(false) && position.x() <= getRightLimit(false) &&
        position.y() >= getTopLimit(false) && position.y() <= getBottomLimit(false) && isPositionInside(position) == false){
        return true;
    }else{
        return false;
    }
}

void Cage::drawOn(sf::RenderTarget& targetWindow){

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

bool Cage::isEmpty(){
    return !occupied;
}
