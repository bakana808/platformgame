#include<SFML/Graphics.hpp>

class Obstacle 
{
	private:

	public:
		
		//Start Position of traps//
		int topXposition=200;//Start offscreen//
		int topYposition=400;
		int bottomXposition=300;
		int bottomYposition=0;
		int topStopYposition=-100;
		int bottomStopYposition=500;

		//This is the current enemy's image
		sf::Texture tex;
		sf::Sprite topTrap;
		sf::Sprite bottomTrap;	

		void spawnTrap();

		void activateTrap();

	};
