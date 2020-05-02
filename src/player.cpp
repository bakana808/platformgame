

#include "player.h"
#include "vector/vec2.h"
#include "collision.h"
#include <iostream>
#define _USE_MATH_DEFINES
#include <math.h>


void Player::set_color(sf::Color color) {

    sf::Color darker(color.r * 0.8, color.g * 0.8, color.b * 0.8);

    this->box.setFillColor(color);
    this->tri.setFillColor(darker);
}


void Player::key_press(sf::Keyboard::Key key) {

    //=========================================================================
    // LEFT / RIGHT MOVEMENT
    //=========================================================================

    if(key == sf::Keyboard::D)
        r_pressed = 1;

    if(key == sf::Keyboard::A)
        l_pressed = 1;

    //=========================================================================
    // JUMP
    //=========================================================================

    if(key == sf::Keyboard::I and (stasis or can_jump) and not is_spinning) {
        vel.y = -1000;
        move({0, -1}); // shift player slightly up to avoid ground collisions
        jump_timer = 0.2f;
        stasis = false;

        for(int i = -32; i <= 32; i += 16) {

            Particle* part = new Particle(this);
            part->handle->setPosition(this->get_pos() + vec2(i, 40));
            this->add_child_free((Entity*)part);

        }
        PRINT("jump");
    }

    if(key == sf::Keyboard::U) {

        is_spinning = true;

        // set_color({255, 255, 150});

        using key = sf::Keyboard;

        float x = 0, y = 0;

        if(key::isKeyPressed(key::D)) {
            x = 1;
        }
        else if(key::isKeyPressed(key::A)) {
            x = -1;
        }

        if(key::isKeyPressed(key::S)) {
            y = 1;
        }
        else if(key::isKeyPressed(key::W)) {
            y = -1;
        }

        if(num_dashes > 0 and (x != 0 or y != 0)) {

            if(can_jump) move({0, -1});

            num_dashes--;

            vec2 dir = vec2(x, y).normalize();
            this->vel = dir * 1500;
            show_afterimage();

            if(num_dashes <= 0) {
                set_color({150, 150, 150});
            }

            // if(can_jump)
                // this->pos.y -= 1;
        }
    }
}

void Player::key_release(sf::Keyboard::Key key) {

    if(key == sf::Keyboard::D)
        r_pressed = 0;

    if(key == sf::Keyboard::A)
        l_pressed = 0;

    if(key == sf::Keyboard::U) {
        PRINT("unspinning");
        is_spinning = false;
    }
}

Player::CollisionSet* Player::test_collisions() {

    // auto* cmap = new CollisionMap();
    auto* cset = new CollisionSet();

    if(!level) return cset;

    // PRINT("# cols => " + STR(cset->size()));

    Collision body_collision, foot_collision;

    for(Platform& line: level->platforms) {

        bool can_jump = false;
        SurfaceType col_type = NONE;
        vec2 normal;
        float angle = 0.f;
        float magnitude = 0.f;

        // PRINT("checking distance");

        float dist = (box.getPosition() - line.getPosition()).magnitude();

        // only test collision if within proximity
        if((box.getPosition() - line.getPosition()).magnitude() < line.get_length() + 10) {

            // PRINT("finding collision");

            // COLLISION WITH PLAYER
            // ---------------------

            body_collision = get_collision(line.get_shape(), body_hb);

            // PRINT("testing collision");

            // COLLISION WITH FEET HITBOX
            // --------------------------

            if(not can_jump) {

                foot_collision = get_collision(line.get_shape(), foot_hb);
                can_jump = foot_collision.has_collided();
            }

            if(body_collision.has_collided()) { // player is colliding

                // PRINT("collision found");

                // adjust object position by minimum translation vector

                normal = *body_collision.get_normal();
                magnitude = *body_collision.get_overlap_len();
                angle = normal.heading(-180, 180);


                if(angle >= -50 and angle <= 50) {

                    col_type = FLOOR;
                }
                else if(angle <= -135 or angle >= 135) {

                    col_type = CEILING;
                }
                else {

                    col_type = WALL;
                }

                // add collision info to the corresponding collision type
                // (*cmap)[col_type].push_back({can_jump, col_type, line, normal, angle, magnitude});
                // PRINT(
                //     "adding collision (" + STR(cset->size()) + ")\n"
                //     "  surface: " + STR(col_type) + "\n"
                //     "  normal: " + (string)normal + "\n"
                //     "  angle: " + STR(angle) + "\n"
                //     "  mag: " + STR(magnitude) + "\n"
                // );
                // PRINT("plat_type => " + STR(line.get_type()));
                cset->insert({can_jump, col_type, &line, normal, angle, magnitude});
            }
        }
    }

    return cset;
}

