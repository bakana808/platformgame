#include <iostream>
#include <SFML/Graphics.hpp>
#include "button.hpp"
using namespace std;


	
	

	//Button Constructor, Creating the button//
	Button::Button(int posx, int posy){
		text.loadFromFile("startgamepic.png");
		buttonImage.setTexture(text);
		buttonImage.setColor(sf::Color(30,30,30,30);
		buttonImage.setScale(.5,.5);
		buttonImage.setPosition(200,200);
	
		//Checking if the Button was clicked, starting game//
	void Button:: isButtonClicked( int posx, int posy){
		if(button.image.getGlobalBounds().contains(posx,posy)){
			ButtonClicked();
	}

	

	void Button:: ButtonClicked(){

	}
