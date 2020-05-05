
#include "collision.h"


void push_normals(vector<vec2>* normals, vector<vec2> vertices) {

    if(vertices.size() <= 1) return;

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

        normals->push_back(norm.normalize());
    }
}


Projection project(vec2 normal, vector<vec2> vertices) {

    float min = normal.dot(vertices[0]);
    float max = min;

    for(int i = 1; i < vertices.size(); i++) {

        float proj = normal.dot(vertices[i]);

        if(proj < min) {
            min = proj;
        }
        else if(proj > max) {
            max = proj;
        }
    }

    return {min, max};
}


Projection project(vec2 normal, vec2 center, float radius) {

    float proj = normal.dot(center);

    return {proj - radius, proj + radius};
}

Collision get_collision(vector<vec2> vertices_a, vector<vec2> vertices_b) {

    vector<vec2> normals;

    // PRINT("collecting normals of A");
    push_normals(&normals, vertices_a);

    // PRINT("collecting normals of B");
    push_normals(&normals, vertices_b);

    float smallest_overlap = -INFINITY;
    vec2 smallest_axis;

    // PRINT(normals.size() << " normals");
    // PRINT("collecting Projections");
    for(vec2 normal: normals) {

        // PRINT("{" << normal.x << ", " << normal.y << "}");
        // PRINT(" - getting 1st Projection");
        Projection p1 = project(normal, vertices_a);
        // PRINT(" - getting 2nd Projection");
        Projection p2 = project(normal, vertices_b);
        // PRINT("{" << p1.min << ", " << p1.max << "} <=> {" << p2.min << ", " << p2.max << "}");

        if(!p1.overlaps(p2)) {
            // PRINT(" - no overlap");
            return Collision();
        }
        else {
            // PRINT(" - found overlap");
            float overlap = p1.get_overlap(p2);

            if(fabs(overlap) < fabs(smallest_overlap)) {

                smallest_overlap = overlap;
                smallest_axis = normal;
            }
        }
    }

    // PRINT("done");

    MTV mtv = {smallest_axis, smallest_overlap};
    return Collision(mtv);
}
Collision get_collision(const sf::Shape& a, const sf::Shape& b) {

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

Collision get_collision(const sf::Shape& a, const sf::CircleShape& b) {

    // PRINT("preparing vertices of A");

    vector<vec2> verts_a = {
        a.getTransform().transformPoint(a.getPoint(0)),
        a.getTransform().transformPoint(a.getPoint(1)),
        a.getTransform().transformPoint(a.getPoint(2)),
        a.getTransform().transformPoint(a.getPoint(3))
    };

    // PRINT("preparing vertices of B");

    const vec2 b_center = vec2(b.getPosition());

    // PRINT("finding circle -> shape axis");

    // get the vector of the shortest line from B to a vertice on A
    // ------------------------------------------------------------

    float min = INFINITY;
    vec2 min_axis;

    for(vec2 vert: verts_a) {

        vec2 axis = vert - b_center;
        float mag_sq = axis.dot(axis);

        if(mag_sq < min) {
            min = mag_sq;
            min_axis = min_axis;
        }
    }

    // PRINT("finding other axes");

    // prepare axes

    vector<vec2> normals;
    push_normals(&normals, verts_a);
    normals.push_back(min_axis.normalize());

    float smallest_overlap = INFINITY;
    vec2 smallest_axis;

    for(vec2 normal: normals) {

        Projection p1 = project(normal, verts_a);
        Projection p2 = project(normal, b_center, b.getRadius());

        if(!p1.overlaps(p2)) {

            return Collision();
        }
        else {
            // PRINT(" - found overlap");
            float overlap = p1.get_overlap(p2);

            if(fabs(overlap) < fabs(smallest_overlap)) {

                smallest_overlap = overlap;
                smallest_axis = normal;
            }
        }
    }

    MTV mtv = {smallest_axis, smallest_overlap};
    return Collision(mtv);
}