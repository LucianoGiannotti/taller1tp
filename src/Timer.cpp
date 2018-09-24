#include "Timer.h"

Timer::Timer(){
    this->startTicks = 0;
    this->pausedTicks = 0;
    this->paused = false;
    this->started = false;
}
void Timer::start() {
    this->started = true;
    this->paused = false;
    this->startTicks = SDL_GetTicks();
}

void Timer::stop() {
    this->started = false;
    this->paused = false;
}

void Timer::pause() {
    if (started && !paused) {
        this->paused = true;
        this->pausedTicks = SDL_GetTicks() - this->startTicks;
    }
}

void Timer::unpause() {
    if (this->paused) {
        this->paused = false;
        this->startTicks = SDL_GetTicks() - this->pausedTicks;
        this->pausedTicks = 0;
    }
}

int Timer::get_ticks() {
    if (this->started) {
        if (this->paused) {
            return this->pausedTicks;
        } else {
            return SDL_GetTicks() - this->startTicks;
        }
    }
    return 0;
}

bool Timer::is_started() {
    return this->started;
    }
bool Timer::is_paused() {
    return this->paused;
    }
