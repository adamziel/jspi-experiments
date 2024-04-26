#include <stdio.h>
#include <dlfcn.h>
#include <emscripten.h>

extern int add(int a, int b);
int wasm_sleep(unsigned int time)
{
    emscripten_sleep(time * 1000); // emscripten_sleep takes time in milliseconds
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
    printf("Result: %d\n", result);

    // Unload the dynamic library
    dlclose(libraryHandle);

    return 0;
}