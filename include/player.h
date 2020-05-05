
#pragma once

#include <cmath>
#include <vector>
#include <map>
#include <set>

#include "common.h"
#include "platform.h"
#include "entity.h"
#include "particle.h"

#define P_WALK_MAX_VEL 800
#define P_WALK_ACCEL 5000
#define P_WALK_DECEL 6000
#define P_GRAV_MAX 1500
#define P_GRAV_ACCEL 5000
#define P_JUMP_VEL 1000
#define P_DASH_VEL 1500
#define P_MAX_DASHES 1
#define P_BOUNCE_DAMP 1.0 /* perc energy conserved after a bounce */

#define P_STASIS_RVEL 500

#define P_COLOR_NORMAL {255, 255, 255}
#define P_COLOR_NODASH {150, 150, 150}

#define P_KEY_RESET Key::R
#define P_KEY_LEFT Key::A
#define P_KEY_RIGHT Key::D
#define P_KEY_JUMP Key::I
#define P_KEY_DASH Key::U

using std::vector;

typedef sf::Keyboard Keyboard;
typedef Keyboard::Key Key;


class Level;
class LevelRegion;


class Player: public CompositeEntity {
public:

    /**
     * @brief Represents what type of surface the player is contacting.
     */
    enum SurfaceType { NONE, FLOOR, WALL, CEILING };

    /**
     * @brief Represents a packet of info retrieved from collision tests.
     */
    struct CollisionInfo {
        // true if the foot hitbox is intersecting a platform
        bool b_can_jump;

        SurfaceType surface;

        Platform* platform; // the platform that was touched

        // if intersecting a platform, is the unit normal vector of it
        vec2 normal;
        // if intersecting a platform, is the angle of the normal
        float angle;
        // if intersecting a platform, is the length of overlap
        float magnitude;

        bool operator< (const CollisionInfo& other) const {

            return surface < other.surface;
        }
    };

private:

    vec2 vel;

    sf::RectangleShape box;
    sf::RectangleShape box_g;
    sf::ConvexShape tri;

    sf::CircleShape* body_hb;
    sf::RectangleShape foot_hb;

    sf::Font font;
    sf::Text l_pos;
    sf::Text l_vel;
    sf::Text l_plat;
    sf::Text l_region;

    bool r_pressed = 0;
    bool l_pressed = 0;

    bool stasis = 1;

    float jump_timer = 0.f; // if > 0, do not check floor collisions
    float unground_timer = 0.f;

    bool b_can_jump = false;
    bool is_grounded = false;
    bool b_spinning = false;
    int num_dashes = 1; // amount of dashes that can be used in the air

    LevelRegion* region = NULL;

    sf::View& view;
    sf::View& hud;

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

    Level* level = nullptr;

    typedef std::map<SurfaceType, vector<CollisionInfo>> CollisionMap;

    typedef std::set<CollisionInfo> CollisionSet;

    /**
     * @brief Tests collisions of the body and feet hitbox against all
     * platforms (via the Player::lines pointer), and stores the results in
     * a vector of CollisionInfos.
     *
     */
    CollisionSet* test_collisions(void);

public:

    Player(sf::View& view, sf::View& hud);

    ~Player() {

        delete region;
        delete body_hb;
    }

    void set_level(Level& level) {

        this->level = &level;
    }

    /**
     * @brief Set the color of this Player.
     *
     * @param color
     */
    void set_color(sf::Color color);

    /**
     * @brief Called every frame. Updates logic for this Player.
     *
     * @param delta
     */
    void update(float delta);

    /**
     * @brief Called when the user presses a key.
     *
     * @param key
     */
    void key_press(Key key);

    /**
     * @brief Called every frame that the user holds down a key.
     *
     * @param key
     */
    void key_hold(Key key);

    /**
     * @brief Called when the user releases a key.
     *
     * @param key
     */
    void key_release(Key key);

    /**
     * @brief Respawn player at checkpoint according to current position.
     */
    void respawn();

    //=========================================================================
    // PLAYER INFO GETTERS
    //=========================================================================

    const vec2& get_vel() { return vel; }

    bool is_spinning() { return b_spinning; }

    int get_num_dashes() { return num_dashes; }

    bool can_jump() { return b_can_jump; }

    sf::CircleShape* get_body() { return body_hb; }

    LevelRegion* get_region() { return region; }

    //=========================================================================
    // PLAYER ACTIONS
    //=========================================================================

    /**
     * @brief Perform a jump.
     *
     */
    void do_jump();

    /**
     * @brief Perform a dash in the specified direction.
     *
     * @param dir
     */
    void do_dash(const vec2& dir);

    /**
     * @brief Move in the specified direction.
     *
     * Providing UP or DOWN will not do anything.
     *
     * @param dir
     * @param delta
     */
    void do_move(Direction dir, float delta);

};
