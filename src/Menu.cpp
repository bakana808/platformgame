#include <iostream>
#include <SFML/Graphics.hpp>
#include "Menu.h"

using namespace std;

Menu :: Menu():
    start_game(600,200,"Start Game"),
    exit_game(600,520,"Exit Game"){
        Selection = 1;
        Menu_Operation = 0;//default operation,1 for up,2 for down,3 for enter.
        Enabled =true;
        start_game.ButtonIsLight=true;
        exit_game.ButtonIsLight=false;
        exit = false;
    }





void Menu::update() {
    //response for keboard event
    if(Menu_Operation == 1){//up
        start_game.ButtonIsLight=true;
        exit_game.ButtonIsLight=false;

    }else if(Menu_Operation == 2){//down
        exit_game.ButtonIsLight=true;
        start_game.ButtonIsLight=false;

    }else if(Menu_Operation == 3){//enter
        if(start_game.ButtonIsLight==true){
            start_game.Selected = true;
        }else{
            exit_game.Selected = true;
        }
    }
    //refresh menu state.

    start_game.update();
    exit_game.update();

    //disable if animation done
    if(start_game.Enabled==false){
        Enabled=false;
    }else if(exit_game.Enabled==false){
        Enabled=false;
        exit = true;
    }
}



void Menu::draw(sf::RenderTarget& target, sf::RenderStates states)
const {
    if (Enabled){
    target.draw(start_game, states);
    target.draw(exit_game, states);
    }else{
    }
}
