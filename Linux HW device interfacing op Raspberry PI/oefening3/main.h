#ifndef MAIN
#define MAIN

#include <time.h>
#include <stdio.h>

FILE *file;

long t_start;
long t_diff;
struct timespec t_now;

//used for the nanosleep version of createWave
//struct timespec ts;

//used to deduct the time it took for operations and IO, from the delay time
long t_delta;

/**
* \brief creates a square wave with frequency freq, alternating between logic level every 1s/(freq*2)
* \param file : the gpio pin value file
* \param freq : freq to base the delays on in order to create the wave
*/
void createWave(FILE * file, int freq);

/**
 * \brief Delay for a given amount of µs of up to 1 second.
 * \param delay_u :The time to delay, passed in µs.
*/
void MicroDelay(long delay_us);

/**
 * \brief Sets the desired GPIO pin
 * \param file : file pointer passed to method
 * \param pinNum : pin number, defined for the C preprocessor
 * \param inOut : used to set GPIO pin "in" or "out"
*/
FILE* setPin(FILE * file, char *pinNum, char *inOut);

#endif


