#include "kyo/frame_clock.h"
float FrameClock::get_average_delta() {

    float deltas = 0;
    for(int i = 0; i < size; i++) {
        deltas += frame_deltas[i];
    }
    return deltas / size;
}

void FrameClock::push_frame() {

    float delta_time = clock.getElapsedTime().asSeconds();

    last_frame = delta_time;

    if( idx == size - 1 ) ready = true;

    frame_deltas[idx] = delta_time;  // update delta at this index
    idx = (idx + 1) % size; // increment index or wrap around to 0

    clock.restart();
}