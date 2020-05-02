#include <SFML/Graphics.hpp>
#include<iostream>
using namespace std;

class Button : public sf::Drawable {
public:
    Button(const Button&) = delete;
    Button& operator=(const Button&) = delete;
    Button(int x, int y, string s);
    
    void update(sf::Time deltaTime);
    bool Selected;
    bool Enabled;
    
private:
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
    sf::RectangleShape _shape;
    sf::Text _text;      
    int posX;
    int posY;
    sf::Font _font;
};