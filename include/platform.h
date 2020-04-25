
#pragma once

#define _USE_MATH_DEFINES
#include <math.h>

#include "common.h"
#include "vector/vec2.h"


enum PlatformType { NORMAL = 0, HAZARD };

class Platform: public sf::Drawable {
private:

    float length;

    sf::RectangleShape line;
    sf::CircleShape f_pt, b_pt; // front/back points

    PlatformType type;

public:

    Platform(const vec2& a,
             const vec2& b,
             float thickness,
             PlatformType type = NORMAL)
             : type(type)
    {
        vec2 diff = b - a;

        length = sqrt((diff.x * diff.x) + (diff.y * diff.y));

        float angle = atan2f(diff.y, diff.x);

        // setPointCount(4);
        // setPoint(0, a + vec2(+sin(angle), -cos(angle)) * thickness);
        // setPoint(1, b + vec2(+sin(angle), -cos(angle)) * thickness);
        // setPoint(2, b + vec2(-sin(angle), +cos(angle)) * thickness);
        // setPoint(3, a + vec2(-sin(angle), +cos(angle)) * thickness);

        float midpt = thickness / 2;

        sf::Color color;
        switch(type) {
        case NORMAL: default:
            color = {200, 200, 200}; break;
        case HAZARD:
            color = {255, 100, 100}; break;
        }

        line.setSize({length, thickness});
        line.setOrigin({0, midpt});
        line.setPosition(a);

        line.setRotation(angle * (180.f / M_PI));
        line.setFillColor(color);

        f_pt.setRadius(midpt);
        f_pt.setPosition(a);
        f_pt.setOrigin({midpt, midpt});
        f_pt.setFillColor(color);

        b_pt.setRadius(midpt);
        b_pt.setPosition(b);
        b_pt.setOrigin({midpt, midpt});
        b_pt.setFillColor(color);
    }

    sf::RectangleShape& get_shape() { return line; }
    const vec2& getPosition() { return static_cast<const vec2&>(line.getPosition()); }

    float get_length(void) { return length; }

    PlatformType get_type(void) { return type; }

    void draw(sf::RenderTarget& target, sf::RenderStates states) const override {

        target.draw(f_pt, states);
        target.draw(b_pt, states);
        target.draw(line, states);
    }
};