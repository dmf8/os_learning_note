#include <stdlib.h>

int main()
{
    int *ptr = malloc(sizeof(int));
    *ptr = 1;
    free(ptr);
    *ptr = 2;
    return 0;
}