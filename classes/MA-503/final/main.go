package main

import (
	"math"
	"fmt"
)

var m int = 11
var a int = 3
var b int = 4

func mod(v int) int {
	out := int(math.Mod(float64(v), float64(m)))
	if out < 0 {
		out += m
	}
	return out
}

func inv(v int) int {
	for i := 0; i < m; i++ {
		if mod(i*v) == 1 {
			return i
		}
	}
	return -1
}
func pow(b int, p int) int {
	out := 1
	for i := 0; i < p; i++ {
		out *= b
	}
	return out
}

func add(x1 int, y1 int, x2 int, y2 int) (bool, int, int) {
	if (x1 == x2) && (y2 != y1) {
		return true, 0, 0
	}
	if (x1 == x2) && (y1 == 0) && (y2 == 0) {
		return true, 0, 0
	}
	var lambda int
	if (x1 == x2) {
		top := mod(3*pow(x1,2) + a)
		bottom := mod(2*y1)
		lambda = mod(top*inv(bottom))
	} else {
		top := mod(y2 - y1)
		bottom := mod(x2 - x1)
		lambda = mod(top*inv(bottom))
	}
	x3 := mod(pow(lambda, 2)-x1-x2)
	y3 := mod(lambda*(x1-x3) - y1)
	return false, x3, y3
}

func main() {
	gX := 7
	gY := 7
	curX := 7
	curY := 7
	var check bool
	for {
		check, curX, curY = add(curX, curY, gX, gY)
		if check {
			break
		}
		fmt.Println(curX, curY)
	}
}
