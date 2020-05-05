
#pragma once

#include "common.h"
#include "vector/vec2.h"
#include "enemy.h"

#include <fstream>
#include <sstream>
#include <map>

#define FONT_FILE "FiraCode-VF.ttf"


class Game;
class Enemy;
class Platform;


class Level: public sf::Drawable {
private:

    Game* game;
    sf::Font font;

public:

    std::vector<Enemy*> enemies;
    std::vector<Platform> platforms;
    std::vector<sf::Text> messages;
    std::map<std::pair<int, int>, string> titles;
    std::map<std::pair<int, int>, vec2> checkpoints;

    Level(Game* game): game(game) {}

    ~Level() {
        for(Enemy* e: enemies)
            delete e;
    }
    /**
     * @brief Load a level from a file.
     *
     * @param filename
     */
    void load(string filename);

    void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

    string get_region_title(const vec2& region);

    const vec2& get_checkpoint(const vec2& region);

    std::vector<Platform>& get_platforms() { return platforms; }

    std::vector<Enemy*>& get_enemies() { return enemies; }
};
