#include <stdio.h>
#include <stdlib.h>
#include <time.h>

//nanosleep function for performing a sleep for a certain amount of time
void nanosleep()
{
    struct timespec delay;
    delay.tv_sec = 0;
    //1000000 for the 1kHZ puls
    //100000 for the 10kHZ puls
    //range 0 - 999999999 (https://stackoverflow.com/questions/7684359/how-to-use-nanosleep-in-c-what-are-tim-tv-sec-and-tim-tv-nsec)
    delay.tv_nsec = 1000000L;
    nanosleep(&delay, NULL);
}

//this is the alternative function with clock_gettime()
//https://www.cs.rutgers.edu/~pxk/416/notes/c-tutorials/gettime.html
void alternative(long delay)
{
    struct timespec start, end;
    clock_gettime(CLOCK_MONOTONIC, &start);
    do {
        clock_gettime(CLOCK_MONOTONIC, &end);

    }while()
    clock_gettime(CLOCK_MONOTONIC, &end);




}

//Function with parameter file, it put the correct values for the GPIO pins
//PIN 17 zal gebruikt worden
void setPin(FILE * file)
{
    file = fopen("/sys/class/gpio/gpio17/direction", "w");
    fprintf(file, "%s", "out");
    fclose(file);
    file = fopen("/sys/class/gpio/gpio17/value", "w");
}

int main(void)
{
    FILE * file;
    setPin(file);

    //delay in nanoseconds for alternative function
    long delay = 1000000000;

    while(1)
    {
        generate1kHZ(file);
        nanosleep();
    }

    /*    while(1)
        {
            generate10kHZ(file);
            nanosleep();
        }
    */

    fclose(file);
    return 0;
}

//functie die een blokgolf van 1kHZ maakt
//1kHZ => periode = 0.001 sec
void generate1kHZ(FILE * file)
{
    fprintf(file, "%d", 0);
    fflush(file);
    nanosleep();
    fprintf(file, "%d", 1);
    fflush(file);
}

//functie die een blokgolf van 10kHZ maakt
//10kHZ => periode = 0.0001 sec
void generate10kHZ(FILE * file)
{
    fprintf(file, "%d", 0);
    fflush(file);
    nanosleep();
    fprintf(file, "%d", 1);
    fflush(file);
}


