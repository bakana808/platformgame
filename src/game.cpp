
#include "game.h"
#include "player.h"
#include "hud.h"
#include <math.h>


Game::Game()
: view({0.f, 0.f}, {WIDTH, HEIGHT})
, hud_view({0.f, 0.f}, {WIDTH, HEIGHT})
, start(20,50,"Start Game")
{
    player = em.spawn_entity<Player>(view, hud_view);
    level = em.spawn_entity<Level>(this);

    player->set_level(*level);

    // this isn't added to the manager since it's rendered
    // in a different view
    hud = new HUD(this);

    sf::ContextSettings settings;
    settings.antialiasingLevel = 8;
    window = new sf::RenderWindow(sf::VideoMode(1280, 720), "Game", sf::Style::None, settings);
    window->setFramerateLimit(200);
    window->setKeyRepeatEnabled(false);

    PRINT("created game");
}

Game::~Game() {

    delete hud;
    delete window;
    delete editor;
}

void Game::run() {

    level->load("level.txt");

    while (window->isOpen()) {

        float dt = fc.get_delta();

        processEvents();
        update(dt);
        render();
        window->display();

        fc.push_frame();
    }

    level->save();
}

void Game::processEvents() {

    sf::Event event;
    while (window->pollEvent(event)) {
        if (event.type == sf::Event::Closed) {
            window->close();
        } else if (event.type == sf::Event::KeyPressed) {

            if(editor and !menu.Enabled) {
                editor->key_press(event.key.code);
            }
            else if(!editor) {
                player->key_press(event.key.code);
            }

            if (event.key.code == sf::Keyboard::Escape) {
                window->close();
            } else if (event.key.code == sf::Keyboard::Up) {
                menu.Menu_Operation = 1;
            } else if (event.key.code == sf::Keyboard::Down) {
                menu.Menu_Operation = 2;
            } else if (event.key.code == sf::Keyboard::Key::Return) {
                menu.Menu_Operation = 3;
            }

            if(event.key.code == Key::E) {
                if(editor) {
                    em.delete_entity(editor);
                    editor = nullptr;
                } else {
                    editor = em.spawn_entity<Editor>(this);

                    vec2 pos = player->get_pos();
                    editor->set_pos({roundf(pos.x / 10) * 10, roundf(pos.y / 10) * 10});
                }
            }

        } else if (event.type == sf::Event::KeyReleased) {

            if(editor and !menu.Enabled) {
                editor->key_release(event.key.code);
            }
            else if(!editor) {
                player->key_release(event.key.code);
            }

            if(event.key.code == sf::Keyboard::Up)
                menu.Menu_Operation = 0;
            else if (event.key.code == sf::Keyboard::Down)
                menu.Menu_Operation = 0;
            else if (event.key.code == sf::Keyboard::Key::Return)
                menu.Menu_Operation = 0;
        }
    }
}


void Game::update(float delta) {

    if(menu.Enabled){

        menu.update(delta);

    }else if(menu.exit){

        window->close();

    }else{

        if(editor) {

            editor->update(delta);

        } else {

            // PRINT("updating HUD");
            hud->update(delta);

            // PRINT("updating EM");
            em.update(delta);

            // PRINT("done updating");
        }
    }
}


void Game::render() {

    window->clear({20, 20, 50});

    if(menu.Enabled){

        window->draw(menu);
        return;
    }

    //=========================================================================
    // WORLD RENDERING
    //=========================================================================

    // PRINT("drawing EM");
    window->setView(view);
    window->draw(em); // entity manager

    //=========================================================================
    // HUD RENDERING
    //=========================================================================

    // PRINT("drawing HUD");
    window->setView(hud_view);
    window->draw(*hud); // HUD object

}
