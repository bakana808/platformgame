
#pragma once

#include "common.h"
#include "vector/vec2.h"
#include "entity/composite.h"
#include "enemy.h"

#include <fstream>
#include <sstream>
#include <map>

#define FONT_FILE "FiraCode-VF.ttf"
#define LEVEL_OUTPUT "level_out.txt"


class Game;
class Enemy;
class Platform;


class Level: public CompositeEntity {
private:

    Game* game;
    sf::Font font;

public:

    std::vector<Enemy*> enemies;
    std::vector<Platform*> platforms;
    std::vector<sf::Text*> messages;
    std::map<std::pair<int, int>, string> titles;
    std::map<std::pair<int, int>, vec2> checkpoints;

    Level(Game* game): game(game) {

        set_name("Level");
    }

    /**
     * @brief Load a level from a file.
     *
     * @param filename
     */
    void load(string filename);

    /**
     * @brief Save the level into a file.
     *
     */
    void save();

    void set_pos(const vec2& pos) override {}

    const vec2& get_pos() override { return vec2::ZERO; }

    void add_platform(const vec2& a, const vec2& b, float width, int type);

    void add_message(const vec2& pos, string message);

    void add_checkpoint(const vec2& reg, const vec2& point);

    void add_shooter(const vec2& pos);

    string get_region_title(const vec2& region);

    const vec2& get_checkpoint(const vec2& region);

    std::vector<Platform*>& get_platforms() { return platforms; }

    std::vector<Enemy*>& get_enemies() { return enemies; }
};
