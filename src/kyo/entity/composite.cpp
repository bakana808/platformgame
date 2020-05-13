
#include "kyo/entity/composite.h"


void CompositeEntity::delete_entity(Entity* ent) {

    Iter it = std::find(entities.begin(), entities.end(), ent);

    if(it != entities.end()) delete_entity(it);
}


CompositeEntity::Iter CompositeEntity::delete_entity(Iter it) {

    float count = entities.size();

    PRINT(get_name() << ": deleting sub-ent " << *it << " (" << (*it)->get_name() << ")");

    delete *it;

    auto new_it = entities.erase(it);

    PRINT(get_name() << ": sub-ents reduced from " << count << " -> " << entities.size());
    return new_it;
}


int CompositeEntity::entity_count() {

    return entities.size();
}


int CompositeEntity::entity_count_rec() {

    int count = 0;

    for(Entity* ent: entities) {

        if(CompositeEntity* comp = dynamic_cast<CompositeEntity*>(ent)) {

            count += comp->entity_count_rec();
        }
    }

    return count + entity_count();
}

void CompositeEntity::draw(sf::RenderTarget& target, sf::RenderStates states) const {

    auto it = entities.begin();
    while(it != entities.end()) {

        target.draw(**it, states);

        it++;
    }
}

void CompositeEntity::update(float delta) {

    for(auto it = entities.begin(); it != entities.end();) {

        // PRINT(get_name() << ": updating sub-ent " << *it);
        // PRINT("EM: updating entity");
        Entity* ptr = *it;
        ptr->update(delta);

        if(ptr->is_deleted())
            it = delete_entity(it);
        else
            it++;
    }

}


void CompositeEntity::set_pos(const vec2& pos) {

    this->pos = pos;
}

/**
 * @brief Get the position of this entity.
 *
 * @return const vec2&
 */
const vec2& CompositeEntity::get_pos(void) {

    return this->pos;
}

/**
 * @brief Translate the position by a vector.
 *
 * @param translation
 */
void CompositeEntity::move(const vec2& translation) {

    set_pos(this->pos + translation);
}