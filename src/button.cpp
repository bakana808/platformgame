#include <iostream>
#include <SFML/Graphics.hpp>
using namespace std;

//Start game option//
Button::Button()
{
    tex.loadFromFile("menu.png");
    menu.setTexture(tex);
    menu.setScale(10, 10);
    menu.setPosition(300, 300);

    //Setings display Option//
    tex.loadFromFile("settings.png");
    settings.setTexture(tex);
    settings.setScale(10, 10);
    settings.setPosition(305, 305);
}

//Menu button being clicked//
void Button::isButtonClicked(int posx, int posy)
{
    if (button.image.getGlobalBounds().contains(300, 300))
    {
        ButtonClicked();

        //How to play setting//
        //Just prototype will make update soon//
    if(button.image.getGlobalBounds().contains(305,305){
            cout << " How to Play" << endl;
            cout << " Press X to go back to main menu" << endl;
            cout << "Directionals: " << endl;
            cout << " Keyboard use" << endl;
            cout << "WATCH OUT FOR ENEMIES AND OBSTACLES!" << endl;
            cout << "HAVE FUN!" << endl;
            //Draw new window//
            ////Draw Text in window//
            //if user presses x button, return to main menu//
            //How to play instructions//

	}



	void Button:: ButtonClicked(){

	}
