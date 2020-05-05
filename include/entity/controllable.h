
#pragma once

#include "entity.h"


class ControllableEntity: public CompositeEntity {
private:

public:

    virtual void key_press(Key key) {};

    virtual void key_hold(Key key) {};

    virtual void key_release(Key key) {};
};