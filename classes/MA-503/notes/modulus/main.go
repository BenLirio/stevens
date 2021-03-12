package main

import (
	"fmt"
)

/*
Algorightm (Euclidean Algorithm) - Solves ax = 1 ( mod b )
*/
func EuclideanAlgorithm(a, b int) (x, y, d int) {
	large := a
	largeIdx := 0
	small := b
	smallIdx := 1
	left := large + small
	prevMultipliers := []int{1,1}
	var multipliers [2]int
	for {
		if small == 0 {
			break
		}
		q := large/small
		r := large%small
		left = r
		multipliers[smallIdx] = -q
		multipliers[largeIdx] = 1
		large = small
		small = r
	}
	return multipliers[0], multipliers[1], left
}
func main() {
	a := 13
	b := 5
	x, y, d := EuclideanAlgorithm(a, b)
	fmt.Printf("(%d)(%d) + (%d)(%d) = %d\n", a, x, b, y, d)
}
