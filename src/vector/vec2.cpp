
#include "common.h"
#include "vector/vec2.h"
#include <iostream>


vec2 const vec2::ZERO  = vec2( 0,  0);
vec2 const vec2::UP    = vec2( 0,  1);
vec2 const vec2::DOWN  = vec2( 0, -1);
vec2 const vec2::LEFT  = vec2(-1,  0);
vec2 const vec2::RIGHT = vec2( 1,  0);


float vec2::distance(const vec2& a, const vec2& b) {
    // try {

        // PRINT("calculating distance");

        // PRINT("a={" << a.x << ", " << a.y << "} b={" << b.x << ", " << b.y << "}");

    return (b - a).magnitude();

        // PRINT("done");

    // }
    // catch( const std::exception& e) {
        // std::cerr << e.what() << std::endl;
    // }
}