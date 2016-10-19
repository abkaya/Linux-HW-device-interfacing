#ifndef MAIN
#define MAIN

#include <stdio.h>
#include <wiringPiI2C.h>
#include <time.h>
#include <string.h>
#include <stdlib.h>

int fd, localHBTemp, remoteHBTemp, localLBTemp, remoteLBTemp;
double temperature;
double locTemp, remTemp;

char slocTemp[10];
char sremTemp[10];

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
 * \brief Takes in the high and low temp bytes and calculates the average temperature of both the local and remote sensor.
 * \param locHB: the local high byte read from the 0x00 pointer register byte
 * \param remHB: the remote high byte read from the 0x01 pointer register byte
 * \param locLB: the local low byte read from the 0x10 pointer register byte
 * \param remLB: the remote low byte read from the 0x11 pointer register byte
*/
double CalcTemp(int locHB, int remHB, int locLB, int remLB);


#endif
