#include "main.h"

int main(void)
{

    //returs the standard linux filehandle. 0x4f is the slave address byte.
    fd=wiringPiI2CSetup(0x4f);

    while(1)
    {
        //Read in the high and low byte from the register.
        //The corresponding low byte should be read after the high byte for accuracy.
        localHBTemp = wiringPiI2CReadReg8(fd, 0x00);
        localLBTemp = wiringPiI2CReadReg8(fd, 0x10);
        remoteHBTemp = wiringPiI2CReadReg8(fd, 0x01);
        remoteLBTemp = wiringPiI2CReadReg8(fd, 0x11);
        //this block looks like and essentially is four "i2cget <addrByte> <pointerRegByte>"s on the scope


        temperature=CalcTemp(localHBTemp,remoteHBTemp,localLBTemp,remoteLBTemp);
        printf("The current temperature is: %f \n",temperature);

        //allows the calculated temperature to be calculated every 300ms -- (loop used to measure EMI for exercise 7)
        MicroDelay(300000);
    }

    return 0;
}


double CalcTemp(int locHB, int remHB, int locLB, int remLB){
    //convert to 'string doubles'
    sprintf(slocTemp,"%d.%d",locHB,locLB);
    sprintf(sremTemp,"%d.%d",remHB,remLB);

    //convert from string to floating point
    locTemp=atof(slocTemp);
    remTemp=atof(sremTemp);

    //return the average of the local and remote temperature
    return ((locTemp+remTemp)/2);

}


//reused custom delay function
void MicroDelay(long delay_us)
{
    // Getting the clock time, with option CLOCK_REALTIME
    // Assign a start time in nanoseconds
    clock_gettime(CLOCK_REALTIME, &t_now);
    t_start = t_now.tv_nsec;
    while (1)
    {
        clock_gettime(CLOCK_REALTIME, &t_now);
        t_diff = t_now.tv_nsec - t_start;
        if (t_diff < 0)
            // Take the roll over into consideration, so we can properly have
            // µs delays of up to 1 second. We do this by adding a second as soon
            // as a rollover is detected.

            t_diff += 1000000000;
        if (t_diff > delay_us * 1000)
            break;
    }
}

