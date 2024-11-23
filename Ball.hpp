#pragma once
#include "Painter.hpp"
#include "Point.hpp"
#include "Velocity.hpp"
#include <fstream>

class Ball {
public:
    void setVelocity(const Velocity& velocity);
    Velocity getVelocity() const;
    void draw(Painter& painter) const;
    void setCenter(const Point& center);
    Point getCenter() const;
    double getRadius() const;
    double getMass() const;
    void setColor(double red, double green, double blue);
    void setColor(Color& color);
    Color getColor() const;
    bool getCollidable() const;

    // конструктор, в который передается один аргумент 
    // типа дабл, считает, что это радиус и инициализаруется этим значением
    Ball(double b_radius, bool b_collidable) : b_radius(b_radius), b_collidable(b_collidable) {}
    Ball() = default;

private:
    Velocity b_velocity;    // = Velocity{0.0, 0.0}
    Point b_center = Point{0.0, 0.0};
    const double b_radius = 0.0;
    Color b_color = Color{255.0, 255.0, 255.0};
    const bool b_collidable = true;
};