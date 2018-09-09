/*
 * Timer.h
 *
 *  Created on: 8 sep. 2018
 *      Author: lucio
 */

#ifndef HEADERS_TIMER_H_
#define HEADERS_TIMER_H_

#include <SDL2/SDL.h>

//The timer
class Timer {
    private:
    //The clock time when the timer started
    int startTicks;

    //The ticks stored when the timer was paused
    int pausedTicks;

    //The timer status
    bool paused;
    bool started;

    public:
    //Initializes variables
    Timer();

    //The various clock actions
    void start();
    void stop();
    void pause();
    void unpause();

    //Gets the timer's time
    int get_ticks();

    //Checks the status of the timer
    bool is_started();
    bool is_paused();
};

#endif /* HEADERS_TIMER_H_ */
