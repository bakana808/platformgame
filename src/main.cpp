
#include <cmath>
#include <vector>

#include "common.h"
#include "frame_clock.h"
#include "player.h"
#include "platform.h"
#include "level.h"

int main(void) {

    sf::ContextSettings settings;
    settings.antialiasingLevel = 8;
    sf::RenderWindow window(sf::VideoMode(1280, 720), "Game", 7U, settings);

    FrameClock fc;

    sf::View view({0.f, 0.f}, {1280.f, 720.f});
    sf::View hud({0.f, 0.f}, {1280.f, 720.f});

    Level level("level.txt");
    Player player(view, hud);

    player.set_level(level);

    window.setFramerateLimit(200);
    window.setKeyRepeatEnabled(false);

    while(window.isOpen()) {


        float dt = fc.get_delta();

        // PRINT(dt);

        sf::Event e;

        if(window.pollEvent(e)) {

            if(e.type == sf::Event::EventType::KeyPressed) {

                player.key_press(e.key.code);
                if(e.key.code == sf::Keyboard::Escape) {

                    window.close();
                }
            }

            if(e.type == sf::Event::EventType::KeyReleased) {

                player.key_release(e.key.code);
            }
        }

        // std::cout << delta << std::endl;
        player.update(dt);

        window.clear({20, 20, 50});

        window.setView(view);

        window.draw(player);
        window.draw(level);

        window.setView(hud);

        player.draw_hud(window);

        window.display();

        fc.push_frame();
    }
}