void Player::update(float delta) {

    update_afterimage(delta);

    // ------------------------------------------------------------------------
    // camera calculations
    // ------------------------------------------------------------------------

    view.setSize({1280.f / view_zoom, 720.f / view_zoom});

    // the nearest 1280x720 region the player is in
    vec2 region(roundf(get_pos().x / 1280.f), roundf(get_pos().y / 720.f));

    view.setCenter(vec2((region.x) * 1280, (region.y) * 720));

    l_region.setString(level->get_region_title(region));

    // ------------------------------------------------------------------------
    // stasis behavior (initial behavior)
    // ------------------------------------------------------------------------

    if(stasis) {

        this->box.rotate(delta * 500);
        this->tri.rotate(delta * 500);

        // slowly zoom in
        if(view_zoom < 4.f)
            view_zoom = fmin(4.f, view_zoom + delta);

        return;
    }

    // zoom out
    if(view_zoom > 1.f)
        view_zoom = fmax(1.f, view_zoom - delta * 20);

    // PRINT("vel=" + (string)vel);
    // PRINT("cos=" << normal_cos);

    // ------------------------------------------------------------------------
    // gravity impl
    // ------------------------------------------------------------------------

    // y-axis acceleration due to gravity

    if(vel.y < 1500 and not is_grounded)
        vel.y += fmax(0.5, fmin(fabs(vel.y) / 1000, 1)) * delta * 5000;


    // x-axis acceleration due to movement

    if(r_pressed and vel.x < 800)
        vel.x += delta * 5000;

    if(l_pressed and vel.x > -800)
        vel.x -= delta * 5000;

    // x-axis deceleration due to no movement

    if(!r_pressed and !l_pressed and not is_spinning) {

        if(vel.x > +0.5) { vel.x -= fmin(+delta * 6000, vel.x); }
        if(vel.x < -0.5) { vel.x -= fmax(-delta * 6000, vel.x); }

        if(vel.x <= 0.5 and vel.x >= -0.5) vel.x = 0;
    }

    // out-of-bounds auto reset
    if(fabs(get_pos().x) > 10000 or fabs(get_pos().y) > 10000) {

        this->respawn(region);
        return;
    }

    // ==================================================
    //  collision checks
    // ==================================================

    vec2 pos = get_pos();

    // std::unique_ptr<CollisionMap> cmap(test_collisions());
    std::unique_ptr<CollisionSet> cset(test_collisions());

    // concat floor - wall - ceiling collisions, in that order

    bool can_jump = false;
    bool on_ground = false;

    string plat_info = "";


    float normal_cos = 1.f, normal_sin = 1.f;

    //-------------------------------------------------------------------------
    // check floor collisions

    // PRINT("# cols => " + STR(cset->size()));

    int i = 0;
    // for(CollisionInfo col: (*cmap)[FLOOR]) {
    for(CollisionInfo col: *cset) {

        // PRINT("processing collision (" + STR(i) + ")");
        if(col.normal == vec2::ZERO) {
            PRINT(
                "WARNING: collided with a zero normal"
                // "  surface: " + STR(col.surface) + "\n"
                // "  normal: " + (string)col.normal + "\n"
                // "  angle: " + STR(col.angle) + "\n"
                // "  mag: " + STR(col.magnitude)
            );
            continue;
        }

        PlatformType plat_type = col.platform->get_type();

        // PRINT("plat_type => " + STR(plat_type));
        if(plat_type == PlatformType::HAZARD) {
            PRINT("==== PLAYER HIT HAZARD ====");
            this->respawn(region);
            return;
        }

        if(is_spinning) { // then bounce off the surface

            // calculates the angle of reflection
            this->vel = (vel - (col.normal * 2 * vel.dot(col.normal)));
            break;
        }

        switch(col.surface) {
        case FLOOR:
            normal_cos = col.normal.dot(vec2::RIGHT);

            // only resolve collision in y-axis to avoid sliding on ramps
            // PRINT("surface = " + (string)col.normal);
            // PRINT("surface * UP = " + STR(col.normal.dot(vec2::UP)));
            pos.y -= col.magnitude / col.normal.dot(vec2::UP);

            plat_info += "FLOOR cos=" + STR(normal_cos) + "\n";

            if(!can_jump and col.can_jump) can_jump = true;
            if(!on_ground) on_ground = true;

            break;

    // }

    //-------------------------------------------------------------------------
    // check wall collisions

    // for(CollisionInfo col: (*cmap)[WALL]) {

        case WALL:
            // const PlatformType& plat_type = col.platform.get_type();
            // if(check_hazard_cols(col) or check_spinbounce(col)) break;

            normal_sin = col.normal.dot(vec2::UP);

            pos -= col.normal * col.magnitude; // resolve collision

            plat_info += "WALL sin=" + STR(normal_sin) + "\n";

            // wall: next position calculations

            break;


    //-------------------------------------------------------------------------
    // check ceiling collisions

    // for(CollisionInfo col: (*cmap)[CEILING]) {

        case CEILING:
        // const PlatformType& plat_type = col.platform.get_type();
        // if(check_hazard_cols(col) or check_spinbounce(col)) break;

        // resolve collisions

            pos -= col.normal * col.magnitude; // resolve collision
        // this->vel.y = 100;
            plat_info += "CEIL";

            break;
        }
        i++;
    }

    //-------------------------------------------------------------------------
    // position calculation in air (no collisions)

    pos.x += this->vel.x * fmax(normal_sin, 0.1) * delta;
    pos.y += this->vel.y * normal_cos * delta;

    if(jump_timer > 0)
        jump_timer -= delta;

    if(this->can_jump != can_jump) {

        this->can_jump = can_jump;

        if(can_jump) {
            PRINT("can now jump");
        } else {
            PRINT("cannot jump");
        }
    }

    if(this->is_grounded != on_ground) {

        if(this->is_grounded = on_ground) {
            PRINT("touched ground");
            set_color({255, 255, 255});
            num_dashes = 1;
        } else {
            PRINT("left ground");
            if(!is_spinning and jump_timer <= 0) vel.y = 0;
        }
    }

    if(is_spinning) {

        float mag = vel.magnitude();

        this->box.rotate(mag * delta * 2);
        this->tri.rotate(mag * delta * 2);

    } else {

        this->box.setRotation(this->vel.x * 50 / 1000);
        this->tri.setRotation(this->vel.x * 50 / 1000);
    }

    // 64 px above center of player
    l_pos.setString((string)pos);

    // 32 px above l_pos
    l_vel.setString((string)vel);

    // 64 px above l_vel
    l_plat.setString(plat_info + "\nspinning = " + STR(is_spinning) + "\ncan jump = " + STR(can_jump)
                     + "\ndashes = " + STR(num_dashes));

    // PRINT((string)pos);
    set_pos(pos);

    CompositeEntity::update(delta);
}

void Player::respawn(const vec2& region) {

    set_pos(level->get_checkpoint(region));
}
