#include <iostream>
using namespace std;
#include "player.hpp"

		//A file containing the display for menu///
		//How many dashes left//
		//inherited from player class//



	//Dash Constructor for The menu Display//
	//2 dashes??//
	//Maybe the dashes reset within a time period??//
	
	Dash::Dash(){
		//Dash1//
		text.loadFromFile("dashimage.png");
		dashimage.setTexture(text);
		dashimage.setColor(sf::Color(30,30,30,30); //Lightblue?
		dashimage.setScale(4,4);
		dashimage.setPosition(0,700); //Top left screen??//
		
		//Dash2//
		text.loadFromFile("dashimage.png");
		dashimage.setTexture(text);
		dashimage.setColor(sf::Color(30,30,30,30); //Lightblue?
		dashimage.setScale(4,4);
		dashimage.setPosition(10,700); //Top left screen??//

	
		}

	Dash::~Dash(){
		if(Player == dash()){
		delete Dash();
			
	
	int dash_is_back( int seconds){
			
		//i think??//
		//if player used dash and seconds =3//
		//Then redraw the dash//
		if(Player ==dash()) && seconds ==3){
			Dash();
	};

	

