#include <SFML/Graphics.hpp>

////File COntaining the button Class and prototypes for
// Functions in button class///


class Button{
	private:
	
	public:

	//The current buttons position//
	
	sf::Texture text;
	sf::Sprite buttonImage;

	//Constructor for the button class, taking x and y coordinate//
	Button(int posx, int posy);

	//Checking if the button was clicked//
	 
	void isButtonClicked(int posx, int posy);

	///Handling the button action once clicked///
	void Buttonclicked();

};
