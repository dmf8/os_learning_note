#include "thread.h"

unsigned long balance = 100;

void pay_withdraw(int amt) {
    if (balance >= amt) {
        usleep(1); //a little unexpected delay
        balance -= amt;
    }
}

void Tpay(int tid) {
    pay_withdraw(100);
}

int main() {
    create(Tpay);
    create(Tpay);
    join();
    printf("balance = %lu\n", balance);
}