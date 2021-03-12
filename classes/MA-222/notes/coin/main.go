package main

import (
	"fmt"
	"math/rand"
)

const (
	WIN = 1
	LOSS = 2
	TIE = 3
)

func toss() int {
	r := rand.Intn(32)
	p1 := (r&1) + (r&(1<<1))>>1 + (r&(1<<2))>>2
	p2 := (r&(1<<3))>>3 + (r&(1<<4))>>4
	//fmt.Println(p1, p2)
	if p1 == p2 {
		return TIE
	}
	if p1 > p2 {
		return WIN
	}
	return LOSS
}

func main() {
	p1 := 0
	p2 := 0
	i := 1
	for {
		res := toss()
		if res == WIN {
			p1 += 1
		}
		if res == LOSS {
			p2 += 1
		}
		if i % 910000 == 0 {
			break
		}
		i += 1
	}
	fmt.Println("P1:", float64(p1) / (float64(p2) + float64(p1)))
	fmt.Println("P2:", float64(p2) / (float64(p2) + float64(p1)))
}
