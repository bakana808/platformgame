
#include "kyo/collision.h"


void push_normals(vector<vec2>* axes, vector<vec2> vertices) {

    if(vertices.size() <= 1) return;

    for(unsigned int i = 0; i < vertices.size(); i++) {

        // current vertex
        vec2 p1 = vertices[i];
        // PRINT("vert => {" << p1.x << ", " << p1.y << "}");

        // next vertex
        vec2 p2 = vertices[(i + 1) % vertices.size()];

        // edge vector p1 - p2
        vec2 edge = p1 - p2;

        // vector normal to (p1 - p2)
        vec2 norm = {-edge.y, edge.x};

        axes->push_back(norm.normalize());
    }
}


Projection project_convex(vec2 axis, vector<vec2> vertices) {

    float min = axis.dot(vertices[0]);
    float max = min;

    for(unsigned int i = 1; i < vertices.size(); i++) {

        float proj = axis.dot(vertices[i]);

        if(proj < min) {
            min = proj;
        }
        else if(proj > max) {
            max = proj;
        }
    }

    return {min, max};
}


Projection project_circle(vec2 normal, vec2 center, float radius) {

    float proj = normal.dot(center);

    return {proj - radius, proj + radius};
}

Collision get_collision(vector<vec2> vertices_a, vector<vec2> vertices_b) {

    // PRINT("TESTINGi CONVEX-CONVEX COLLISION");

    // use normals of shapes A and B as test axes
    // PRINT("    generating test axes...");

    vector<vec2> axes;
    push_normals(&axes, vertices_a);
    push_normals(&axes, vertices_b);

    // project both shapes onto every axis while also
    // finding the axis with the smallest overlap
    // PRINT("    testing axes...");

    float min_overlap = INFINITY;
    vec2 min_axis;

    for(vec2 axis: axes) {

        Projection p1 = project_convex(axis, vertices_a); // project shape A
        Projection p2 = project_convex(axis, vertices_b); // project shape B

        // NOTE: if one of the projections don't overlap,
        // then the two shapes do not overlap
        if(!p1.overlaps(p2)) {

            return Collision(); // return a "no collision"
        }
        else {

            // keep track of the smallest axis/overlap

            float overlap = p1.get_overlap(p2);

            if(fabs(overlap) < fabs(min_overlap)) {

                min_overlap = overlap;
                min_axis = axis;
            }
        }
    }

    // PRINT("    done");

    // finally return the collision
    Collision col(min_axis, min_overlap);
    return col;
}


Collision get_collision(vector<vec2> vertices_a, const vec2& center_b, float radius_b) {

    // PRINT("TESTING CONVEX-CIRCLE COLLISION");

    vector<vec2> axes;

    // find the shortest line from B to a vertice on A
    // and use this line as a test axis
    // PRINT("    generating test axes (circle)...");

    float dist_b = INFINITY;
    vec2 axis_b;

    for(vec2 vert: vertices_a) {

        vec2 axis = vert - center_b;
        float mag_sq = axis.dot(axis);

        if(mag_sq < dist_b) {
            dist_b = mag_sq;
            axis_b = axis;
        }
    }

    axes.push_back(axis_b.normalize());

    // add normals of A as test axes
    // PRINT("    generating test axes (convex)...");

    push_normals(&axes, vertices_a);

    // project both shapes onto every axis
    // PRINT("    testing axes...");

    float min_overlap = INFINITY;
    vec2 min_axis;

    for(vec2 axis: axes) {

        Projection p1 = project_convex(axis, vertices_a); // project A
        Projection p2 = project_circle(axis, center_b, radius_b); // project B

        if(!p1.overlaps(p2)) {

            return Collision();
        }
        else {
            // PRINT(" - found overlap");
            float overlap = p1.get_overlap(p2);

            if(fabs(overlap) < fabs(min_overlap)) {

                min_overlap = overlap;
                min_axis = axis;
            }
        }
    }

    // PRINT("    done");

    Collision col(min_axis, min_overlap);
    return col;
}

Collision get_collision(const sf::Shape& a, const sf::Shape& b) {

    // PRINT("CONVERTING SHAPES FOR COLLISION TEST");
    // PRINT("    preparing vertices of A");

    vector<vec2> verts_a = {
        a.getTransform().transformPoint(a.getPoint(0)),
        a.getTransform().transformPoint(a.getPoint(1)),
        a.getTransform().transformPoint(a.getPoint(2)),
        a.getTransform().transformPoint(a.getPoint(3))
    };

    // PRINT("    preparing vertices of B");

    vector<vec2> verts_b = {
        b.getTransform().transformPoint(b.getPoint(0)),
        b.getTransform().transformPoint(b.getPoint(1)),
        b.getTransform().transformPoint(b.getPoint(2)),
        b.getTransform().transformPoint(b.getPoint(3))
    };

    return get_collision(verts_a, verts_b);
}


Collision get_collision(const sf::Shape& a, const sf::CircleShape& b) {

    // PRINT("CONVERTING SHAPES FOR COLLISION TEST");
    // PRINT("    preparing vertices of A");

    vector<vec2> verts_a = {
        a.getTransform().transformPoint(a.getPoint(0)),
        a.getTransform().transformPoint(a.getPoint(1)),
        a.getTransform().transformPoint(a.getPoint(2)),
        a.getTransform().transformPoint(a.getPoint(3))
    };

    vec2 pos = b.getPosition();

    // PRINT("    preparing circle B");

    return get_collision(verts_a, pos, b.getRadius());
}