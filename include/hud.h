
#include <map>

#include "common.h"
#include "entity.h"
#include "game.h"

using std::map;


class HUD: public Entity {
private:

    Game *const game;

    sf::Font font;
    map<string, sf::Text*> elements;

public:

    HUD(Game* game);

    ~HUD();

    /**
     * @brief Create a text object at the specified position under a given ID.
     *
     * @param id
     * @param pos
     * @return sf::Text*
     */
    sf::Text* add_elm(string id, const vec2& pos, int size = 14);

    /**
     * @brief Set the text of an element.
     *
     * @param id
     * @param text
     */
    void set_elm(string id, string text);


    void draw(sf::RenderTarget&, sf::RenderStates) const override;

    void set_pos(const vec2&) override;

    const vec2& get_pos() override;

    void update(float delta) override;
};