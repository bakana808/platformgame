
#pragma once

#include "common.h"
#include <iostream>

using namespace std;

class Button : public sf::Drawable {
public:
    Button(const Button&) = delete;
    Button& operator=(const Button&) = delete;
    Button(int x, int y, string s);

    void update(float deltaTime);
    bool ButtonIsLight;
    bool Selected;
    bool Enabled;

private:
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
    sf::RectangleShape _shape;
    sf::Text _text;
    int posX;
    int posY;
    sf::Font _font;
    sf::Color Butt_High_Light;
    sf::Color Butt_backgroud;
    sf::Vector2f _velocity;
    int Button_Frame_count;
};