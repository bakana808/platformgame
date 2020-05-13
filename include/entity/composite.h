
#pragma once

#include "common.h"
#include "entity.h"
#include "entity/object.h"
#include "vector/vec2.h"
#include <vector>
#include <algorithm>


/**
 * @brief Manages all entities in the game.
 *
 */
class CompositeEntity: public Entity {
protected:

    std::vector<Entity*> entities;

    typedef std::vector<Entity*>::iterator Iter;

    vec2 pos;

public:

    ~CompositeEntity() {

        // delete all pointers
        for(auto it = entities.begin(); it != entities.end();) {
            it = delete_entity(it);
        }

        PRINT(get_name() << ": finished deleting. " << entities.size() << " sub-ents remain.");
    }

    /**
     * @brief Add a sub-entity to this entity.
     *
     * @param child the child to add
     */
    template<class T>
    void add_entity(T* ptr) {

        PRINT(get_name() << ": adding sub-ent " << ptr << " (" << ptr->get_name() << ")");

        this->entities.push_back(ptr);
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
    template<class T, typename ...Args>
    T* spawn_entity(Args &&...args) {

        if constexpr (std::is_base_of<Entity, T>()) {

            // T is an Entity -> create an instance and push it
            T *ent = new T(std::forward<Args>(args)...);
            this->add_entity(ent);

            return ent;
        }
        else {

            // Assume T is a SFML object -> create a wrapper and push it
            GameObject<T> *obj = new GameObject<T>();
            this->add_entity(obj);

            return obj->handle;
        }
    }

    /**
     * @brief Removes and deletes a child entity.
     * This will probably crash the program if the child isn't
     * in allocated memory.
     *
     * @param child
     */
    void delete_entity(Entity* ent);

    Iter delete_entity(Iter it);

    /**
     * @brief Return the current amount of entities.
     *
     * @return int
     */
    int entity_count();

    /**
     * @brief Recursively return the sub-entity count and the sub-entity count
     * of any nested composite entities.
     *
     * @return int
     */
    int entity_count_rec();

    void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

    virtual void update(float delta) override;

    //=========================================================================
    // GETTER / SETTERS
    //=========================================================================

    /**
     * @brief Set the position to a vector.
     * This will also set the position of all child entities.
     *
     * @param pos
     */
    virtual void set_pos(const vec2& pos) override;

    /**
     * @brief Get the position of this entity.
     *
     * @return const vec2&
     */
    const vec2& get_pos(void) override;

    /**
     * @brief Translate the position by a vector.
     *
     * @param translation
     */
    void move(const vec2& translation);
};