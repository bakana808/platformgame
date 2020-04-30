#include "game.h"



Game::Game() : window(sf::VideoMode(1280, 720), "Game", 7U, settings),
                view({0.f, 0.f}, {1280.f, 720.f}),
                hud({0.f, 0.f}, {1280.f, 720.f}),
                level("level.txt"),
                player(view, hud)
                {
                    settings.antialiasingLevel = 8;
                    player.set_level(level);
                    window.setFramerateLimit(60);
                    window.setKeyRepeatEnabled(false);
                }

void Game::run() {
    while (window.isOpen()) {
        processEvents();
        update();
        render();
    }
}

void Game::processEvents() {
    sf::Event event;
    if (window.pollEvent(event)) {
        if ((event.type == sf::Event::Closed)
          || ((event.type == sf::Event::KeyPressed) && (event.key.code == sf::Keyboard::Escape))) {
            window.close();
        }
        if(event.type == sf::Event::EventType::KeyPressed) {
                player.key_press(event.key.code);
                if(event.key.code == sf::Keyboard::Escape) {
                    window.close();
                }
            }
            if(event.type == sf::Event::EventType::KeyReleased) {
                player.key_release(event.key.code);
            }
    }
}

void Game::update() {
    float dt = fc.get_delta();
    player.update(dt);
    window.setView(view);//zoom 
   fc.push_frame();//?
}

void Game::render() {
    window.clear({20, 20, 50});



    window.draw(player);
    window.draw(level);

    //indow.setView(hud);

    player.draw_hud(window);

    window.display();


}