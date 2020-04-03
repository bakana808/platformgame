
#include <SFML/Graphics.hpp>
// #include "player.h"

int main(void) {

    sf::RenderWindow window(sf::VideoMode(1280, 720), "Game");

    // Player player;

    while(window.isOpen()) {

        sf::Event e;

        if(window.pollEvent(e)) {

            if(e.type == sf::Event::EventType::KeyPressed) {

                // player.key_press(e.key.code);
                if(e.key.code == sf::Keyboard::Escape) {

                    window.close();
                }
            }


            if(e.type == sf::Event::EventType::KeyReleased) {

                // player.key_release(e.key.code);
            }
        }

        window.clear();

        // window.draw(player);

        window.display();
    }
}