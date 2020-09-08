#ifndef TIMER_HEADER
#define TIMER_HEADER

/* timer.h and timer.c
    A simple interface to get an elapsed time since timerInit().
    The time returned from timerElapsed() is in seconds.
*/

int timerInit();

double timerElapsed();

#endif

