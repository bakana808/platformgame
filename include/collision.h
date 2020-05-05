
#pragma once


#include "common.h"
#include "vector/vec2.h"
#include <optional>
#include <vector>

#define _USE_MATH_DEFINES
#include <cmath>
#include <limits>

using std::vector;


/**
 * @brief Represents two points on a given axis.
 *
 * (treated as a one-dimensional line)
 *
 */
class Projection {
public:
    float min, max;

    /**
     * @brief Returns if the given projection overlaps this one.
     *
     * Assumes both projections are on the same axis.
     *
     * @param b
     * @return true if this projection overlaps this one
     * @return false if this projection does not overlap this one
     */
    bool overlaps(Projection b) {
        return !(min > b.max or b.min > max);
    }

    /**
     * @brief Returns the magnitude of overlap.
     *
     * Will return 0 if there is no overlap.
     *
     * @param b
     * @return float the magnitude of overlap.
     */
    float get_overlap(Projection b) {
        if(!overlaps(b)) return 0;

        if(b.max >= min) return b.max - min;
        else return b.min - max;
    }
};


/**
 * @brief The Minimum Translation Vector (MTV).
 *
 * The MTV holds information on the the shortest vector needed to
 * resolve a collision between two objects.
 *
 */
struct MTV {

    // normal vector of the collision surface
    vec2 normal;

    // minimum distance to resolve the collision
    float mt_length;

    // here, you can translate one of the shapes by (normal * mt_length)
    // to move the shape out of the collision.
};


/**
 * @brief Holds information on the collision between two objects (the MTV).
 *
 * Inherits from std::optional to be able to represent no collision.
 *
 */
class Collision: public std::optional<MTV> {
public:

    Collision(): std::optional<MTV>(std::nullopt) {};

    Collision(MTV mtv): std::optional<MTV>(mtv) {};

    inline bool has_collided(void) { return this->has_value(); }

    vec2* get_normal(void) {

        if(has_collided()) {
            return &value().normal;
        } else {
            return nullptr;
        }
    }

    float* get_overlap_len(void) {

        if(has_collided()) {
            return &value().mt_length;
        } else {
            return nullptr;
        }
    }
};


/**
 * @brief Given a reference to a
 *
 * @param normals
 * @param vertices
 */
void push_normals(vector<vec2>* normals, vector<vec2> vertices);


/**
 * @brief Project a shape onto an axis.
 *
 * @param axis the axis to test
 * @param vertices the vertices of the shape
 * @return Projection
 */
Projection project(vec2 normal, vector<vec2> vertices);

/**
 * @brief Project a circle onto an axis.
 *
 * @param axis the axis to test
 * @param center the center of the circle
 * @param radius the radius of the circle
 * @return Projection
 */
Projection project(vec2 normal, vec2 center, float radius);

/**
 * @brief Get the Minimum Translation Vector (MTV) using the
 * Separation Axis Theorem.
 */
Collision get_collision(vector<vec2> vertices_a, vector<vec2> vertices_b);

Collision get_collision(const sf::Shape& a, const sf::Shape& b);

Collision get_collision(const sf::Shape& a, const sf::CircleShape& b);