
#pragma once

#include "kyo/common.h"
#include "kyo/vector/vec2.h"

#define _USE_MATH_DEFINES
#include <vector>
#include <cmath>
#include <limits>

using std::vector;


/**
 * @brief Represents a region on a given axis.
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
// struct MTV {

//     // normal vector of the collision surface
//     vec2 axis;

//     // minimum distance to resolve the collision
//     float mt_length;

//     // here, you can translate one of the shapes by (normal * mt_length)
//     // to move the shape out of the collision.
// };


/**
 * @brief Holds information on the collision between two objects.
 *
 * The axis and magnitude that is stored is also known as the
 * "minimum translation vector".
 *
 * Translating one of the intersecting objects by the axis scaled by the
 * magnitude will resolve the intersection.
 *
 * This translation is gauranteed to be the shortest vector needed to
 * resolve the intersection based on the collision check.
 *
 */
class Collision {
private:

    bool b_has_collided;

    vec2 *axis; // the axis where the shapes collided

    float *magnitude; // the magnitude of intersection

public:

    Collision() : b_has_collided(false), axis(NULL), magnitude(NULL) {}

    Collision(const vec2& axis, float magnitude)
    : b_has_collided(true) {

        this->axis = new vec2(axis);
        this->magnitude = new float(magnitude);
    }

    bool has_collided(void) { return b_has_collided; }

    vec2* get_axis(void) {

        if(axis) return axis;

        throw 1;
    }

    float* get_magnitude(void) {

        if(magnitude) return magnitude;

        throw 1;
    }

};


/**
 * @brief Converts a vector of vertices to test axes and appends them
 * to the given pointer to a vector of axes.
 *
 * This implementation uses the normals of all edges of the shape as the
 * test axes.
 *
 * @param normals
 * @param vertices
 */
void push_normals(vector<vec2>* axes, vector<vec2> vertices);


/**
 * @brief Project a shape onto an axis.
 *
 * @param axis the axis to test
 * @param vertices the vertices of the shape
 * @return Projection
 */
Projection project_convex(vec2 axis, vector<vec2> vertices);

/**
 * @brief Project a circle onto an axis.
 *
 * @param axis the axis to test
 * @param center the center of the circle
 * @param radius the radius of the circle
 * @return Projection
 */
Projection project_circle(vec2 normal, vec2 center, float radius);

/**
 * @brief Check the collision between two convex shapes.
 *
 * @param vertices_a the vertices of shape A
 * @param vertices_b the vertices of shape B
 * @return Collision the collision test results
 */
Collision get_collision(vector<vec2> vertices_a, vector<vec2> vertices_b);

/**
 * @brief Check the collision between a convex shape and a circle.
 *
 * This implementation is a bit different than the convex-convex test.
 *
 * @param vertices_a the vertices of shape A
 * @param center_b   the center position of shape B
 * @param radius_b   the radius of shape B
 * @return Collision the collision test results
 */
Collision get_collision(vector<vec2> vertices_a, const vec2& center_b, float radius_b);

Collision get_collision(const sf::Shape& a, const sf::Shape& b);

Collision get_collision(const sf::Shape& a, const sf::CircleShape& b);