
#pragma once

#include "common.h"

/**
 * @brief A drawable and updatable object.
 *
 */
class ScriptableObject: public sf::Drawable {
public:

    /**
     * @brief Draw this entity.
     */
    virtual void draw(sf::RenderTarget&, sf::RenderStates) const = 0;

    /**
     * @brief Process a time step for this entity.
     *
     * @param delta the change in time from the last frame
     */
    virtual void update(float delta) = 0;
};


/**
 * @brief A drawable and updatable object with a position.
 *
 */
class Entity: public ScriptableObject {
private:

    bool b_is_deleted = false;

    string name;

public:

    Entity(): name(game::demangle(typeid(this).name())) {}

    /**
     * @brief Sets the position of this entity.
     */
    virtual void set_pos(const vec2&) = 0;

    /**
     * @brief Gets the position of this entity.
     *
     * @return const vec2&
     */
    virtual const vec2& get_pos() = 0;

    /**
     * @brief Return the name of this entity as a string.
     *
     * Used for debugging purposes.
     *
     */
    string get_name() { return name; }

    void set_name(string name) { this->name = name; }

    /**
     * @brief Return if this Entity is to be deleted.
     *
     * @return true
     * @return false
     */
    bool is_deleted() { return b_is_deleted; }

    void destroy() { b_is_deleted = true; }
};
