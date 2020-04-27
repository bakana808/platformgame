
#include "enemy.h"

Enemy::Enemy()
{
    tex.loadFromFile("goomba.png");
    enemyimage.setTexture(tex);
    enemyimage.setScale(0.5, 0.5);
    enemyimage.setPosition(300, 300);
}

void Enemy::fireball()
{

    tex.loadFromFile("fireballimage.png");
    fireballimage.setTexture(tex);
    fireballimage.setScale(0.2, 0.2);
    fireballimage.setPosition(295, 295);
}

void Enemy::move()
{
    //Handles movement
    //If player becomes too close, shoot a fireball at player//
    //else move left for a certain time and right for a certain time//
    //waiting for trouble//

    // if the player is within 15 units of this enemy
    // if (goomba.enemyimage.getPosition().x - player1.playerimage.getPosition().x <= 15)
    // {
    //     goomba.enemyimage.move(30, 0);

    //     fireball1.fireballimage.move(0, 20);
    //     fireball1.fireballimage.move(5, 0);
    // }
    // else
    //     goomba.enemyimage.move(0, 20);
    // goomba.enemyimage.move(5, 0);
}

void teleport()
{
    //psychic/ghost kind Enemy//
    //porter will teleport through time into different spaces on the map//
    //randomly??or preset spaces//
    //randomly using time??//

    tex.loadFromFile("teleporter.png");
    teleporterimage.setTexture(tex);
    teleporterimage.setScale(0.3, 0.3);
    teleporterimage.setPosition(400, 600);

    //If 5 seconds pass//
    //Wjile teleporter is in startig position//
    while(teleporterimage.setPosition(400,600) {
        if (sf::Time::t1 = sf::seconds(5f))
        {
            //Randomly teleport enemy on screen//
            int numx;
            int numy;

            numx = PICK(0, 600);
            numy = PICK(0, 600);

            //Displaying teleporter after 5 seconds//
            teleporterimage.setPosition(numx, numy);
        }
        else
            return teleporterimage.setPosition(0, 0);
    }
}

int PICK(int start, int stop)
{
    return (rand() % (stop - start + 1)) + start;
}

//Boss, if user reaches end of level or something//
void boss()
{
    //Create boss image//
    tex.loadFromFile("boss.png");
    boss.setTexture(tex);
    boss.setScale(10, 10);
    boss.setPosition(400, 600);

    //Boss attacks//
    //Boss Health//
}
