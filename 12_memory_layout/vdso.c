#include <stdio.h>
#include <time.h>
#include <unistd.h>
#include <sys/time.h>

double gettime()
{
    struct timeval t;
    gettimeofday(&t, NULL);
    return t.tv_sec + t.tv_usec / 1000000.0;
}

int main()
{
    printf("time stamp %ld\n", time(NULL));
    double st = gettime();
    sleep(1);
    double ed = gettime();
    printf("Time: %.6lfs\n", ed - st);
}