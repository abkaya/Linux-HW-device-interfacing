//------------------------
// testDelay.c :Tests the delay function MicroDelay(long delay_ms)
//------------------------

#include <time.h>
#include <stdio.h>

#define B_BAUD 9600
#define GET_DELAY(b) 1000000/b

int main(void)
{
	long delay_us=GET_DELAY(B_BAUD);
	printf("%ld,%ld\n",B_BAUD,delay_us);

	return 0;
}
