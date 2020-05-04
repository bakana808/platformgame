
#include "common.h"
#include "vector/vec2.h"
#include <math.h>
#include <sstream>


inline float lerp(float a, float b, float t) {

    return a + t * (b - a);
}

vec2 lerp(vec2 a, vec2 b, float t) {

    return {lerp(a.x, b.x, t), lerp(a.y, b.y, t)};
}

namespace game {

    float round(float n, int decimals) {

        int f = (int)pow(10, f);

        return roundf(n * f) / f;
    }

    std::string round_str(float n, int decimals) {

        std::ostringstream ss;
        ss.precision(decimals);

        ss << std::fixed << n;
        return ss.str();
    }
}
