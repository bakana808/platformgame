
#include "common.h"
#include <optional>
#include <vector>
#include <cmath>

using std::vector;



inline float dot_product(vec2 a, vec2 b) {

    return a.x * b.x + a.y * b.y;
}


inline float distance(vec2 a) {

    return sqrt(dot_product(a, a));
}


vec2 normalize(vec2 a) {

    float dist = distance(a);
    return {a.x / dist, a.y / dist};
}


class projection {
public:
    float min, max;

    bool overlaps(projection b) {
        return !(min > b.max or b.min > max);
    }

    float get_overlap(projection b) {
        if(!overlaps(b)) return 0;

        if(b.max >= min) return b.max - min;
        else return b.min - max;
    }
};

struct mtv {
    vec2 axis;
    float overlap;
};


void push_normals(vector<vec2>* axes, vector<vec2> vertices) {

    for(int i = 0; i < vertices.size(); i++) {


        // current vertex
        vec2 p1 = vertices[i];
        // PRINT("vert => {" << p1.x << ", " << p1.y << "}");

        // next vertex
        vec2 p2 = vertices[(i + 1) % vertices.size()];

        // edge vector p1 - p2
        vec2 edge = p1 - p2;

        // vector normal to (p1 - p2)
        vec2 norm = {-edge.y, edge.x};

        axes->push_back(normalize(norm));
    }
}


projection project(vec2 axis, vector<vec2> vertices) {

    float min = dot_product(axis, vertices[0]);
    float max = min;

    for(int i = 1; i < vertices.size(); i++) {

        float proj = dot_product(axis, vertices[i]);

        if(proj < min) {
            min = proj;
        }
        else if(proj > max) {
            max = proj;
        }
    }

    return {min, max};
}

/**
 * @brief Get the Minimum Translation Vector (MTV) using the
 * Separation Axis Theorem.
 */
std::optional<mtv> get_collision(vector<vec2> vertices_a, vector<vec2> vertices_b) {

    vector<vec2> axes;

    // PRINT("collecting axes of A");
    push_normals(&axes, vertices_a);

    // PRINT("collecting axes of B");
    push_normals(&axes, vertices_b);

    bool has_smallest = 0;
    float smallest_overlap;
    vec2 smallest_axis;

    // PRINT(axes.size() << " axes");
    // PRINT("collecting projections");
    for(vec2 axis: axes) {

        // PRINT("{" << axis.x << ", " << axis.y << "}");
        // PRINT(" - getting 1st projection");
        projection p1 = project(axis, vertices_a);
        // PRINT(" - getting 2nd projection");
        projection p2 = project(axis, vertices_b);
        // PRINT("{" << p1.min << ", " << p1.max << "} <=> {" << p2.min << ", " << p2.max << "}");

        if(!p1.overlaps(p2)) {
            // PRINT(" - no overlap");
            return std::optional<mtv>();
        }
        else {
            // PRINT(" - found overlap");
            float overlap = p1.get_overlap(p2);

            if(!has_smallest or fabs(overlap) < fabs(smallest_overlap)) {

                has_smallest = 1;
                smallest_overlap = overlap;
                smallest_axis = axis;
            }
        }
    }

    // PRINT("done");

    return std::optional<mtv>({smallest_axis, smallest_overlap});
}

std::optional<mtv> get_collision(const sf::Shape& a, const sf::Shape& b) {

    vector<vec2> verts_a = {
        a.getTransform().transformPoint(a.getPoint(0)),
        a.getTransform().transformPoint(a.getPoint(1)),
        a.getTransform().transformPoint(a.getPoint(2)),
        a.getTransform().transformPoint(a.getPoint(3))
    };

    vector<vec2> verts_b = {
        b.getTransform().transformPoint(b.getPoint(0)),
        b.getTransform().transformPoint(b.getPoint(1)),
        b.getTransform().transformPoint(b.getPoint(2)),
        b.getTransform().transformPoint(b.getPoint(3))
    };

    return get_collision(verts_a, verts_b);

}