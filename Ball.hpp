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
    void setColor(double red, double green, double blue);
    void setColor(Color& color);
    Color getColor() const;
private:
    Velocity b_velocity;    // = Velocity{0.0, 0.0}
    Point b_center = Point{0.0, 0.0};
    double b_radius = 0.0;
    double b_mass = 0.0;
    Color b_color = Color{255.0, 255.0, 255.0};
};
