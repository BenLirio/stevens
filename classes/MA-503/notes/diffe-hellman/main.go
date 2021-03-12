package main

import (
	"fmt"
)

var g uint64 = 2
var n uint64 = 11
var A uint64
var B uint64

func exp(b uint64, e uint64, n uint64) uint64 {
	var val uint64 = 1
	var i uint64
	for i = 0; i < e; i++ {
		val = (val*b) % n
	}
	return val
}

func alice_gen() {
	fmt.Println("ALICE")
	var a uint64 = 2
	A = exp(g, a, n)
	fmt.Printf("a: %d A: %d\n\n\n", a, A)
}
func bob_gen() {
	fmt.Println("BOB")
	var b uint64 = 5
	B = exp(g, b, n)
	fmt.Printf("b: %d B: %d\n\n\n", b, B)
}
func eve() {
	fmt.Println("EVE")
	fmt.Println("A: ", A)
	fmt.Println("B: ", B)
	var i uint64
	exps := map(uint64, uint64)
	for i = 0; i < n; i++ {
		exps[exp(g, i, n)] = i
	}
}

func main() {
	fmt.Printf("g: %d n: %d\n\n\n", g, n)
	alice_gen()
	bob_gen()
	eve()
}
