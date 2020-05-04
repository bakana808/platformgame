
#include <cmath>
#include <vector>

#include "frame_clock.h"
#include "common.h"
#include "player.h"
#include "platform.h"
#include "level.h"
<<<<<<< Updated upstream
#include "Menu.h"

=======
#include "enemy.h"
#include "obstacle.hpp"
>>>>>>> Stashed changes

class Game {
public:

    Game(const Game&) = delete;
    Game& operator=(const Game&) = delete;
    Game();
    ~Game();

    void run();

private:

    sf::RenderWindow* window;

    FrameClock fc;

    sf::View view;
    sf::View hud;

    Level level;
    Player player;
<<<<<<< Updated upstream
    Menu menu;
=======
    Enemy enemy;
    Obstacle obstacle;
    
>>>>>>> Stashed changes

    void processEvents();

    /**
     * @brief Process game logic with the given change in time
     * from the last frame.
     *
     * @param delta
     */
    void update(float delta);

    /**
     * @brief Render a frame.
     */
    void render();

};
