#ifndef CAGE_HPP
#define CAGE_HPP
#include <Utility/Vec2d.hpp>
#include "SFML/Graphics.hpp"
#include "Drawable.hpp"
#pragma once


typedef std::pair <Vec2d, Vec2d> Wall; //bottom right corner, top left corner
typedef std::vector<Wall> Walls;

class Cage: public Drawable{

    Vec2d position;
    double width;
    double height;
    double wallWidth;
    Walls walls;               //0 = top, 1 = right
                               //2 = bottom, 3 = left


    bool occupied;  //true if there is an animal in the cage


public:
    /*!
    * @brief Constructor of a Cage, initialized with position, width, height, wallWidth provided by default
    * walls are constructed in the body of the constructor
    */
    Cage(Vec2d postion, double width = 300.0, double height = 300.0, double wallWidth = 10.0);

    /*!
    * @brief Destructor
    */
   virtual ~Cage()=default;

    /*!
    * @brief Copy constructer by default
    */
    Cage(const Cage&)=default;

    /*!
    * @brief Getters
    */
    Vec2d getCenter();
    double getWidth();
    double getHeight();
    double getWallWidth();

    Wall getTop();
    Wall getRight();
    Wall getBottom();
    Wall getLeft();

    /*!
    * @brief getting the coordinate of the inner wall of the Cage (if intern = true)
    *        or getting the coordinate of the outer wall (if intern = false)
    *
    * @return double with x or y value of the wall
    */
    double getLeftLimit(bool intern = false);
    double getRightLimit(bool intern = false);
    double getTopLimit(bool intern = false);
    double getBottomLimit(bool intern = false);

    /*!
    * @brief check whether a object (point per default) is inside of a Cage (walls excuded)
    *
    * @return true if point is inside
    */
    bool isPositionInside(const Vec2d& position, double radius =0);

    /*!
    * @brief check whether a point is on the wall of the Cage
    *
    * @return true if point is on the wall
    */
    bool isPositionOnWall(const Vec2d& position);

    /*!
    * @brief sets the attibut occupied = true (meaning : cage occupied by an animal)
    */
    void addOccupant();

    /*!
    * @brief sets the attibut occupied = false (meaning : cage not occupied by an animal)
    */
    void reset();

    /*!
    * @brief checks whether a cage is empty (no animal inside)
    *
    * @return ture if empty
    */
    bool isEmpty();

    /*!
    * @brief Draw a cage
    */
    void drawOn(sf::RenderTarget& targetWindow) override;


    };

#endif // CAGE_HPP
