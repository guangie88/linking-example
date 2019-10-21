#include <math.h>

unsigned long long fib(int n) {
    // https://en.wikipedia.org/wiki/Fibonacci_number#Computation_by_rounding
    double gr = (1 + sqrt(5)) / 2;
    return round(pow(gr, n) / sqrt(5));
}
