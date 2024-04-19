#include <Env/CircularBody.hpp>
#include <Utility/Vec2d.hpp>
#include <Utility/Utility.hpp>


    //not used anymore since 3.1
/*
        CircularBody::CircularBody(const Vec2d& p, double r)
        :position(p), radius(r){}


        Vec2d CircularBody::getCenter()const{
             return position;
        }

        double CircularBody::getRadius()const{
            return radius;
        }
*/

        CircularBody::CircularBody(){};


        bool CircularBody::isColliding(const CircularBody& other)const{
            return *this | other;
        }

        bool CircularBody::isPointInside(const Vec2d& point) const {
            return *this > point;
        }

        bool operator|(const CircularBody& object1, const CircularBody& object2){
            Vec2d distance(object1.getCenter() -object2.getCenter());            // vector between centers of circular objects
            return object1.getRadius() + object2.getRadius() > distance.length();
        }

        //3.1 -> not possible anymore to construct a CircularBody here (abstract class)
        /*
        bool operator>(const CircularBody& object1, const Vec2d& point){
            CircularBody circlePoint(point, 0.0);           //the point is recreated as a circular body with radius 0
            return  object1 | circlePoint;                  //so the operator | can be used
        }
*/
        bool operator>(const CircularBody& object1, const Vec2d& point){
            Vec2d distance(object1.getCenter() - point);
                return  object1.getRadius() > distance.length();
        }

       void CircularBody::drawOn(sf::RenderTarget& target){
           auto circle(buildCircle(getCenter(), getRadius(), sf::Color(20,150,20,30)));
           target.draw(circle);
       }
