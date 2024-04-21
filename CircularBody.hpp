/*
 *  Glycolysis inhibition 2024
 *  @authors: 
 */
#include <Utility/Vec2d.hpp>
#include <SFML/Graphics.hpp>
#pragma once

class CircularBody{
public:

    /*!
    * @brief Constructor
    */
    //CircularBody(const Vec2d& p, double r);
    CircularBody(); //constructuer par default since it is an abstract class

    /*!
    * @brief Getters
    */
    virtual Vec2d getCenter() const = 0;
    virtual double getRadius() const = 0;

    /*!
    * @brief checks whether two bodies are colliding
    *
    * @return true if they are colliding, false otherwise
    */
    bool isColliding(const CircularBody& other) const;

    /*!
    * @brief checks whether a point is inside of an circular body
    *
    * @return true if point is inside
    */
    bool isPointInside(const Vec2d& point) const;

    /*!
    * @brief drawOn function for the circle or the circular body in debug mode
    */
    void drawOn(sf::RenderTarget& target);


private:
    // no attributs since part 3.1 -> abstract class
        //Vec2d position;
        //double radius;

};

    /*!
    * @brief operator definition: |
    *
    * @return true if two circular bodies are colliding
    */
    bool operator|(const CircularBody& object1, const CircularBody& object2);

    /*!
    * @brief operator definition: >
    *
    * @return true if the point is inside the circular body
    */
    bool operator>(const CircularBody& object1, const Vec2d& point);
