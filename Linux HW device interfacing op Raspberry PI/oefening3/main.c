#include <stdio.h>
#include <time.h>

int main(void)
{
    FILE * file;
    file = fopen("/sys/class/gpio/gpio17/value", "w");
    int val;
    val =0;
    //Create square wave with 10kHz frequency
    createSqWave(file, 1000);
    return 0;
}

void createSqWave(FILE *file, int freq)
{
int val;
    val=0;
    int delayTime;
    delayTime=(1000000000/freq)/2;
    struct timespec ts;
    ts.tv_sec=0;
    ts.tv_nsec=delayTime;


    while(1)
    {
        if (val==0)
        {
            val=1;
        }
        else if(val==1)
        {
            val=0;
        }
        fprintf(file, "%d", val);
        fflush(file);
        nanosleep(&ts,NULL);
    }
}


