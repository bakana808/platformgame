
#pragma once

#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>

#define WIDTH 1280
#define HEIGHT 720

#ifdef DEBUG
    #define PRINT(x) std::cout << x << std::endl
#else
    #define PRINT(x)
#endif

#define ROUND2(x) ((int)(x * 100)) / 100.f
#define STR(x) std::to_string(x)

typedef std::string string;
typedef sf::Vector2i vec2i;
typedef sf::Keyboard Keyboard;
typedef Keyboard::Key Key;

// linear interpolation functions (unused)
class vec2;

float lerp(float, float, float);
vec2 lerp(vec2, vec2, float);

/**
 * @brief Cordial directions for general use.
 *
 */
enum Direction { NONE, LEFT, RIGHT, UP, DOWN };

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

    string demangle(const char *name);
}
