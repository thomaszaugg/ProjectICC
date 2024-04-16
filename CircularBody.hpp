/*
 *  Glycolysis inhibition 2024
 *  @authors: 
 */
#include <Utility/Vec2d.hpp>
#include <SFML/Graphics.hpp>
#pragma once

class CircularBody{
    public:

    //constructor
    //CircularBody(const Vec2d& p, double r);
    CircularBody(); //constructuer par default

    //returns the center of the circular body
    virtual Vec2d getCenter() const = 0;

    //returns the radius of the circular body
    virtual double getRadius() const = 0;

    //returns true if the two bodies are colliding and false otherwise
    bool isColliding(const CircularBody& other) const;

    //returns true if the point is inside the
    bool isPointInside(const Vec2d& point) const;

    void drawOn(sf::RenderTarget& target);


    private:
        //Vec2d position;
        //double radius;

};

    //returns true if the two objects are colliding
  bool operator|(const CircularBody& object1, const CircularBody& object2);

    //returnes true if the point is inside the object1
  bool operator>(const CircularBody& object1, const Vec2d& point);
