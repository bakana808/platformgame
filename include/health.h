#include <SFML/Graphics.hpp>

			//Health.hpp//
	class Health{
	
		public:
			int playerhealth;
			int enemyhealth;
			int lives;
			int death;
			int hit_count;
		
		//Getting and setting player health//
		//3 hit and he dies//

		getplayerhealth const {return playerhealth};
		sethealth(playerhealth=3);
		

		//One hit he gone//
		//Getting and setting enemy health//
		getenemyhealth const {return enemyhealth};
		setenemyhealth(enemyhealth = 1);
		
		//Health constructor//
	Health();

	//FUnction determininng if the player is dead//
	void is_dead( int playerhealth, int hitcount);
	
	//Function displaying the number of lives//
	void lives( int lives);
		

	};
