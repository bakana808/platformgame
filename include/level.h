
#include "common.h"
#include "platform.h"
#include <fstream>


class Level: public sf::Drawable {
private:

    std::vector<Platform> platforms;

public:

    Level(string filename) {
        PRINT("loading level from \"" + filename + "\"...");

        std::fstream file(filename);

        int x1, y1, x2, y2, width, type;

        // read the next 6 numbers in the file
        while(file >> x1 and file >> y1 and file >> x2 and file >> y2 and
              file >> width and file >> type)
        {
            platforms.push_back({{x1, y1}, {x2, y2}, width, static_cast<PlatformType>(type)});
        }

        PRINT("finished loading (" + STR(platforms.size()) + " platforms)");
    }

    void draw(sf::RenderTarget& target, sf::RenderStates states) const override {

        for(Platform plat: platforms)
            target.draw(plat, states);
    }

    std::vector<Platform>& get_platforms() { return platforms; }
};