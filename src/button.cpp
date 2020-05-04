#include <iostream>
#include <SFML/Graphics.hpp>
#include "button.h"

using namespace std;

const float Button_wide =200;
const float Button_high =50;
const float Menu_Font_Size =24;
const float Button_Scale_Rate= 1.01;




Button::Button(int x, int y,string s) : _shape(sf::Vector2f(Button_wide,Button_high))
{
    Enabled = true;
    Selected = false;
    ButtonIsLight=false;
    Butt_High_Light = sf::Color::White;
    Butt_backgroud = {200, 200, 200};
    _shape.setFillColor(Butt_backgroud);
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
    Button_Frame_count = 0;

}

void Button::update(float delta) {

    if(ButtonIsLight){
        _shape.setFillColor(Butt_High_Light);
    }else{
        _shape.setFillColor(Butt_backgroud);
    }
        //highlight
    if (Selected) {
        if(Button_Frame_count<100){
                _shape.scale(Button_Scale_Rate,Button_Scale_Rate);
                _text.scale(Button_Scale_Rate,Button_Scale_Rate);
                Button_Frame_count++;
        }else if(Button_Frame_count<200){
                _shape.scale(Button_Scale_Rate-0.02,Button_Scale_Rate-0.02);
                _text.scale(Button_Scale_Rate-0.02,Button_Scale_Rate-0.02);
                Button_Frame_count++;
        }else if(Button_Frame_count<400){
                _shape.move(5,0);
                _text.move(5,0);
                Button_Frame_count++;
        }else{
            Enabled = false;
        }
    }else{

    }

}

void Button::draw(sf::RenderTarget& target, sf::RenderStates states)
const {
    if (Enabled){
    target.draw(_shape, states);
    target.draw(_text, states);
    }else{


    }
}

