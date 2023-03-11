#include "thread.h"

#define N 100000000

long sum = 0;

void Tsum(int tid) {
    for (int i = 0; i < N; ++i) {
        sum++;
    }
}

int main() {
    create(Tsum);
    create(Tsum);
    join();
    printf("sum = %lu\n", sum);
}