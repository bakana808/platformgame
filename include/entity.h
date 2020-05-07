
#pragma once

#include <algorithm>
#include <memory>
#include <utility>
#include <map>
#include "common.h"
#include "vector/vec2.h"

using std::pair;
using std::vector;


/**
 * @brief A drawable and updatable object.
 *
 */
class Entity: public sf::Drawable {
private:

    bool b_is_deleted = false;

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

    /**
     * @brief Return if this Entity is to be deleted.
     *
     * @return true
     * @return false
     */
    bool is_deleted() { return b_is_deleted; }

    void destroy() { b_is_deleted = true; }
};


template<typename T>
class GameObject;


/**
 * @brief A drawable object that is made up of multiple entities.
 *
 */
class CompositeEntity: public Entity {
private:

    // if the bool is true, mirror the position of the parent
    std::map<Entity*, bool> children;

    vec2 pos;

public:

    CompositeEntity() {}

    ~CompositeEntity() {

        PRINT("deleting entity");

        // FIXME: deleting these points sometimes crashes the program

        auto it = children.begin();
        while(it != children.end()) {

            it = remove_child(it, "");
        }
    }

    /**
     * @brief Add a sub-entity to this entity.
     *
     * @param child the child to add
     */
    template<class T>
    T* add_child(T* child, bool mirror_pos = true) {

        PRINT("adding child " << child << " (" << typeid(T).name() << ")");

        this->children[child] = mirror_pos;
        if(mirror_pos) child->set_pos(pos);

        return child;
    }

    /**
     * @brief Removes and deletes a child entity.
     * This will probably crash the program if the child isn't
     * in allocated memory.
     *
     * @param child
     */
    template<class T>
    void remove_child(T* child) {

        auto it = children.find(child);
        if(it != children.end()) {
            remove_child(it, typeid(T).name());
        }
    }

    std::map<Entity*, bool>::iterator remove_child(std::map<Entity*, bool>::iterator it, string name) {

        PRINT("removing child " << it->first << " (" << name << ")");

        auto new_it = children.erase(it);

        delete it->first;

        return new_it;
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
    template<class T>
    T* add_child(bool mirror_pos = true) {

        // GameObject<T> *ent = new GameObject<T>(std::unique_ptr<T>(&obj), this);
        GameObject<T> *obj = new GameObject<T>(this);
        this->add_child(obj, mirror_pos);

        return obj->handle;
    }


    /**
     * @brief Draws all child entities.
     *
     * @param target
     * @param states
     */
    void draw(sf::RenderTarget& target, sf::RenderStates states) const override {

        for(auto t: children)
            target.draw(*t.first);
    }


    /**
     * @brief Set the position to a vector.
     * This will also set the position of all child entities.
     *
     * @param pos
     */
    void set_pos(const vec2& pos) override {

        this->pos = pos;

        for(auto t: children)
            if(t.second) t.first->set_pos(pos);
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

        set_pos(this->pos + translation);
    }

    virtual void update(float delta) override {

        // update all child entities

        auto it = children.begin();
        while(it != children.end()) {

            it->first->update(delta);

            if(it->first->is_deleted())
                it = remove_child(it, "");
            else
                it++;
        }
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
 */
template<class T>
class GameObject: public Entity {
private:

    CompositeEntity* source;

    sf::Drawable * drawable;
    sf::Transformable * transformable;

    vec2 pos;

public:

    T* handle;

    GameObject(CompositeEntity* source = nullptr) : source(source) {

        handle = new T();
        drawable = (sf::Drawable*)handle;
        transformable = (sf::Transformable*)handle;

        pos = transformable->getPosition();
    }

    ~GameObject() {

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
