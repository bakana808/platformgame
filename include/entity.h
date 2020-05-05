
#pragma once

#include <algorithm>
#include <memory>
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

    /**
     * @brief Gets the position of this entity.
     *
     * @return const vec2&
     */
    virtual const vec2& get_pos() = 0;

    /**
     * @brief Process a time step for this entity.
     *
     * @param delta the change in time from the last frame
     */
    virtual void update(float delta) = 0;
};


template<typename DT>
class GameObject;


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
    void add_child(Entity* child) {

        this->bound_children.push_back(child);
        child->set_pos(pos);
    }

    /**
     * @brief Add a free sub-entity to this entity.
     *
     * @param child the child to add
     */
    void add_child_free(Entity* child) {

        this->free_children.push_back(child);
    }


    /**
     * @brief Removes and deletes a child entity.
     * This will probably crash the program if the child isn't
     * in allocated memory.
     *
     * @param child
     */
    void remove_child(Entity* child) {

        PRINT("removing child " << child);
        {
            std::vector<Entity*>& vec = this->bound_children;
            vec.erase(std::remove(vec.begin(), vec.end(), child), vec.end());
        }
        {
            std::vector<Entity*>& vec = this->free_children;
            vec.erase(std::remove(vec.begin(), vec.end(), child), vec.end());
        }
    }


    /**
     * @brief Add an object that inherits from both
     * sf::Drawable and sf::Transformable.
     *
     * Should produce a compiler error if DT is not a sf::Drawable and
     * sf::Transformable.
     *
     * @tparam DT
     * @param obj
     */
    template<class DT>
    void add_child(DT& obj) {

        GameObject<DT> *ent = new GameObject<DT>(std::unique_ptr<DT>(&obj), this);
        this->add_child((Entity*)ent);
    }


    template<class DT>
    void add_child_free(DT& obj) {

        GameObject<DT> *ent = new GameObject<DT>(std::unique_ptr<DT>(&obj), this);
        this->add_child_free((Entity*)ent);
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
     * This will also set the position of all child entities.
     *
     * @param pos
     */
    void set_pos(const vec2& pos) override {

        this->pos = pos;

        for(Entity* child: bound_children)
            child->set_pos(pos);
    }


    /**
     * @brief Get the position of this entity.
     *
     * @return const vec2&
     */
    const vec2& get_pos(void) override {

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

    virtual void update(float delta) override {

        // update all child entities

        for(Entity* child: bound_children)
            child->update(delta);

        for(Entity* child: free_children)
            child->update(delta);
    }
};


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
 * The term DT is short for Drawable-Transformable.
 */
template<class DT>
class GameObject: public Entity {
private:

    CompositeEntity* source;

    sf::Drawable * drawable;
    sf::Transformable * transformable;

public:

    std::unique_ptr<DT> handle;

    GameObject(std::unique_ptr<DT>&& handle, CompositeEntity* source = nullptr)
    : source(source)
    , handle(std::move(handle))
    , drawable((sf::Drawable*)handle.get())
    , transformable((sf::Transformable*)handle.get())
    {
        // compile-time asserts to ensure that the
        // parent object inherits from these types.
        static_assert(std::is_base_of<sf::Drawable, DT>::value, "Given object not a drawable");
        static_assert(std::is_base_of<sf::Transformable, DT>::value, "Given object not a transformable");
    }

    ~GameObject() {

        destroy();
    }

    void draw(sf::RenderTarget& target, sf::RenderStates states) const override {
        target.draw(*drawable, states);
    }

    void set_pos(const vec2& pos) override {
        transformable->setPosition(pos);
    }

    const vec2& get_pos(void) { return transformable->getPosition(); }


    void update(float delta) override {}

    /**
     * @brief Delete this object. (self-delete)
     *
     */
    void destroy() {

        if(source)
            source->remove_child(this);
    }

    bool operator==(const GameObject& other) {

    }
};
