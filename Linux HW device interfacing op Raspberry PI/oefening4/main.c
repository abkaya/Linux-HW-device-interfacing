#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// for 9600 baud the period is 104 microseconds. 1/9600 = 1,04*10^-4
// for other baud rates, adjust the period accordingly
#define period 104


//nanosleep function for performing a sleep for a certain amount of time
void nanosleep()
{
    struct timespec delay;
    delay.tv_sec = 0;
    //range 0 - 999999999 (https://stackoverflow.com/questions/7684359/how-to-use-nanosleep-in-c-what-are-tim-tv-sec-and-tim-tv-nsec)
    delay.tv_nsec = period * 1000L;
    nanosleep(&delay, NULL);
}

//Function with parameter file, it put the correct values for the GPIO pins
void setPin(FILE * file)
{
    file = fopen("/sys/class/gpio/gpio17/direction", "w");
    fprintf(file, "%s", "out");
    fclose(file);
    file = fopen("/sys/class/gpio/gpio17/value", "w");
}

//bron: https://saeedsolutions.blogspot.be/2012/07/pic12f675-software-uart-bit-banging.html
void uart_TX(const char data, FILE * file)
{
    //start bit
    fprintf(file, "%d", 0);
    fflush(file);
    nanosleep();

    for (unsigned char i = 0; i < 8; i ++)
    {
        //set pin according to the data value (in binary value)
        //start with LSB
        if ((data>>i)& 0x01)
        {
            fprintf(file, "%d", 1);
            fflush(file);
        }
        else
        {
            fprintf(file, "%d", 0);
            fflush(file);

        }
        nanosleep();
    }

    //stop bit
    fprintf(file, "%d", 1);
    fflush(file);
    nanosleep();
}

int main()
{
    FILE * file;
    setPin(file);
    while(1)
    {
        uart_TX("A", file);
    }
    fclose(file);

}


