#include <emscripten.h>
#include <stdlib.h>
#include <stdio.h>

unsigned int async_call_sleep(unsigned int time)
{
	emscripten_sleep(time * 1000);
	return time;
}

int main()
{
    printf("Hello, World (JSPI!)\n");
    async_call_sleep(3);
    printf("Goodbye, World (JSPI!)\n");
    return 0;
}
