
#include "level.h"
#include "platform.h"


void Level::load(string filename) {

    font.loadFromFile(FONT_FILE); // read font

    std::fstream file(filename); // read file

    if(file.good()) {

        PRINT("loading level from \"" + filename + "\"...");
        string line;

        while(std::getline(file, line)) {

            std::stringstream ss;
            ss << line;

            char type;

            // read first character of line to determine object type
            if(ss >> type) {

                switch(type) {
                case 'p': {// platform

                    float x1, y1, x2, y2, width;
                    int type;
                    // try to read the next 6 numbers in the file
                    if(
                        ss >> x1 and ss >> y1 and
                        ss >> x2 and ss >> y2 and
                        ss >> width and ss >> type
                    ) {

                        add_platform({x1, y1}, {x2, y2}, width, type);
                    }
                }
                    break;

                case 'm': {// text

                    float x, y;
                    string message;

                    if(ss >> x and ss >> y) {

                        // collect the rest of the line in a loop
                        string tmp;
                        while(ss >> tmp) {
                            message += tmp + " ";
                        }

                        add_message({x, y}, message);
                    }
                }
                    break;
                case 't': { // region title

                    float x, y;
                    string title;

                    if(ss >> x and ss >> y) {

                        string tmp;
                        while(ss >> tmp) {
                            title += tmp + " ";
                        }

                        vec2 region(x, y);
                        PRINT("    setting title at " + (string)region);
                        titles[{x, y}] = title;
                    }
                }

                case 'c': { // checkpoint

                    // region xy and spawnpoint xy
                    float rx, ry, x, y;

                    if(ss >> rx and ss >> ry and ss >> x and ss >> y) {

                        add_checkpoint({rx, ry}, {x, y});
                    }
                }
                    break;

                case 'e': { // shooter enemy

                    // spawnpoint XY
                    float x, y;

                    if(ss >> x and ss >> y) {

                        add_shooter({x, y});
                        // enemy.set_pos(vec2(x, y));
                        // enemies.push_back(enemy);
                    }
                }

                default:
                    break;
                }
            }
        }

        PRINT("finished loading (" + STR(platforms.size()) + " platforms)");
    }
    else {
        PRINT("could not read \"" + filename + "\" !");
    }
}

void Level::save() {

    std::remove(LEVEL_OUTPUT);

    std::fstream file;

    file.open(LEVEL_OUTPUT, std::fstream::binary | std::fstream::in | std::fstream::out | std::fstream::trunc);

    if(!file.good()) {
        PRINT("failed to save level");
        return;
    }

    for(auto plat: platforms) {
        file << "\np " << plat.a.x << " " << plat.a.y;
        file << " " << plat.b.x << " " << plat.b.y;
        file << " " << plat.thickness << " " << (int)plat.get_type();
    }

    for(auto enemy: enemies) {
        file << "\ne " << enemy->get_pos().x << " " << enemy->get_pos().y;
    }

    for(auto ch: checkpoints) {
        file << "\nc " << ch.first.first << " " << ch.first.second;
        file << " " << ch.second.x << " " << ch.second.y;
    }

    for(auto msg: messages) {
        file << "\nm " << msg.getPosition().x << " " << msg.getPosition().y;
        file << " " << (string)msg.getString();
    }
}


void Level::add_platform(const vec2& a, const vec2& b, float width, int type) {

    platforms.push_back({a, b, width, static_cast<PlatformType>(type)});
}


void Level::add_message(const vec2& pos, string message) {

    sf::Text text;

    text.setFont(this->font);
    text.setPosition(pos);
    text.setCharacterSize(14);
    text.setString(message);

    messages.push_back(std::move(text));
}


void Level::add_checkpoint(const vec2& reg, const vec2& point) {

    PRINT("    adding checkpoint");
    checkpoints[{reg.x, reg.y}] = point;
}


void Level::add_shooter(const vec2& pos) {

    PRINT("    adding enemy");
    Enemy* enemy = new Enemy(game);
    enemy->set_pos(pos);
    enemies.push_back(enemy);
}


void Level::draw(sf::RenderTarget& target, sf::RenderStates states) const {

    for(Platform plat: platforms)
        target.draw(plat, states);

    for(sf::Text msg: messages)
        target.draw(msg, states);

    for(Enemy* enemy: enemies)
        target.draw(*enemy, states);
}


void Level::update(float delta) {

    for(Enemy* enemy: enemies) enemy->update(delta);
}


string Level::get_region_title(const vec2& region) {

    std::pair<int, int> key = {(int)region.x, (int)region.y};

    if(titles.find(key) == titles.end()) {
        return (string)region + " ???";
    }
    else {
        return titles[key];
    }
}

const vec2& Level::get_checkpoint(const vec2& region) {

    std::pair<int, int> key = {(int)region.x, (int)region.y};

    if(checkpoints.find(key) == checkpoints.end()) {
        return vec2::ZERO;
    }
    else {
        return checkpoints[key];
    }
}