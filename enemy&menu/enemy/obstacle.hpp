#include<SFML/Graphics.hpp>
#include <Time.hpp>

class Obstacle: public Enemy
{
	private:


	public:

		posx=x;
		posy=y;

		//This is the current enemy's image
		sf::Texture tex;
		sf::Sprite enemyimage;

		//Enemy Cosnstructor
		Obstacle();
		
		//Destructor//
		~Obstacle();

	//Obstacle Functions//
	
		
		//time bases thorns are activated through some obstacles//
		void obby_thorns_activate();

		void out_of_bounds();


