#include <stdio.h>
#include <wiringPiI2C.h>

int main(void)
{
	int fd, hightemp, lowtemp;
	fd = wiringPiI2CSetup(0x4f);

	hightemp = wiringPiI2CReadReg8(fd, 0x00);
	fprintf("%d", hightemp);


	return 0;
}
