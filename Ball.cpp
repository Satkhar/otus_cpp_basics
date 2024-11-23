#include "Ball.hpp"
#include <cmath>

/**
 * Задает скорость объекта
 * @param velocity новое значение скорости
 */
void Ball::setVelocity(const Velocity& velocity) {
    //  [x] TODO: место для доработки
    b_velocity = velocity.vector();
}

/**
 * @return скорость объекта
 */
Velocity Ball::getVelocity() const {
    // [x] TODO: место для доработки
    return b_velocity;
}

/**
 * @brief Выполняет отрисовку объекта
 * @details объект Ball абстрагирован от конкретного
 * способа отображения пикселей на экране. Он "знаком"
 * лишь с интерфейсом, который предоставляет Painter
 * Рисование выполняется путем вызова painter.draw(...)
 * @param painter контекст отрисовки
 */
void Ball::draw(Painter& painter) const {
    // [x] TODO: место для доработки
    painter.draw(b_center,b_radius,b_color);
}

/**
 * Задает координаты центра объекта
 * @param center новый центр объекта
 */
void Ball::setCenter(const Point& center) {
    // [x] TODO: место для доработки
    b_center = center;
}

/**
 * @return центр объекта
 */
Point Ball::getCenter() const {
    // [x] TODO: место для доработки
    return b_center;
}

/**
 * @brief Возвращает радиус объекта
 * @details обратите внимание, что метод setRadius()
 * не требуется
 */
double Ball::getRadius() const {
    // [x] TODO: место для доработки
    return b_radius;
}

/**
 * @brief Возвращает массу объекта
 * @details В нашем приложении считаем, что все шары
 * состоят из одинакового материала с фиксированной
 * плотностью. В этом случае масса в условных единицах
 * эквивалентна объему: PI * radius^3 * 4. / 3.
 */
double Ball::getMass() const {
    // [x] TODO: место для доработки
    return 3.1428*(b_radius*b_radius*b_radius)*4./3.;
}

/// @brief Устанавливает цвет шара в формате RGB
/// @param red значение красного
/// @param green значение зеленого
/// @param blue значение синего
void Ball::setColor(double red, double green, double blue)
{
    b_color = Color{red, green, blue};
}

void Ball::setColor(Color& input_color)
{
    b_color = Color{input_color};
}

/// @brief Функция для чтения цвет шара
/// @return Возвращает цвет шара
Color Ball::getColor() const
{
    return b_color;
}

/// @brief функция для получения параметра обработки столкновений
/// @return возвращает true если надо обрабатывать столкновения
bool Ball::getCollidable() const
{
    return b_collidable;
}
