
#pragma once

#include <cmath>
#include <vector>

#include "common.h"
#include "platform.h"
#include "entity.h"

using std::vector;


class Player: public CompositeEntity {
public:

    /**
     * @brief Represents what type of surface the player is contacting.
     */
    enum CollisionType { NONE, FLOOR, WALL, CEILING };

    /**
     * @brief Represents a packet of info retrieved from collision tests.
     */
    struct CollisionInfo {
        // true if the foot hitbox is intersecting a platform
        bool can_jump;
        // contains the type of surface the body hitbox is intersecting
        CollisionType type;

        PlatformType plat_type;

        // if intersecting a platform, is the unit normal vector of it
        vec2 normal;
        // if intersecting a platform, is the angle of the normal
        float angle;
        // if intersecting a platform, is the length of overlap
        float magnitude;
    };

private:

    vec2 vel;

    sf::RectangleShape box;
    sf::RectangleShape box_g;
    sf::ConvexShape tri;

    sf::CircleShape body_hb;
    sf::RectangleShape foot_hb;

    sf::Font font;
    sf::Text l_pos;
    sf::Text l_vel;
    sf::Text l_plat;

    bool r_pressed = 0;
    bool l_pressed = 0;

    bool stasis = 1;

    float jump_timer = 0.f; // if > 0, do not check floor collisions
    float unground_timer = 0.f;

    bool can_jump = false;
    bool is_grounded = false;
    bool is_spinning = false;
    int num_dashes = 1; // amount of dashes that can be used in the air

    sf::View& view;

    float view_zoom = 1.f;

    float ghost_alpha = 0;

    void show_afterimage() {

        box_g.setPosition(box.getPosition());
        box_g.setRotation(box.getRotation());
        ghost_alpha = 100;
        box_g.setFillColor({255, 255, 255, ghost_alpha});
    }

    void update_afterimage(float delta) {

        auto color = box_g.getFillColor();
        if(ghost_alpha > 0) {
            ghost_alpha = fmax(0, ghost_alpha - delta * 500);
            box_g.setFillColor({255, 255, 255, (int)ghost_alpha});
        }
    }

    vector<Platform>* lines = nullptr;

    void test_collision(vector<CollisionInfo>&);

public:

    Player(sf::View& view)
    : view(view)
    , box({64, 64})
    , box_g({64, 64})
    , body_hb(32)
    , foot_hb({16, 16}) {

        if(!font.loadFromFile("FiraCode-VF.ttf")) {
            PRINT("unable to load font");
        }

        l_pos.setFont(font);
        l_pos.setCharacterSize(14);
        l_pos.setColor(sf::Color::White);
        l_pos.setOrigin({600, +320});

        l_vel.setFont(font);
        l_vel.setCharacterSize(14);
        l_vel.setColor(sf::Color::Green);
        l_vel.setOrigin({600, +320 - 16});

        l_plat.setFont(font);
        l_plat.setCharacterSize(14);
        l_plat.setColor(sf::Color::White);
        l_plat.setOrigin({600, +320 - 64});

        tri.setPointCount(3);
        tri.setPoint(0, {0, 0});
        tri.setPoint(1, {64, 0});
        tri.setPoint(2, {0, 64});
        tri.setOrigin({32, 32});
        tri.setFillColor({150, 150, 150});

        box.setOrigin({32, 32});
        box_g.setOrigin({32, 32});
        box_g.setFillColor({255, 255, 255, 0});

        body_hb.setFillColor(sf::Color::Transparent);
        body_hb.setOutlineColor(sf::Color::Red);
        body_hb.setOutlineThickness(2.0f);
        body_hb.setOrigin({32, 32});

        foot_hb.setFillColor(sf::Color::Transparent);
        foot_hb.setOutlineColor(sf::Color::Red);
        foot_hb.setOutlineThickness(2.0f);
        foot_hb.setOrigin({8, 8 - 40});

        add_child(box);
        add_child(tri);
        add_child(body_hb);
        add_child(foot_hb);
        add_child_free(box_g);
        add_child(l_pos);
        add_child(l_vel);
        add_child(l_plat);
    }

    void update_lines(vector<Platform>* lines) {

        this->lines = lines;
    }

    void update(float delta);

    void key_press(sf::Keyboard::Key key);

    void key_hold(sf::Keyboard::Key key);

    void key_release(sf::Keyboard::Key key);

    /**
     * @brief Set the player's position to (0, 0).
     */
    void respawn(void);
};