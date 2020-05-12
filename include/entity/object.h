
#pragma once

#include "entity.h"
#include "vector/vec2.h"


/**
 * @brief An object that is drawable and has a transform.
 *
 * Serves as a wrapper for any object that inherits both
 * sf::Drawable and sf::Transformable.
 * (e.g. sf::Shape, sf::Sprite, and sf::Text)
 *
 * This wrapper class was created because SFML lacks an interface that
 * inherits both sf::Drawable and sf::Transformable.
 *
 * By using static_assert and std::is_base_of, the template class DT can be
 * narrowed down to only those that inherit sf::Drawable and sf::Transformable,
 * and should raise a compiler error if it doesn't.
 *
 */
template<class T>
class GameObject: public Entity {
private:

    sf::Drawable * drawable;
    sf::Transformable * transformable;

    vec2 pos;


public:

    T* handle;

    GameObject() {

        this->set_name(game::demangle(typeid(T).name()));

        handle = new T();
        drawable = (sf::Drawable*)handle;
        transformable = (sf::Transformable*)handle;

        pos = transformable->getPosition();
    }

    ~GameObject() {

        PRINT(get_name() << ": destructor called " << this);
        delete handle;
    }

    void draw(sf::RenderTarget& target, sf::RenderStates states) const override {

        target.draw(*drawable, states);
    }

    void set_pos(const vec2& pos) override {

        transformable->setPosition(pos);
        this->pos = pos;
    }

    const vec2& get_pos(void) { return pos; }


    void update(float delta) override {}

    bool operator==(const GameObject& other) {

        return this->handle == other.handle;
    }
};