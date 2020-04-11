
#pragma once

#include "vector/vec2.h"

#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>

#define PRINT(x) std::cout << x << std::endl

#define STR(x) std::to_string(x)

using vec2i = sf::Vector2i;
using std::string;


float lerp(float, float, float);
vec2 lerp(vec2, vec2, float);

