

#include "player.h"
#include "collision.h"
#include <iostream>
#define _USE_MATH_DEFINES
#include <math.h>

void Player::key_press(sf::Keyboard::Key key) {

    if(key == sf::Keyboard::D)
        r_pressed = 1;

    if(key == sf::Keyboard::A)
        l_pressed = 1;

    if(key == sf::Keyboard::I and (stasis or can_jump) and not is_spinning) {
        vel.y = -1200;
        move({0, -1}); // shift player slightly up to avoid ground collisions
        jump_timer = 0.2f;
        stasis = false;
        PRINT("jump");
    }

    if(key == sf::Keyboard::U and !can_jump) {

        is_spinning = true;

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

            num_dashes--;

            vec2 dir = vec2(x, y).normalize();
            this->vel = dir * 1500;
            show_afterimage();

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

void Player::test_collision(vector<CollisionInfo>& collisions) {

    if(!lines) return;

    Collision body_collision, foot_collision;

    for(Platform line: *lines) {

        bool can_jump = false;
        CollisionType col_type = NONE;
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
            }

            // COLLISION WITH FEET HITBOX
            // --------------------------

            if(not can_jump) {

                foot_collision = get_collision(line.get_shape(), foot_hb);
                can_jump = foot_collision.has_collided();
            }

            if(col_type != NONE) {
                collisions.push_back({can_jump, col_type, line.get_type(), normal, angle, magnitude});
            }
        }
    }
}

void Player::update(float delta) {

    update_afterimage(delta);

    view.setSize({1280.f / view_zoom, 720.f / view_zoom});
    view.setCenter(get_pos());

    if(stasis) {

        this->box.rotate(delta * 500);
        this->tri.rotate(delta * 500);

        if(view_zoom < 4.f)
            view_zoom = fmin(4.f, view_zoom + delta);

        return;
    }

    if(view_zoom > 1.f)
        view_zoom = fmax(1.f, view_zoom - delta * 20);

    // PRINT("vel=" + (string)vel);
    // PRINT("cos=" << normal_cos);

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

        this->move(vec2::ZERO);
        return;
    }

    // ==================================================
    //  collision checks
    // ==================================================

    vec2 pos = get_pos();

    vector<CollisionInfo> collisions;
    test_collision(collisions);

    bool can_jump = false;
    bool on_ground = false;

    string plat_info = "NONE";

    for(auto col: collisions) {

        float normal_cos = 1.f, normal_sin = 1.f;

        if(col.plat_type == PlatformType::HAZARD) {
            PRINT("==== PLAYER HIT HAZARD ====");
            this->respawn();
            return;
        }

        // PRINT("coltype=" << col.type);
        // calculate bounce angle

        if(is_spinning and col.type != NONE) {

            // PRINT("angle => " << col.angle);
            // calculates the angle of reflection
            this->vel = (vel - (col.normal * 2 * vel.dot(col.normal)));
        }

        // fix collision (on floor)

        switch(col.type) {
        case FLOOR:

            normal_cos = col.normal.normalize().dot(vec2::RIGHT);
            // PRINT("cos=" << normal_cos);
            // only rectify collision in y-axis to avoid sliding on ramps
            pos.y -= col.magnitude / col.normal.normalize().dot(vec2::UP);

            plat_info = "FLOOR cos=" + STR(normal_cos);
            break;

        case WALL:

            normal_sin = col.normal.normalize().dot(vec2::UP);
            PRINT("norm=" << (string)col.normal);
            pos -= col.normal * col.magnitude;

            plat_info = "WALL sin=" + STR(normal_sin);
            break;

        case CEILING:

            this->vel.y = 100;
            plat_info = "CEIL";

        default:
            break;
        }

        if(!can_jump and col.can_jump) can_jump = true;

        if(!on_ground and col.type == FLOOR and !is_spinning) on_ground = true;

        if(!is_spinning) {
            pos.x += this->vel.x * fmax(normal_sin, 0.1) * delta;
            pos.y += this->vel.y * normal_cos * delta;
        } else {
            pos += this->vel * delta;
        }
    }

    // position calculation in air (no collisions)
    if(collisions.size() == 0) {

        pos += this->vel * delta;
    }

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
            num_dashes = 1;
        } else {
            PRINT("left ground");
            if(jump_timer <= 0) vel.y = 0;
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
}

void Player::respawn(void) {

    set_pos({0, 0});
}
