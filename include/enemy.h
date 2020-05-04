#include <SFML/Graphics.hpp>
#include"player.h"

class Enemy: public CompositeEntity {

private:
    int speed = 4;

public:

    int enemyXposition=200;
    int enemyYposition=200;
    int fireballXposition=enemyXposition;
    int fireballYposition=enemyYposition;
    int teleporterXposition=250;
    int teleporterYposition=250;

    //This is the current enemy's image
    sf::Texture tex;
    sf::Sprite enemyimage;
    sf::Sprite fireballimage;
    sf::Sprite teleporterimage;
    sf::View& view;
    sf::View& hud;

 	//Enemy Cosnstructor
    Enemy(sf::View& view, sf::View&hud);

    void update(float delta) override;

    //Handle enemy movement

    void enemyMove();

    void spawnEnemyfireball();

    void enemyFireballattack();

    void spawnTeleporter();

    void enemySpawn();

    int Random_position(int start, int stop);
};
