#ifndef CAGE_HPP
#define CAGE_HPP
#include <Utility/Vec2d.hpp>
#include "SFML/Graphics.hpp"
#pragma once


typedef std::pair <Vec2d, Vec2d> Wall; //bottom right corner, top left corner
typedef std::vector<Wall> Walls;

class Cage{

    Vec2d position;
    double width;
    double height;
    double wallWidth;
    Walls walls;
    Wall top;
    Wall right;
    Wall bottom;
    Wall left;

    bool occupied;


public:
    /*!
    * @brief Constructor of a Cage, initialized with position, width, height, wallWidth provided by default
    * walls are constructed in the body of the constructor
    */
    Cage(Vec2d postion, double width = 300.0, double height = 300.0, double wallWidth = 10.0);

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
    * @brief getting the coord of the inner wall of the Cage (if intern = true) or getting the coord of the outer wall (if intern = false)
    *
    * @return double with x or y value of the wall
    */
    double getLeftLimit(bool intern = false);
    double getRightLimit(bool intern = false);
    double getTopLimit(bool intern = false);
    double getBottomLimit(bool intern = false);

    /*!
    * @brief check whether a point is inside of a Cage (walls excuded)
    *
    * @return true if point is inside
    */
    bool isPositionInside(const Vec2d& position);

    /*!
    * @brief check whether a point is on the wall of the Cage
    *
    * @return true if point is on the wall
    */
    bool isPositionOnWall(const Vec2d& position);

    /*!
    * @brief Destructor
    */
    ~Cage(){}

    /*!
    * @brief Draw a cage
    */
    void drawOn(sf::RenderTarget& targetWindow);

    void addOccupant();
    void reset();
    bool isEmpty();

    };

#endif // CAGE_HPP
