#include <stdio.h>
#include <dlfcn.h>
#include <emscripten.h>
#include <setjmp.h>

extern int add(int a, int b);

jmp_buf buf;
void second() {
    printf("second %d\n", add(1, 4));   // prints
    longjmp(buf,1);      // jumps back to where setjmp was called - making setjmp now return 1
}

void first() {
    printf("first\n");   // does not print
}

int async_extern_add()
{
    if (!setjmp(buf))
        first();    // when setjmp returns 0
    else           // when longjmp jumps back
        printf("main\n");  // prints
    
    return add(4, 5);
}

int main() {
    // Load the dynamic library
    void* libraryHandle = dlopen("./library", RTLD_LAZY);
    if (libraryHandle == NULL) {
        fprintf(stderr, "Failed to load the dynamic library: %s\n", dlerror());
        return 1;
    }

    // Get the function pointer
    typedef int (*AddFunction)(int, int);
    AddFunction dyn_add = (AddFunction)dlsym(libraryHandle, "add");
    if (dyn_add == NULL) {
        fprintf(stderr, "Failed to get the function pointer: %s\n", dlerror());
        dlclose(libraryHandle);
        return 1;
    }

    // Call the function
    int result = dyn_add(3, 4);
    result += async_extern_add();
    printf("Result: %d\n", result);

    // Unload the dynamic library
    dlclose(libraryHandle);

    return 0;
}