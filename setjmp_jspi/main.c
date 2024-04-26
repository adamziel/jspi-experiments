#include <stdio.h>
#include <setjmp.h>
#include <emscripten.h>

jmp_buf buf;

void second() {
    printf("sleep(2000)\n");   // prints
    emscripten_sleep(2000);
    printf("third\n");   // prints
    longjmp(buf,1);      // jumps back to where setjmp was called - making setjmp now return 1
}

void first() {
    second();
    printf("first\n");   // does not print
}

int main() {
    if (!setjmp(buf))
        first();    // when setjmp returns 0
    else           // when longjmp jumps back
        printf("main\n");  // prints

    return 0;
}
