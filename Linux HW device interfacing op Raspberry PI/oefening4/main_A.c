//----------------------------------
// oefening4 : main.h
//----------------------------------
#include "main.h"

//Define the desired baud here. The delay will sort itself out
#define B_BAUD 9600
#define GET_DELAY(b) 1000000/b
#define RPI_PIN "17"

//debugging on or off
#define debug

int main()
{
	//delay calculation
	delay_bit = GET_DELAY(B_BAUD);
	#ifdef debug
	printf("Baud: %ld,delay_bit: %ld\n",B_BAUD,delay_bit);
	#endif

    FILE * file;
    setPin(file, RPI_PIN, "out");
		
    while(1)
    {
        uart_TX("A", file);
    }
	
    fclose(file);
	
	return 0;
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

        	/*
        	 * Omdat de limiet om te tellen maar op 999999999 ligt zal er dus bij 99..99 een rolover gebeuren
        	 * en om de correcte tijd te kunnen wachten moet men dus 1 seconde (1000000000) erbij moeten tellen
        	 * omdat de teller terug naar 0 gaat!
        	 *
        	 */
            t_diff += 1000000000;
			printf("%ld\n",t_diff);
            break;
    }
}

//bron: https://saeedsolutions.blogspot.be/2012/07/pic12f675-software-uart-bit-banging.html
void uart_TX(const char data, FILE * file)
{
    //start bit
    fprintf(file, "%d", 0);
    fflush(file);
    MicroDelay(delay_bit);

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
        MicroDelay(delay_bit);
    }

    //stop bit
    fprintf(file, "%d", 1);
    fflush(file);
    MicroDelay(delay_bit);
}




