#include <SFML/Graphics.hpp>
//Enemy.hpp//
///Enemy classes///
//Possible Obstacles///


	class Enemy: public player{
	
		private:
			int speed = 5;

		public:
			sf::Texture text;
			sf::Sprite enemyimagecharacter; //Character enemy//
			sf::Sprite enemyimageobstacle; //Obstacleenemy//
		
		//Enemy Constructor//
		Enemy();

		//ENemy Destructor//
		~Enemy();

		//Gets player position//
		//Then move towards that position//
		//Function to move towards the player psoition//
		
     void enemy_move(int posx, int posy);
	
     	void enemy_attack(int posx, int posy){

	};
