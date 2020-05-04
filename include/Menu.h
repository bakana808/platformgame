#include <iostream>
#include <SFML/Graphics.hpp>
#include "button.h"

using namespace std;


class Menu : public sf::Drawable {
public:
    Menu(const Button&) = delete;
    Menu& operator=(const Button&) = delete;
    Menu();
    
    void update();
    //bool Selected;
    bool Enabled;
    int  Menu_Operation;
    bool exit;
private:
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
    int  Selection;
    Button start_game;
    Button exit_game;
};