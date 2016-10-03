#include <stdio.h>
#include <stdlib.h>


int main(void)
{
    int val;
    val=1;

    FILE * file;

    file = fopen("/sys/class/gpio/gpio17/direction", "w");
    fprintf(file, "%s", "out");
    fclose(file);
    file = fopen("/sys/class/gpio/gpio17/value", "w");


    while(1)
    {
        if (val==0)
        {
            controlLed(file, val);
            val=1;
        }
        else if(val==1)
        {
            controlLed(file, val);
            val=0;
        }
    }

    return 0;
}

void controlLed(FILE *file, int val)
{
    fprintf(file, "%d", val);
    fflush(file);

}



