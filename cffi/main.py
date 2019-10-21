#!/usr/bin/env python3
import ctypes, sys

def main():
    nth = int(sys.argv[1])  # nth value of fib
    libfib = ctypes.CDLL("./lib/libfib.so")
    fib = libfib.fib
    print("fib({}): {}".format(nth, fib(nth)))

if __name__ == "__main__":
    main()
