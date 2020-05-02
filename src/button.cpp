#include <iostream>
#include <SFML/Graphics.hpp>
#include "button.h"

using namespace std;

const float Button_wide =200;
const float Button_high =50;
const float Menu_Font_Size =24;
Button::Button(int x, int y,string s) : _shape(sf::Vector2f(Button_wide,Button_high))
{
    _shape.setFillColor(sf::Color::White);
    _shape.setOrigin(_shape.getLocalBounds().width/2, _shape.getLocalBounds().height/2);
    _shape.setPosition(x, y);
    _font.loadFromFile("FiraCode-VF.ttf");
    _text.setFont(_font); // font is a sf::Font
    _text.setString(s);
    _text.setCharacterSize(Menu_Font_Size); // in pixels, not points!
    _text.setFillColor(sf::Color::Black);
    _text.setStyle(sf::Text::Bold);
    _text.setOrigin(_text.getLocalBounds().width/2, _text.getLocalBounds().height/2+8);
    _text.setPosition(x, y);
}

void Button::update(sf::Time deltaTime) {
    float seconds = deltaTime.asSeconds();
    
    if (Selected) {

    }

    if (Enabled) {
    }
}

void Button::draw(sf::RenderTarget& target, sf::RenderStates states)
const {
    target.draw(_shape, states);
    target.draw(_text, states);
}