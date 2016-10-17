#ifndef MAIN
#define MAIN

#include <time.h>
#include <stdio.h>

FILE *file;

int wave_state;

/**
 * \brief Sets the desired GPIO pin
 * \param file : file pointer passed to method
 * \param pinNum : pin number, defined for the C preprocessor
 * \param inOut : used to set GPIO pin "in" or "out"
*/
FILE* setPin(FILE * file, char *pinNum, char *inOut);

#endif
