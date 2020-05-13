
#include "kyo/common.h"
#include "kyo/entity/object.h"


class Particle: public GameObject<sf::RectangleShape> {
private:

    float size;

public:

    Particle(float size = 50.f): size(size) {

        handle->setSize({size, size});
        handle->setOrigin({size/2, size/2});
        handle->setFillColor({255, 255, 255, 100});
    }

    void update(float delta) {

        size -= delta * 100;

        if(size > 0) {

            handle->setSize({size, size});
            handle->setOrigin({size/2, size/2});
            handle->rotate(delta * 300);
        }
        else {

            this->destroy();
        }
    }
};