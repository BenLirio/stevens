package main

import (
	"fmt"
)

type Expression uint

type Operation func(Expression) Expression

func I(A []Expression, P []Operation) []Expression {
	seen := map[Expression]bool{}
	que := []Expression{}
	out := []Expression{}
	for _, a := range A {
		que = append(que, a)
		seen[a] = true
	}
	for len(que) != 0 {
		cur := que[0]
		que = que[1:]
		for _, p := range P {
			gen := p(cur)
			if _, ok := seen[gen]; ok == false {
				seen[gen] = true
				que = append(que, gen)
			}
		}
	}
	for expression := range seen {
		out = append(out, expression)
	}
	return out
}

func main() {
	A := []Expression{100, 4, 15}
	op1 := func(expression Expression) Expression {
		return expression % 10
	}
	op2 := func(expression Expression) Expression {
		return expression % 7
	}
	P := []Operation{op1, op2}
	W := I(A, P)
	fmt.Println(W)
}
