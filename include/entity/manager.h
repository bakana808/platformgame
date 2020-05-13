
#pragma once

#include "entity/composite.h"


class EntityManager: private CompositeEntity {
public:

    EntityManager() {

        this->set_name("Entity");
    }


    using CompositeEntity::Entity;
    using CompositeEntity::Drawable;
    using CompositeEntity::spawn_entity;
    using CompositeEntity::delete_entity;
    using CompositeEntity::draw;
    using CompositeEntity::Drawable::draw;
    using CompositeEntity::update;
    using CompositeEntity::entity_count;
    using CompositeEntity::entity_count_rec;
};
