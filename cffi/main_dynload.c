#include <dlfcn.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[]) {
	if (argc < 2) exit(1);
	int n = atoi(argv[1]);

    // This declares fib as function pointer
    unsigned long long (*fib)(int);

    // Open the shared library
    void* lib = dlopen("./lib/libfib.so", RTLD_LAZY);
    if (!lib) { fputs(dlerror(), stderr); exit(2); }

    // Attempt to load the symbol
    fib = dlsym(lib, "fib");
    char* error;
    if ((error = dlerror()) != NULL) { fputs(error, stderr); exit(3); }

    // Use the symbol and close it
	printf("fib(%d): %lld\n", n, fib(n));
    dlclose(lib);

	return 0;
}
