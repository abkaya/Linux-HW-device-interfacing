//----------------------------------
// oefening3 : main.h
//----------------------------------
#include "main.h"

#define RPI_PIN "17"

int main(void)
{
    FILE *file;
	/*
	file = fopen("/sys/class/gpio/gpio17/direction", "w");
    fprintf(file, "%s", "out");
    fclose(file);
    file = fopen("/sys/class/gpio/gpio17/value", "w");
	*/
	setPin(file, RPI_PIN, "out");
    int wave_state;
    wave_state =0;
    //Create square wave with 10kHz frequency -- results in a logic level change every 50us
    createSqWave(file, 10000);
    return 0;
}

void createSqWave(FILE *file, int freq)
{
int wave_state;
    wave_state=0;
    int delayTime;
	// 1000000 µs = 1 second.
    delayTime=(1000000/(freq*2));

    while(1)
    {
        if (wave_state==0)
        {
            wave_state=1;
        }
        else if(wave_state==1)
        {
            wave_state=0;
        }
        fprintf(file, "%d", wave_state);
        fflush(file);
        MicroDelay(delayTime);
    }
}

void MicroDelay(long delay_us)
{	
    // Getting the clock time, with option CLOCK_REALTIME
    // Assign a start time in nanoseconds
    clock_gettime(CLOCK_REALTIME, &t_now);
    t_start = t_now.tv_nsec;
    while (1) {
        clock_gettime(CLOCK_REALTIME, &t_now);
        t_diff = t_now.tv_nsec - t_start;
        if (t_diff < 0)
            // Take the roll over into consideration, so we can properly have
            // µs delays of up to 1 second. We do this by adding a second as soon
            // as a rollover is detected.
            t_diff += 1000000000;
			printf("%ld\n",t_diff);
            break;
    }
}

//Function with parameter file, it put the correct values for the GPIO pins
void setPin(FILE * file, char *pinNum, char *inOut)
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
}

