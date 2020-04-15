#include <SFML/Graphics.hpp>
#include "health.hpp"
using namespace std;

			//Health.cpp//

	Health::Health(){


		//Loading lives image to screen//
		 //Live 1//

		text.loadFromFile("livesdisplay.png");
		livesdisplay.setTexture(text);
		livesdisplay.setColor(sf::Color(0,0,0,0));
		livesdisplay.setScale(3,3);
		livesdisplay.setPostion(500,900); //Far right screen//

		//Live 2//

		text.loadFromFile("livesdisplay1.png");
		livesdisplay1.setTexture(text);
		livesdisplay1.setColor(sf::Color(0,0,0,0));
		livesdisplay1.setScale(3,3);
		livesdisplay1.setPostion(510,900); //Far right screen//

		
		//Live 3//
		//Last Life//

		text.loadFromFile("livesdisplay.png");
		livesdisplay2.setTexture(text);
		livesdisplay2.setColor(sf::Color(0,0,0,0));
		livesdisplay2.setScale(3,3);
		livesdisplay2.setPostion(520,900); //Far right screen//

		//Player is dead if he runs off the screen or health=0//
		int is_dead(int playerhealth, int hit_count){
			if( playerhealth==0|| Playerposition == posx, posy){
			delete text.loadFromFile("livesdisplay.png");}

			else
				return 0;

	//After death, redraws player to the screen at starting position//
		void respawn(){

		//Draw player to the screen at the statring position//
		
		
		text.loadFromFile("playerimage.png");
		playerimage.setTexture(text);
		playerimage.setColor(sf::Color(0,0,0,0));
		playerimage.setScale(3,3);
		playerimage.setPostion(520,900);//Start Position for level//		
