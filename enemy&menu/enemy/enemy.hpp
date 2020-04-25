#include<SFML/Graphics.hpp>
#include <Time.h>
#include <stdlib.h>
class Enemy
{
	private:
		int speed = 4;

	public:

		posx=x;
		posy=y;

		//This is the current enemy's image
		sf::Texture tex;
		sf::Sprite enemyimage;

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
