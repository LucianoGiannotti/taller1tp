#ifndef TIMER_H
#define TIMER_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <cstdio>
#include <string>
#include <stdexcept>

//The timer
class Timer
{
    private:
        int startTicks;
        int pausedTicks;
        bool paused;
        bool started;

    public:

        Timer();

        void start();

        void stop();

        void pause();

        void unpause();

        int get_ticks();

        bool is_started();

        bool is_paused();
};

#endif // TIMER_H
