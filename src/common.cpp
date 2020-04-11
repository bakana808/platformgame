
#include "common.h"


inline float lerp(float a, float b, float t) {

    return a + t * (b - a);
}

vec2 lerp(vec2 a, vec2 b, float t) {

    return {lerp(a.x, b.x, t), lerp(a.y, b.y, t)};
}