
#pragma once

#include "common.h"
#include "entity/controllable.h"

#define EDITOR_GRID 10

class Game;

/**
 * @brief A level editor.
 *
 */
class Editor: public ControllableEntity {
private:

    Game* game;

    sf::Font font;

    sf::CircleShape *cursor;
    sf::Text *info;

    vec2 *plat_a = NULL, *plat_b = NULL;
    int plat_mode = 0;

public:

    Editor(Game* game);

    ~Editor();

    void update(float delta);

    void key_press(Key key);
};