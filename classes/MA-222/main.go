package main

import (
	"fmt"
)


func nCr(n int, k int) int {
	combinations := 1
	for i := 1; i <= n; i++ {
		combinations *= i
	}
	for i := 1; i <= k; i++ {
		combinations /= i
	}
	for i := 1; i <= (n-k); i++ {
		combinations /= i
	}
	fmt.Println("combinations: ", combinations)
	return combinations
}

func pow(b float64, e int, scale float64) float64 {
	for i := 0; i < e; i++ {
		scale *= b
	}
	return scale
}

func P(n float64, k float64, p float64) float64 {
	var i float64
	down := []float64{}
	up := []float64{}
	for i = 1; i <= n; i++ {
		up = append(up, i)
	}
	for i = 1; i <= k; i++ {
		down = append(down, 1/i)
	}
	for i = 1; i <= (n-k); i++ {
		down = append(down, 1/i)
	}
	for i = 0; i < k; i++ {
		down = append(down, p)
	}
	for i = 0; i < (n-k); i++ {
		down = append(down, 1-p)
	}
	val := 1.0
	for len(down) > 0 || len(up) > 0 {
		if(len(up) == 0 || (val > 1 && len(down) > 0)) {
			val *= down[0]
			down = down[1:]
		} else {
			val *= up[0]
			up = up[1:]
		}
	}
	return val
}

func bin(n int, p float64) []float64 {
	X := []float64{}
	for i := 0; i <= n; i++ {
		x := P(float64(n), float64(i), p)
		X = append(X, x)
	}
	return X
}

func main() {
	X := bin(50, 0.05)
	sum := 0.0
	for i, x := range(X) {
		sum += x
		fmt.Printf("%d:\t%0.5f\n", i, x)
	}
	fmt.Println("sum:", sum)
}
