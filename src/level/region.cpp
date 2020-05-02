
#include <math.h>
#include "level/region.h"


LevelRegion::LevelRegion(Player *player, sf::View *view)
: player(player)
, view(view)
{
    const vec2 &pos = player->get_pos();

    vec2 offset(REGION_WIDTH/2, REGION_HEIGHT/2);

    coords = vec2(
        floorf((pos.x + offset.x) / REGION_WIDTH),
        floorf((pos.y + offset.y) / REGION_HEIGHT)
    );


    // define the bounds of the region

    min = vec2(coords.x * REGION_WIDTH, coords.y * REGION_HEIGHT) - offset;
    max = vec2((coords.x+1) * REGION_WIDTH, (coords.y+1) * REGION_HEIGHT) - offset;

    // define the bounds of the camera

    vmin = min + vec2(WIDTH/2, HEIGHT/2);
    vmax = max - vec2(WIDTH/2, HEIGHT/2);

    PRINT("entered region" << (string)coords << ": " << (string)min << " to " << (string)max);
}


bool LevelRegion::is_inside(void) {

    const vec2 &pos = player->get_pos();

    if(
        pos.x >= min.x and pos.y >= min.y and
        pos.x <= max.x and pos.y <= max.y
    )
    {
        return true;
    }
    return false;
}


void LevelRegion::update_view(float delta) {

    const vec2 &pos = player->get_pos();

    // clamp center of camera to camera bounds

    float x = fmax(fmin(pos.x, vmax.x), vmin.x);
    float y = fmax(fmin(pos.y, vmax.y), vmin.y);

    view->setCenter(vec2(x, y));
}