#ifndef MAIN
#define MAIN

#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//baud rate control variables
long delay_bit;

//MicroDelay variables
long t_start;
long t_diff;
struct timespec t_now;

/**
 * \brief Delay for a given amount of µs of up to 1 second.
 * \param delay_u : time to delay, passed in µs.
*/
void MicroDelay(long delay_us);

/**
 * \brief Sets the desired GPIO pin
 * \param file : file pointer passed to method
 * \param pinNum : pin number, defined for the C preprocessor
 * \param inOut : used to set GPIO pin "in" or "out"
*/
void setPin(FILE * file, char *pinNum, char *inOut);

#endif
