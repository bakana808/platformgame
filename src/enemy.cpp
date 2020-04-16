#include <SFML/Graphics.hpp>
#include "enemy.hpp"

				//Enemy.cpp//


	//ENemy Constructor//
	Enemy::Enemy(){
		text.loadFromFile("enemyimage.png"); //EnemycharacterImage//
		enemyimage.setTexture(text);
		enemyimage.setColor(sf::Color(255,255,255,255));
		enemyimage.setScale(.5,.5);
		enemyimage.setPosition(200,200);

		//For the Enemy Obstacle//
		text.loadFromFile("enemyobstacle.png"); //EnemyobstacleImage//
		enemyimage.setTexture(text);
		enemyimage.setColor(sf::Color(200,200,200,200));
		enemyimage.setScale(10,10);
		enemyimage.setPosition(400,5000);
		


	}

	//Deleting enemy//
	Enemy::~Enemy(){
		delete enemy;

	}

		
		//Function to move towards the player psoition//
		
     void enemy_move(int posx, int posy);
		getPlayerposition(return posx,posy);
		
		if(enemyimage.getGlobalBounds().contains(posx,posy){
				enemypos= Playerposition-posx;}

	void enemy_attack(int posx, int posy){
		//GetPlayer Position//
		getPlayerposition(return posx, posy);
		
	//If enemy within close range of player, player health minus1//
		if(enemy.image.getGlobalBounds().contains(posx,posy){
			playerhealth--;
			else
			enemy_move(int posx, int posy);

	//If player steps within x or y coordinates of enemy box//
	//Then enemy move towards position player is coming from //
	
