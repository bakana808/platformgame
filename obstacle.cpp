
#include "obstacle.h"
#include <time.h>

Obstacle::Obstacle()
{
    //Mountain obstacle//

    tex.loadFromFile("mountainprototype.png");
    mountainprototype.setTexture(tex);
    mountainprototype.setScale(0.5, 0.5);
    mountainprototype.setPosition(200, 400);
}

void Obstacle::obby_thorns_active()
{
    //Time based//
    if (sf::Time::t1 = sf::seconds(5f))
    {

        //Transform mountain to mountian with electric thorns//
        tex.loadFromFile("mountain.png");
        mountain.setTexture(tex);
        mountain.setScale(0.5, 0.5);
        mountain.setPosition(200, 400);
        //Thorns coming out of other obstacles//
    }

    void out_of_bounds()
    {
        //FUnction setting limits for out of bounds//
        //If player setposition greater than end of map//
        //Kill player//
        //Enemy cannot go out of bounds//
    }
}
