#include "thread.h"
#include <stdatomic.h>

int x = 0, y = 0;

atomic_int flag;
#define FLAG atomic_load(&flag)
#define FLAG_XOR(val) atomic_fetch_xor(&flag, val)
#define WAIT_FOR(cond) while (!(cond)) ;

__attribute__((noinline))
void write_x_read_y() {
    int y_val;
    asm volatile (
        "movl $1, %0;"
        "movl %2, %1;"
        : "=m"(x), "=r"(y_val) : "m"(y)
    );
    printf("%d ", y_val);
}

__attribute__((noinline))
void write_y_read_x() {
        int x_val;
    asm volatile (
        "movl $1, %0;"
        "movl %2, %1;"
        : "=m"(y), "=r"(x_val) : "m"(x)
    );
    printf("%d ", x_val);
}

void T1(int id) {
    while (1) {
        WAIT_FOR((FLAG & 1));
        write_x_read_y();
        FLAG_XOR(1);
    }
}

void T2(int id) {
    while (1) {
        WAIT_FOR((FLAG & 2));
        write_y_read_x();
        FLAG_XOR(2);
    }
}

void Tsync() {
    while (1) {
        x = y = 0;
        __sync_synchronize(); //full barrier
        //usleep(1);
        assert(FLAG == 0);
        FLAG_XOR(3);
        WAIT_FOR(FLAG == 0);
        printf("\n");
        fflush(stdout);
        
    }
}

int main() {
    create(T1);
    create(T2);
    create(Tsync);
}
