
#include <stdio.h>

__attribute__((constructor)) void hello() {
    printf("Hello, world\n");
}
__attribute__((destructor)) void goodbye() {
    printf("Goodbye, world\n");
}

int main() {
    
}