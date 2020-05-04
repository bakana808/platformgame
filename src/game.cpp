<<<<<<< Updated upstream
=======
#include "game.h"
#include "player.h"

>>>>>>> Stashed changes

#include "game.h"
Game::Game()
: view({0.f, 0.f}, {WIDTH, HEIGHT})
, hud({0.f, 0.f}, {WIDTH, HEIGHT})
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
    while (window->pollEvent(event)) {
        if (event.type == sf::Event::Closed) {
            window->close();
        } else if (event.type == sf::Event::KeyPressed) {
            player.key_press(event.key.code);
            if (event.key.code == sf::Keyboard::Escape) {
                window->close();
            } else if (event.key.code == sf::Keyboard::Up) {
                menu.Menu_Operation = 1;
            } else if (event.key.code == sf::Keyboard::Down) {
                menu.Menu_Operation = 2;
            } else if (event.key.code == sf::Keyboard::Enter) {
                menu.Menu_Operation = 3;
            }
        } else if (event.type == sf::Event::KeyReleased) {
            player.key_release(event.key.code);
            if(event.key.code == sf::Keyboard::Up)
                menu.Menu_Operation = 0;
            else if (event.key.code == sf::Keyboard::Down)
                menu.Menu_Operation = 0;
            else if (event.key.code == sf::Keyboard::Enter)
                menu.Menu_Operation = 0;
        }
    }
}


void Game::update(float delta) {
<<<<<<< Updated upstream
    if(menu.Enabled){
        menu.update();
    }else if(menu.exit){
        window->close();
    }else{
        player.update(delta);
    }
=======
    player.update(delta);
 	
 //   obstacle.activateTrap();*/
>>>>>>> Stashed changes
}

void Game::render() {
    window->clear({20, 20, 50});
    if(menu.Enabled){
        window->draw(menu);

    }else if(!menu.exit){
    //=========================================================================
    // WORLD RENDERING
    //=========================================================================
	
    window->setView(view);//zoom
    window->draw(player);
    window->draw(level);
    window->draw(enemy);
    

    //=========================================================================
    // HUD RENDERING
    //=========================================================================

    window->setView(hud);
    player.draw_hud(*window);
    enemy.draw_hud(*window);

    }


    window->display();
}
