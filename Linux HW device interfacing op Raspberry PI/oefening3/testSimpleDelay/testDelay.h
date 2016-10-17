#ifndef TESTDELAY_H
#define TESTDELAY_H

#include <time.h>
#include <stdio.h>

long t_start;
long t_diff;
struct timespec t_now;

/**
 * \brief Delay for a given amount of µs of up to 1 second.
 * \param delay_u :The time to delay, passed in µs.
*/
void MicroDelay(long delay_us);
#endif
