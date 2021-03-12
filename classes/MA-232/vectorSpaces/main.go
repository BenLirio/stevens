package main

import (
	"fmt"
)

var N int = 23

type element struct {
	id string
	val0 int
	val1 int
}

func Mul(a element, b element) element {
	val0 := (a.val0 * b.val0)%N
	val1 := (a.val1 * b.val1)%N
	c := element{id: string(val0*val1), val0: val0, val1: val1}
	return c
}
func Add(a element, b element) element {
	val0 := (a.val0 + b.val1)%N
	val1 := (a.val1 + b.val0)%N
	c := element{id: string(val0*val1), val0: val0, val1: val1}
	return c
}
func Identity() element {
	return element{id: "1", val0: 1, val1: 1}
}
func NewVal(a int) element {
	return element{id: string(a), val0: a, val1: a+1}
}

func Gen(g element, operator func(element, element) element) []element {
	elementExists := make(map[element]bool)
	elements := []element{}
	cur := Identity()
	for {
		if _, ok := elementExists[cur]; ok {
			break
		} else {
			elements = append(elements, cur)
			elementExists[cur] = true
		}
		cur = operator(g, cur)
	}
	return elements
}

func main() {
	g := NewVal(2)
	G := Gen(g, Add)
	for _, a := range(G) {
		fmt.Println(a.val0, a.val1)
	}
}
