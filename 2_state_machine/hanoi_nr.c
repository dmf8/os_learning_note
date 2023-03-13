#include <stdio.h>
#include <assert.h>

typedef struct
{
    int pc, n;
    char from, to, via;
} Frame;

#define call(...)   ({ *(++top) = (Frame){ .pc = 0, __VA_ARGS__};})
#define ret()       ({ top--; })
#define goto(loc)   ({ f->pc = (loc) - 1;})

void hanoi(int n, char from, char to, char via) {
    Frame stk[64], *top = stk - 1;
    call(n, from, to, via);
    for (Frame *f; (f = top) >= stk; f->pc++) {
        switch (f->pc)
        {
        case 0:
            if (f->n == 1) {
                printf("%c -> %c\n", f->from, f->to);
                goto(4);
            }
            break;
        case 1:
            call(f->n - 1, f->from, f->via, f->to);
        case 2: 
            call(1, f->from, f->to, f->via);
        case 3:
            call(f->n - 1, f->via, f->to, f->from);
        case 4:
            ret();
        
        default:
            // assert(0);
            break;
        }
    }
}

int main() {
    hanoi(3, 'A', 'C', 'B');
    return 0;
}