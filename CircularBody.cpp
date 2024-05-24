#include <Env/CircularBody.hpp>
#include <Utility/Vec2d.hpp>
#include <Utility/Utility.hpp>



bool CircularBody::isColliding(const CircularBody& other)const{
    return *this | other;
}

bool CircularBody::isPointInside(const Vec2d& point) const {
    return *this > point;
}

bool operator|(const CircularBody& object1, const CircularBody& object2){
    Vec2d distance(object1.getCenter() - object2.getCenter());            // vector between centers of circular objects
    return object1.getRadius() + object2.getRadius() > distance.length();
}


bool operator>(const CircularBody& object1, const Vec2d& point){
    Vec2d distance(object1.getCenter() - point);
        return  object1.getRadius() > distance.length();
}

void CircularBody::drawOn(sf::RenderTarget& target) const{
   auto circle(buildCircle(getCenter(), getRadius(), sf::Color(20,150,20,30)));
   target.draw(circle);
}
