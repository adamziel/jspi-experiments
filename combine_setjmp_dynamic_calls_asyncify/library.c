#include <stdio.h>
#include <emscripten.h>

int add(int a, int b) {
    emscripten_sleep(1000); 
    return a + b;
}
