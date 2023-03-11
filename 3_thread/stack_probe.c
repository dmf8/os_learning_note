#include "thread.h"

//__thread means thread local variables
__thread char *base, *cur;
__thread int id;

__attribute__((noinline)) void set_cur(void *ptr) {
    cur = ptr;
}

__attribute__((noinline)) char *get_cur() {
    return cur;
}

void stackoverflow(int n) {
    set_cur(&n);
    if (n % 1024 == 0) { //output stack current size for a certain period (every 1024 times of calling)
        int sz = base - get_cur();
        printf("stack size of T%d >= %d KB\n", id, sz / 1024);
    }
    stackoverflow(n + 1);
}

void Tprobe(int tid) {
    id = tid;
    base = (void *)&tid; //this address is close to thread stack beginning
    stackoverflow(0);
}

int main() {
    setbuf(stdout, NULL);
    for (int i = 0; i < 4; ++i) {
        create(Tprobe);
    }
}