package main

// #cgo LDFLAGS: -Llib -lfib -Wl,-rpath='$ORIGIN/lib'
// unsigned long long fib(int n);
import "C"

import (
	"fmt"
	"os"
	"strconv"
)

func main() {
	nn, _ := strconv.Atoi(os.Args[1])
	n := C.int(nn)
	fmt.Printf("fib(%v): %v\n", n, C.fib(n))
}
