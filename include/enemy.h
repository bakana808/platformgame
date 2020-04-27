
#include <SFML/Graphics.hpp>
#include <Time.h>
#include <stdlib.h>

class Enemy
{
private:
    int speed = 4;

public:
    float posx;
    float posy;

    //This is the current enemy's image
    sf::Texture tex;
    sf::Sprite enemyimage;
    sf::Sprite fireballimage;
    sf::Sprite teleporterimage;

    //Enemy Cosnstructor
    Enemy();

    //Handle enemy movement
    void move();

    //Enemy Fireball??//
    //A fireball shooting from the enemy mouth//

    void fireball();

    void teleport();

    int PICK(int start, int stop);
};
