#include <SFML/Graphics.hpp>
#include "frame_clock.h"
#include <cmath>
#include <vector>
#include "common.h"
#include "player.h"
#include "platform.h"
#include "level.h"

class Game {
    public:
        Game(const Game&) = delete;
        Game& operator=(const Game&) = delete;
        Game();
        void run();
    private:
        void processEvents();
        void update();
        void render();
        sf::RenderWindow window;
        sf::ContextSettings settings;
        FrameClock fc;
        sf::View view;
        sf::View hud;
        Level level;
        Player player;
};