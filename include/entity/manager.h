
#include "common.h"
#include "entity.h"
#include <vector>


/**
 * @brief Manages all entities in the game.
 *
 */
class EntityManager: public sf::Drawable {

    std::vector<Entity*> entities;

public:

    ~EntityManager() {

        // delete all pointers
        for(Entity* ent: entities) delete_entity(ent);
    }

    /**
     * @brief Creates an entity.
     *
     * Ownership of the pointer will be passed to this manager.
     *
     * @tparam T
     * @param ent
     * @return T*
     */
    template<class T>
    T* create_entity(T* ent) {

        entities.push_back(ent);
        PRINT("EM: adding \"" << ent->get_name() << "\" (" << ent << ")");

        return ent;
    }

    /**
     * @brief Deletes an entity.
     *
     * @tparam T
     * @param ent
     */
    template<class T>
    void delete_entity(T* ent) {

        auto it = std::find(entities.begin(), entities.end(), ent);
        if(it != entities.end()) {
            entities.erase(it);
            PRINT("EM: deleting \"" << ent->get_name() << "\" (" << ent << ")");
            delete ent;
        }
    }

    /**
     * @brief Return the current amount of entities.
     *
     * @return int
     */
    int entity_count() {

        return entities.size();
    }

    void draw(sf::RenderTarget& target, sf::RenderStates states) const {

        for(Entity* ent: entities) target.draw(*ent, states);
    }

    void update(float delta) {

        for(Entity* ent: entities) {
            // PRINT("EM: updating entity");
            ent->update(delta);
        }
        // PRINT("EM: done updating");
    }
};