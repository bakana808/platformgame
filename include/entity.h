
#pragma once

#include "common.h"
#include "vector/vec2.h"


/**
 * @brief A drawable object.
 *
 */
class Entity: public sf::Drawable {
public:


    /**
     * @brief Draw this entity.
     */
    virtual void draw(sf::RenderTarget&, sf::RenderStates) const = 0;


    /**
     * @brief Sets the position of this entity.
     */
    virtual void set_pos(const vec2&) = 0;
};


/**
 * @brief An object that is drawable and has a transform.
 * Serves as a wrapper for sf::Shape, sf::Sprite, and sf::Text objects.
 *
 */
template<class DT>
class GameObject: public Entity {
public:

    sf::Drawable * drawable;
    sf::Transformable * transformable;

    // DT => short for Drawable-Transformable
    template<typename... Args>
    GameObject(DT& parent) {

        // compile-time asserts to ensure that the
        // parent object inherits from these types.
        static_assert(std::is_base_of<sf::Drawable, DT>::value, "Given object not a drawable");
        static_assert(std::is_base_of<sf::Transformable, DT>::value, "Given object not a transformable");

        drawable = (sf::Drawable*)(&parent);
        transformable = (sf::Transformable*)(&parent);
    }

    void draw(sf::RenderTarget& target, sf::RenderStates states) const override {
        target.draw(*drawable, states);
    }

    void set_pos(const vec2& pos) override {
        transformable->setPosition(pos);
    }

    const vec2& get_pos(void) { return transformable->getPosition(); }
};


/**
 * @brief A drawable object that is made up of multiple entities.
 *
 */
class CompositeEntity: public Entity {
private:

    // position of entities within will mirror parent
    std::vector<Entity*> bound_children;

    // position of entities within are independant of parent
    std::vector<Entity*> free_children;

    vec2 pos;

public:

    CompositeEntity() {}

    ~CompositeEntity() {

        for(Entity* child: bound_children)
            delete child;

        for(Entity* child: free_children)
            delete child;

        bound_children.clear();
        free_children.clear();
    }


    /**
     * @brief Add a sub-entity to this entity.
     *
     * @param child the child to add
     */
    void add_child(Entity& child) {

        this->bound_children.push_back(&child);
        child.set_pos(pos);
    }

    /**
     * @brief Add a free sub-entity to this entity.
     *
     * @param child the child to add
     */
    void add_child_free(Entity& child) {

        this->free_children.push_back(&child);
    }


    template<class DT, typename... Args>
    void add_child(DT& obj) {

        GameObject<DT> *ent = new GameObject<DT>(obj);
        PRINT("created wrapper for drawable-transformable");
        this->add_child(*(Entity*)ent);
        PRINT("wrapper for drawable-transformable");
    }

    template<class DT>
    void add_child_free(DT& obj) {

        GameObject<DT> *ent = new GameObject<DT>(obj);
        PRINT("created wrapper for drawable-transformable");
        this->add_child_free(*(Entity*)ent);
    }


    /**
     * @brief Get the vector of child entities. Read-only.
     *
     * @return const std::vector<Entity*>&
     */
    const std::vector<Entity*>& get_children(void) { return bound_children; }


    /**
     * @brief Draws all child entities.
     *
     * @param target
     * @param states
     */
    void draw(sf::RenderTarget& target, sf::RenderStates states) const override {

        for(const Entity* child: bound_children)
            target.draw(*child, states);

        for(const Entity* child: free_children)
            target.draw(*child, states);
    }


    /**
     * @brief Set the position to a vector.
     *
     * @param pos
     */
    void set_pos(const vec2& pos) override {

        this->pos = pos;

        for(Entity* child: bound_children)
            child->set_pos(pos);
    }


    const vec2& get_pos(void) {

        return this->pos;
    }


    /**
     * @brief Translate the position by a vector.
     *
     * @param translation
     */
    void move(const vec2& translation) {

        this->pos += translation;

        for(Entity* child: bound_children)
            child->set_pos(pos);
    }

};