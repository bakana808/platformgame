
#pragma once

#include <SFML/Graphics.hpp>
#include <cmath>

#define FRAME_SAMPLES 100

/**
 * @brief Keeps track of delta time between frames.
 *
 */
class FrameClock {
private:
    static const int size = FRAME_SAMPLES;

    sf::Clock clock;
    float frame_deltas[FRAME_SAMPLES] = {};
    int idx = 0;

    /**
     * @brief False when not ready to average all elements in frame_deltas[].
     * This happens if the array has not been completely filled yet.
     */
    bool ready = false;

    float* last_frame;

    /**
     * @brief Upper limit of delta time (dt). The read value of get_delta()
     * will be only equal or less than this value.
     */
    float upper_dt;

    float get_average_delta();

public:

    FrameClock(float upper_dt = (1.0 / 144.0)): upper_dt(upper_dt) {
        clock.restart();
    }

    float get_delta() {
        return fmin(upper_dt, frame_deltas[0]);
    }

    int get_average_fps() {

        if( !ready ) {
            return 0;
        }
        else {
            return (int)(1 / get_average_delta());
        }
    }

    void push_frame();
};

float FrameClock::get_average_delta() {

    float deltas = 0;
    for(int i = 0; i < size; i++) {
        deltas += frame_deltas[i];
    }
    return deltas / size;
}

void FrameClock::push_frame() {

    float delta_time = clock.getElapsedTime().asSeconds();

    if( idx == size - 1 ) ready = true;

    frame_deltas[idx] = delta_time;  // update delta at this index
    idx = (idx + 1) % size; // increment index or wrap around to 0

    clock.restart();
}