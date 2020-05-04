#include "enemy.h"
#include <SFML/Graphics.hpp>

//Defining Pick function//
int Enemy::Random_position(int start, int stop)
{
    return (rand() % (stop - start + 1)) + start;
}

//EnemyCreation//
void Enemy::enemySpawn()
{
    tex.loadFromFile("redsquare.png");
    enemyimage.setTexture(tex);
    enemyimage.setScale(0.5, 0.5);
    enemyimage.setPosition(enemyXposition, enemyYposition);

    //Handles enemy Movement&Fireballattack//
    enemyMove();
    enemyFireballattack();
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
    tex.loadFromFile("redsquare.png");
    fireballimage.setTexture(tex);
    fireballimage.setScale(0.01, 0.01);
    fireballimage.setPosition(fireballXposition, fireballYposition);
}

void Enemy::enemyFireballattack()
{

    while (fireballXposition == 300)
    {
        spawnEnemyfireball();

        //shootingFireballImage//

        fireballXposition--;
        //Updating fireballMovement//
        fireballimage.setPosition(fireballXposition, fireballYposition);
    }
}

void Enemy::spawnTeleporter()
{

    tex.loadFromFile("teleporter.png");
    teleporterimage.setTexture(tex);
    teleporterimage.setScale(0.3, 0.3);
    teleporterimage.setPosition(teleporterXposition, teleporterYposition);

    //while teleporter is in starting position//
    while (teleporterXposition == 250)
    {

        //Teleporter Moves to Random position on map//
        teleporterXposition = Random_position(0, 300);
        teleporterYposition = Random_position(0, 300);

        //New Teleporter Position//
        teleporterimage.setPosition(teleporterXposition, teleporterYposition);
    }
}

Enemy::Enemy(sf::View &view, sf::View &hud): view(view), hud(hud)
{
    enemySpawn();
    spawnTeleporter();
}

void Enemy::update(float delta) {

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
