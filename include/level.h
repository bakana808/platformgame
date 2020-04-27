
#pragma once

#include "common.h"
#include "vector/vec2.h"
#include "platform.h"
#include <fstream>
#include <sstream>
#include <map>

#define FONT_FILE "FiraCode-VF.ttf"


class Level: public sf::Drawable {
private:

    sf::Font font;

public:

    std::vector<Platform> platforms;
    std::vector<sf::Text> messages;
    std::map<std::pair<int, int>, string> titles;
    std::map<std::pair<int, int>, vec2> checkpoints;

    Level(string filename) {

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

                            platforms.push_back({{x1, y1}, {x2, y2}, width, static_cast<PlatformType>(type)});
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

                            sf::Text text;

                            text.setFont(this->font);
                            text.setPosition(x, y);
                            text.setCharacterSize(14);
                            text.setString(message);

                            messages.push_back(std::move(text));
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

                    case 'c': { // checkpoiont

                        // region xy and spawnpoint xy
                        float rx, ry, x, y;

                        if(ss >> rx and ss >> ry and ss >> x and ss >> y) {

                            PRINT("    adding checkpoint");
                            checkpoints[{rx, ry}] = vec2(x, y);
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

    void draw(sf::RenderTarget& target, sf::RenderStates states) const override {

        for(Platform plat: platforms)
            target.draw(plat, states);

        for(sf::Text msg: messages)
            target.draw(msg, states);
    }

    string get_region_title(const vec2& region) {

        std::pair<int, int> key = {(int)region.x, (int)region.y};

        if(titles.find(key) == titles.end()) {
            return (string)region + " ???";
        }
        else {
            return titles[key];
        }
    }

    const vec2& get_checkpoint(const vec2& region) {

        std::pair<int, int> key = {(int)region.x, (int)region.y};

        if(checkpoints.find(key) == checkpoints.end()) {
            return vec2::ZERO;
        }
        else {
            return checkpoints[key];
        }
    }

    std::vector<Platform>& get_platforms() { return platforms; }
};