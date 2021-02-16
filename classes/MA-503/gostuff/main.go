package main

import (
	"./unit"
	"fmt"
)


func main() {
	a := unit.NewUnit()
	b := unit.NewUnit()
	c := unit.Combine(a, b)
	fmt.Println(c)
}
