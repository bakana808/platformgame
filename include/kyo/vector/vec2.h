
#pragma once

#define _USE_MATH_DEFINES

#include "kyo/common.h"
#include <SFML/Graphics.hpp>
#include <math.h>
#include <iostream>
#include <string>


/**
 * @brief A 2D vector with additional math functions.
 *
 */
class vec2: public sf::Vector2f {
public:

    static const vec2 ZERO, LEFT, RIGHT, UP, DOWN;

    static float distance(const vec2& a, const vec2& b);

    vec2(): sf::Vector2f() {}

    vec2(float x, float y): sf::Vector2f(x, y) {}

    vec2(const sf::Vector2f& v): sf::Vector2f(v.x, v.y) {
        // std::cout << "converting vector2f to vec2" << std::endl;
        // std::cout << "x = " << x << ", y = " << y << std::endl;
        // this->x = v.x;
        // this->y = v.y;
    }

    /**
     * @brief Returns the angle of the given vector (in degrees)
     * The range of the angle will be [0, 360)
     *
     * @param v the vector
     * @return float the angle of the vector
     */
    float inline heading(float min = 0.f, float max = 360.f) {

        float angle = (heading_rad() * 180 / M_PI);

        if(angle < min) angle += 360;
        if(angle > max) angle -= 360;

        return angle;
    }

    float heading_rad() {

        return atan2f(x, y);
    }

    /**
     * @brief Returns the dot product of this vector and another vector.
     *
     * @param other
     * @return float
     */
    float dot(const vec2& other) const {

        return (x * other.x) + (y * other.y);
    }

    /**
     * @brief Returns the magnitude or length of a vector.
     *
     * @return float
     */
    float magnitude() {

        return sqrtf(this->dot(*this));
    }

    vec2 normalize() {

        float mag = this->magnitude();

        if(fabs(mag) < std::numeric_limits<float>::epsilon()) {
            return {0, 0};
        } else {
            return {x / mag, y / mag};
        }
    }

    /**
     * @brief Convert this vector into a string.
     *
     * @return std::string
     */
    operator std::string() const;

    /**
     * @brief Negate this vector.
     *
     * @return vec2
     */
    vec2 operator-() const { return vec2(-x, -y); }

    /**
     * @brief Returns this vector scaled by a scalar.
     *
     * @param c
     * @return vec2
     */
    vec2 operator*(const float& c) const {

        return vec2(x * c, y * c);
    }

    float operator*(const vec2& other) const {

        return this->dot(other);
    }

    friend vec2 operator+(const vec2& lhs, const vec2& rhs) {

        return vec2(lhs.x + rhs.x, lhs.y + rhs.y);
    }

    friend vec2 operator+(const vec2& lhs, const sf::Vector2f& rhs) {

        return vec2(lhs.x + rhs.x, lhs.y + rhs.y);
    }

    friend vec2 operator+(const sf::Vector2f& lhs, const vec2& rhs) {

        return rhs + lhs;
    }

    friend vec2 operator-(const vec2& rhs) {

        return vec2(-rhs.x, -rhs.y);
    }

    friend vec2 operator-(const vec2& lhs, const vec2& rhs) {

        return vec2(lhs.x - rhs.x, lhs.y - rhs.y);
    }

    friend vec2 operator-(const sf::Vector2f& lhs, const vec2& rhs) {

        return vec2(lhs.x - rhs.x, lhs.y - rhs.y);
    }

    friend vec2 operator-(const vec2& lhs, const sf::Vector2f& rhs) {

        return vec2(lhs.x - rhs.x, lhs.y - rhs.y);
    }

    vec2& operator=(const sf::Vector2f& rhs) {

        x = rhs.x;
        y = rhs.y;

        return *this;
    }

    vec2& operator+=(const vec2& rhs) {

        x = x + rhs.x;
        y = y + rhs.y;

        return *this;
    }

    vec2& operator-=(const vec2& rhs) {

        x = x - rhs.x;
        y = y - rhs.y;

        return *this;
    }

    bool operator==(const vec2& other) const {

        return x == other.x and y == other.y;
    }

    bool operator<(const vec2& other) const {

        return x < other.x and y < other.y;
    }
};
