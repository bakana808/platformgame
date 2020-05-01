#include "game.h"


Game::Game()
: view({0.f, 0.f}, {1280.f, 720.f})
, hud({0.f, 0.f}, {1280.f, 720.f})
, level("level.txt")
, player(view, hud)
{
    sf::ContextSettings settings;
    settings.antialiasingLevel = 8;

    window = new sf::RenderWindow(sf::VideoMode(1280, 720), "Game", 7U, settings);
    window->setFramerateLimit(200);
    window->setKeyRepeatEnabled(false);

    player.set_level(level);
}

Game::~Game() {

    delete window;
}

void Game::run() {

    while (window->isOpen()) {

        float dt = fc.get_delta();

        processEvents();
        update(dt);
        render();

        fc.push_frame();
    }
}

void Game::processEvents() {

    sf::Event event;
    if (window->pollEvent(event)) {
        if ((event.type == sf::Event::Closed)
          || ((event.type == sf::Event::KeyPressed) && (event.key.code == sf::Keyboard::Escape))) {
            window->close();
        }
        if(event.type == sf::Event::EventType::KeyPressed) {
                player.key_press(event.key.code);
                if(event.key.code == sf::Keyboard::Escape) {
                    window->close();
                }
            }
            if(event.type == sf::Event::EventType::KeyReleased) {
                player.key_release(event.key.code);
            }
    }
}

void Game::update(float delta) {
    player.update(delta);
}

void Game::render() {

    window->clear({20, 20, 50});

    //=========================================================================
    // WORLD RENDERING
    //=========================================================================

    window->setView(view);//zoom

    window->draw(player);
    window->draw(level);

    //=========================================================================
    // HUD RENDERING
    //=========================================================================

    window->setView(hud);

    player.draw_hud(*window);

    window->display();
}