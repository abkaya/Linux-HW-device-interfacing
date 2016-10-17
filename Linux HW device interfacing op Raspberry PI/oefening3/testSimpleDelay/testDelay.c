//------------------------
// testDelay.c :Tests the delay function MicroDelay(long delay_ms)
//------------------------

#include "testDelay.h"

int main(void)
{
    MicroDelay(700000);

    return 0;
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
        printf("%ld\n", t_diff);
        if (t_diff > delay_us * 1000)
            break;
    }
}
