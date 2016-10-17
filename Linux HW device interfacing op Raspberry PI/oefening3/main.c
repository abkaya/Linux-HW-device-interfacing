//----------------------------------
// oefening3 : main.h
//----------------------------------
#include "main.h"

//Defines the GPIO# here, once, rather than at every occurence in the program.
#define RPI_PIN "17"
//#define debug

int main(void)
{
    file=setPin(file, RPI_PIN, "out");
    // Create square wave with 10kHz frequency -- results in a logic level change every 50us
    createWave(file, 10000);
    return 0;
}

void createWave(FILE *file, int freq)
{
    int wave_state;
    wave_state=0;
    int delayTime;
    // 1000000 µs = 1 second.
    delayTime=(1000000/(freq*2));

    while(1)
    {
        // part1 of the attempt to diminish operation time delays
        clock_gettime(CLOCK_REALTIME, &t_now);
        t_start = t_now.tv_nsec;

        // This part takes care of the alternating bits
        wave_state = !wave_state;
        fprintf(file, "%d", wave_state);
        fflush(file);

        // part2 of the attempt to diminish operation time delays
        clock_gettime(CLOCK_REALTIME, &t_now);
        t_delta = t_now.tv_nsec - t_start;

        if (t_delta < 0)
            t_delta += 1000000000;

        // The actual resulting/remaining delay
        MicroDelay(delayTime-(t_delta/1000));

        // Compensating the delta delay:
        // For reference: when generating a 10kHz wave, it helps us
        // to go from a 9.3khz(non compensated) to a 9.6kHz(delta compensated) wave.
    }

    //nanosleep alternative
    /*
    ts.tv_sec=0;
    ts.tv_nsec=delayTime*1000;
    while(1){
        wave_state = !wave_state;
        fprintf(file, "%d", wave_state);
        fflush(file);
        nanosleep(&ts,NULL);
    }*/

}

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
#ifdef debug
        printf("%ld\n", t_diff);
#endif
        if (t_diff > delay_us * 1000)
            break;
    }
}

FILE* setPin(FILE * file, char *pinNum, char *inOut)
{
    //paths to the gpio direction and value
    char direction_path[50] = "";
    char value_path[50] = "";

    //concatenate the defined pin number with the path to both the direction and value
    snprintf(direction_path, sizeof(direction_path), "/sys/class/gpio/gpio%s/direction", pinNum);
    snprintf(value_path, sizeof(value_path), "/sys/class/gpio/gpio%s/value", pinNum);

    file = fopen(direction_path, "w");
    fprintf(file, "%s", inOut);
    fclose(file);

    file = fopen(value_path, "w");
#ifdef debug
    printf("Direction path: %s\nValue path: %s\n",direction_path,value_path);
#endif
    return file;
}

