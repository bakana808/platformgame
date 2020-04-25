
#pragma once

#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>

#define PRINT(x) std::cout << x << std::endl
#define ROUND2(x) ((int)(x * 100)) / 100.f
#define STR(x) std::to_string(x)

using vec2i = sf::Vector2i;
using std::string;

class vec2;

float lerp(float, float, float);
vec2 lerp(vec2, vec2, float);

namespace game {

    /**
     * @brief Round a float to a specified amount of decimals.
     *
     * @param n
     * @param decimals
     * @return float
     */
    float round(float n, int decimals = 2);

    std::string round_str(float n, int decimals = 2);
}
