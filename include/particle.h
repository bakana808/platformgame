
#include "common.h"
#include "entity.h"


class Particle: public GameObject<sf::RectangleShape> {
private:

    float size;

public:

    Particle(CompositeEntity* source, float size = 50.f)
    : GameObject(std::unique_ptr<sf::RectangleShape>(new sf::RectangleShape()), source)
    , size(size)
    {
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