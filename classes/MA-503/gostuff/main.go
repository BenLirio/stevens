package main

import (
	"fmt"
)

type Num struct {
	val int
}

func (num *Num) isPrime() bool {
	for i := 2; i < num.val; i++ {
		if num.val % i == 0 { return false }
	}
	return true
}

func add(n1 *Num, n2 *Num) *Num {
	return &Num{n1.val + n2.val}
}

func min(n1 *Num, n2 *Num) *Num {
	if n1.val < n2.val { return &Num{n1.val} }
	return &Num{n2.val}
}

func divides(n1 *Num, n2 *Num) bool {
	return (n2.val % n1.val) == 0
}

func gcf(n1 *Num, n2 *Num) *Num {
	start := min(n1, n2)
	for i := start.val; i > 0; i-- {
		if divides(&Num{i}, n1) && divides(&Num{i}, n2) {
			return &Num{i}
		}
	}
	return &Num{1}
}

func main() {
	n1 := &Num{10}
	n2 := &Num{15}
	fmt.Println(gcf(n1, n2))
}
