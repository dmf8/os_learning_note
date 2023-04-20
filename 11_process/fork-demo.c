#include <unistd.h>
#include <stdio.h>

int main()
{
    __pid_t pid1 = fork();
    __pid_t pid2 = fork();
    __pid_t pid3 = fork();
    printf("hello fork (%d %d %d)\n", pid1, pid2, pid3);
}