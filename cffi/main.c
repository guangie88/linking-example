#include <stdio.h>
#include <stdlib.h>
#include <string.h>

unsigned long long fib(int n);

int main(int argc, char *argv[]) {
	if (argc < 2) exit(1);
	int n = atoi(argv[1]);
	printf("fib(%d): %lld\n", n, fib(n));
	return 0;
}
