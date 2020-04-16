#include <iostream>
#include <SFML/Graphics.hpp>
#include "player.hpp"



		
	class Dash: public Player{
	
		public:
		int dashcount;
	//Dash Constructor and destructor//
	Dash();

	~Dash();

	//DashFunction??//
	//Would be cool if like dash from Celeste//
			
	int dash_is_back( int seconds);
