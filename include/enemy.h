
#pragma once

#include "common.h"
#include "player.h"
#include "entity.h"
#include "collision.h"


class Game;
class Enemy;


class Bullet: public CompositeEntity {
private:

    bool enabled = true;

    Game* game;
    Enemy* source;

    sf::RectangleShape body;

    vec2 dir;
    float speed;

public:

    Bullet(Game* game, Enemy* source, vec2 direction, float speed)
    : game(game)
    , source(source)
    , dir(direction.normalize())
    , speed(speed)
    {
        body.setFillColor(sf::Color::Red);
        body.setSize({32, 32});
        body.setOrigin({16, 16});

        this->add_child(body);
    }

    void update(float delta) override;
};

class Enemy: public CompositeEntity {

private:

    Game* game;

    int speed = 4;

public:

    Bullet* bullet;

    int enemyXposition=200;
    int enemyYposition=200;
    int fireballXposition=enemyXposition;
    int fireballYposition=enemyYposition;
    int teleporterXposition=250;
    int teleporterYposition=250;

    //This is the current enemy's image
    sf::ConvexShape body;
    // sf::Sprite enemyimage;
    // sf::Sprite fireballimage;
    // sf::Sprite teleporterimage;

 	//Enemy Cosnstructor
    Enemy(Game* game);

    ~Enemy() {
        delete_bullet();
    }

    void update(float delta) override;

    //Handle enemy movement

    /**
     * @brief Return the vector of this position minus the player's position.
     *
     * @return vec2
     */
    vec2 get_player_axis();

    /**
     * @brief Fire a bullet at the player.
     *
     */
    void fire_bullet();

    void delete_bullet();

    void enemyMove();

    void spawnEnemyfireball();

    void enemyFireballattack();

    void spawnTeleporter();

    int Random_position(int start, int stop);
};
