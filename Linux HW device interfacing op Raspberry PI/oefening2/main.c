//----------------------------------
// oefening2 : main.h
//----------------------------------

#include "main.h"

//Defines the GPIO# here, once, rather than at every occurence in the program.
#define RPI_PIN "17"

int main(void)
{
    wave_state=1;
    file=setPin(file, RPI_PIN, "out");

    while(1)
    {
        //bitwise XOR operation to toggle wave_state;
        wave_state ^= 1;
        fprintf(file, "%d", wave_state);
        fflush(file);
    }

    return 0;
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



