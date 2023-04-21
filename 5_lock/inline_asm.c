#include <stdio.h>

int xchg(volatile int *addr, int newval)
{
    int result;
    asm volatile("lock xchg %0, %1" // 加不加lock都一样
                 : "+m"(*addr), "=a"(result)
                 : "1"(newval));
    return result;
}

int main()
{
    // int a = 10, b;
    // asm volatile("movl %1, %%eax; movl %% eax, %0;"
    //              : "=r"(b) /* output */
    //              : "r"(a)  /* input */
    //              : "%eax"  /* clobbered register */
    // );
    // printf("test\n");

    int a = 3, b = 5;
    int c = xchg(&a, b);
    printf("a=%d, b=%d, c=%d\n", a, b, c);
}