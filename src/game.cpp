
#include "game.h"
#include "player.h"
#include "hud.h"
#include <math.h>


Game::Game()
: view({0.f, 0.f}, {WIDTH, HEIGHT})
, hud_view({0.f, 0.f}, {WIDTH, HEIGHT})
, start(20,50,"Start Game")
, player(view, hud_view)
{
    level = new Level(this);
    hud = new HUD(this);
    sf::ContextSettings settings;
    settings.antialiasingLevel = 8;
    window = new sf::RenderWindow(sf::VideoMode(1280, 720), "Game", 7U, settings);
    window->setFramerateLimit(200);

    window->setKeyRepeatEnabled(false);

    player.set_level(*level);

    // editor = new Editor(this);
}

Game::~Game() {

    delete hud;
    delete window;
    delete level;
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
                player.key_press(event.key.code);
            }

            if (event.key.code == sf::Keyboard::Escape) {
                window->close();
            } else if (event.key.code == sf::Keyboard::Up) {
                menu.Menu_Operation = 1;
            } else if (event.key.code == sf::Keyboard::Down) {
                menu.Menu_Operation = 2;
            } else if (event.key.code == sf::Keyboard::Key::Enter) {
                menu.Menu_Operation = 3;
            }

            if(event.key.code == Key::E) {
                if(editor) {
                    delete editor; editor = nullptr;
                } else {
                    editor = new Editor(this);

                    vec2 pos = player.get_pos();
                    editor->set_pos({roundf(pos.x / 10) * 10, roundf(pos.y / 10) * 10});
                }
            }

        } else if (event.type == sf::Event::KeyReleased) {

            if(editor and !menu.Enabled) {
                editor->key_release(event.key.code);
            }
            else if(!editor) {
                player.key_release(event.key.code);
            }

            if(event.key.code == sf::Keyboard::Up)
                menu.Menu_Operation = 0;
            else if (event.key.code == sf::Keyboard::Down)
                menu.Menu_Operation = 0;
            else if (event.key.code == sf::Keyboard::Key::Enter)
                menu.Menu_Operation = 0;
        }
    }
}


void Game::update(float delta) {

    hud->update(delta);

    if(menu.Enabled){
        menu.update(delta);
    }else if(menu.exit){
        window->close();
    }else{

        // only update the editor if there is an editor

        if(editor) { editor->update(delta); }
        else {
            player.update(delta);
            for(Enemy* enemy: level->get_enemies())
                enemy->update(delta);
        }
    }

    //   obstacle.activateTrap();*/
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

    window->setView(view);//zoom
    window->draw(player);
    window->draw(*level);

    if(editor) { window->draw(*editor); }

    //=========================================================================
    // HUD RENDERING
    //=========================================================================

    window->setView(hud_view);

    window->draw(*hud);

}
