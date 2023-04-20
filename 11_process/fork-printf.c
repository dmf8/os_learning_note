#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>

int main()
{
    for (int i = 0; i < 2; ++i)
    {
        fork();
        printf("hello\n");
    }

    for (int i = 0; i < 2; ++i)
    {
        wait(NULL);
    }
}