#pragma once
#include "Painter.hpp"
#include "Point.hpp"
#include "Velocity.hpp"

class Ball {
public:
    void setVelocity(const Velocity& velocity);
    Velocity getVelocity() const;
    void draw(Painter& painter) const;
    void setCenter(const Point& center);
    Point getCenter() const;
    double getRadius() const;
    double getMass() const;
private:
    Velocity b_velocity;  // скорость
    Point b_center;       // центр шара
    double b_radius;      // радиус
    double b_mass;        // масса
};
