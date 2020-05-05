
#include "hud.h"
#include <math.h>

#define HUD_DEBUG_POS "debug_pos"
#define HUD_DEBUG_VEL "debug_vel"
#define HUD_DEBUG_COL "debug_col"
#define HUD_DEBUG_REG "debug_reg"

#define HUD_TIMER "timer"

HUD::HUD(Game* game): game(game) {

    // try to load font
    if(!font.loadFromFile("FiraCode-VF.ttf")) {
        PRINT("unable to load font");
    }

    add_elm(HUD_TIMER, {0, 320}, 20);

    // debug text
    add_elm(HUD_DEBUG_POS, {-600, -320});
    add_elm(HUD_DEBUG_VEL, {-600, -320 + 16});
    add_elm(HUD_DEBUG_COL, {-600, -320 + 64});
    add_elm(HUD_DEBUG_REG, { 000, -320});
}


HUD::~HUD() {

    // delete all pointers in map
    for(auto pair: elements)
        delete pair.second;
}


sf::Text* HUD::add_elm(string id, const vec2& pos, int size) {

    sf::Text* elm = new sf::Text();

    elm->setFont(font);
    elm->setCharacterSize(size);
    elm->setColor(sf::Color::White);
    elm->setOrigin(-pos.x, -pos.y);

    elements[id] = elm;

    PRINT("added HUD element @ " + (string)pos + " (id=" + id + ")");
}


void HUD::set_elm(string id, string text) {

    elements[id]->setString(text);
}

void HUD::draw(sf::RenderTarget& target, sf::RenderStates states) const {

    for(auto pair: elements)
        target.draw(*pair.second, states);
}


void HUD::set_pos(const vec2& pos) {

    for(auto pair: elements)
        pair.second->setPosition(pos);
}

const vec2& HUD::get_pos() { return vec2::ZERO; }


void HUD::update(float delta) {

    static double accum = 0;

    accum += delta;

    int ms = (int)floorf(accum * 1000) % 1000;
    int sec = (int)accum % 60;
    int min = floorf(accum / 60);

    set_elm(HUD_TIMER, STR(min) + ":" + STR(sec) + "." + STR(ms));

    Player& player = game->get_player();

    set_elm(HUD_DEBUG_POS, (string)player.get_pos());
    set_elm(HUD_DEBUG_VEL, (string)player.get_vel());

    set_elm(HUD_DEBUG_COL,
        "spinning = " + STR(player.is_spinning()) + "\n"
        "can jump = " + STR(player.can_jump()) + "\n"
        "dashes = " + STR(player.get_num_dashes()) + "\n"
    );
}