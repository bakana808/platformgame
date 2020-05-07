
#include "enemy.h"
#include "game.h"
#include "level/region.h"
#include <math.h>

Enemy::Enemy(Game* game): game(game)
{
    PRINT("creating enemy");
    // tex.loadFromFile("redsquare.png");

    body = add_child<sf::ConvexShape>();
    body->setPointCount(3);
    body->setPoint(0, {-32, 32});
    body->setPoint(1, {+32, 32});
    body->setPoint(2, {0, -32});
    body->setFillColor({255, 0, 0});

    PRINT("    done");

    // enemyimage.setTexture(tex);
    // enemyimage.setScale(0.5, 0.5);
    // enemyimage.setPosition(enemyXposition, enemyYposition);

    // spawnTeleporter();
}

//Defining Pick function//
int Enemy::Random_position(int start, int stop)
{
    return (rand() % (stop - start + 1)) + start;
}

void Enemy::enemyMove()
{
    //If player becomes too close, shoot a fireball at player//
    //else move le

    while (enemyXposition == 200)
    {

        //Move towards enemy//
        enemyXposition--;
    }
}

void Enemy::spawnEnemyfireball()
{
    // tex.loadFromFile("redsquare.png");
    // fireballimage.setTexture(tex);
    // fireballimage.setScale(0.01, 0.01);
    // fireballimage.setPosition(fireballXposition, fireballYposition);
}

void Enemy::enemyFireballattack()
{

    while (fireballXposition == 300)
    {
        spawnEnemyfireball();

        //shootingFireballImage//

        fireballXposition--;
        //Updating fireballMovement//
        // fireballimage.setPosition(fireballXposition, fireballYposition);
    }
}

void Enemy::spawnTeleporter()
{

    // tex.loadFromFile("teleporter.png");
    // teleporterimage.setTexture(tex);
    // teleporterimage.setScale(0.3, 0.3);
    // teleporterimage.setPosition(teleporterXposition, teleporterYposition);

    //while teleporter is in starting position//
    while (teleporterXposition == 250)
    {

        //Teleporter Moves to Random position on map//
        teleporterXposition = Random_position(0, 300);
        teleporterYposition = Random_position(0, 300);

        //New Teleporter Position//
        // teleporterimage.setPosition(teleporterXposition, teleporterYposition);
    }
}

vec2 Enemy::get_player_axis() {

    return this->get_pos() - game->get_player().get_pos();
}

void Enemy::delete_bullet() {
    if(bullet) {
        this->remove_child(bullet);
        bullet = NULL;
    }
}

void Enemy::fire_bullet() {

    delete_bullet();

    bullet = add_child(new Bullet(game, this, get_player_axis() * -1, 3));
    bullet->set_pos(this->get_pos());
}

void Enemy::update(float delta) {

    // if enemy is not on the same region as the player then do nothing

    if(LevelRegion::get_coords(this) != game->get_player().get_region()->get_coords()) {
        fire_timer = 0.f;
        delete_bullet();

        return;
    }

    // fade to red before firing

    float factor = fire_timer / 2.f;
    sf::Uint8 r = (int)(factor * factor * factor * 255);
    sf::Uint8 gb = 255 - r;
    body->setFillColor({r, gb, gb});

    // increment timer to fire

    fire_timer += delta;

    if(fire_timer > 2.f) {
        fire_timer -= 2.f;
        fire_bullet();
    }

    if(bullet) {
        bullet->update(delta);
    }

    // rotate to "aim" at the player

    body->setRotation(-get_player_axis().heading());
}


void Bullet::update(float delta) {

    this->move(dir * speed);

    sf::CircleShape *p_body = game->get_player().get_body();

    // collision check on player

    if(get_collision(*body, *p_body).has_collided()) {
        game->get_player().respawn();
    }

    // collision check on platforms

    for(auto plat: game->get_level().get_platforms()) {

        if(get_collision(*body, plat.get_shape()).has_collided()) {

            // source->remove_child(this);
        }
    }
}

//////IDEAS && ADD-ONS/////
///////////////////////////
///////////////////////////

/*void Enemy::spawnGhostenemy(){

	}


	//Spawning Boss, if user reaches end of level//
	void Enemy:: spawnboss(){

	//Create boss image//
	tex.loadFromFile("boss.png");
	boss.setTexture(tex);
	boss.setScale(10, 10);
	boss.setPosition(400,600);

	//Boss attacks//
	//Boss Health//
}*/
