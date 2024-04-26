#include <stdio.h>

int add(int a, int b);
int add(int a, int b) {
    emscripten_sleep(1 * 1000); 
    return a + b;
}
