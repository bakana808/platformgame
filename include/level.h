
#include "common.h"
#include "vector/vec2.h"
#include "platform.h"
#include <fstream>
#include <sstream>

#define FONT_FILE "FiraCode-VF.ttf"


class Level: public sf::Drawable {
private:

    sf::Font font;

    std::vector<Platform> platforms;
    std::vector<sf::Text> messages;

public:

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

                        int x1, y1, x2, y2, width, type;
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

                        // std::noskipws allows for spaces in message
                        if(ss >> x and ss >> y) {

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

    std::vector<Platform>& get_platforms() { return platforms; }
};