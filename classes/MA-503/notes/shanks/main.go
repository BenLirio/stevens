package main

import (
	"fmt"
	"math/big"
	"math/rand"
)
var millerSeed int = 62

func NextPrime(z *big.Int) *big.Int {
	one := big.NewInt(1)
	for {
		z.Add(z, one)
		if z.ProbablyPrime(millerSeed) {
			return z
		}
	}
}

func getOrder(g *big.Int, P *big.Int) *big.Int {
	one := big.NewInt(1)
	if g.Cmp(one) == 0 {
		return big.NewInt(0)
	}
	e := big.NewInt(1)
	cur := big.NewInt(0).Set(g)
	i := big.NewInt(1)
	for {
		if cur.Cmp(e) == 0 {
			return i
		}
		cur.Mul(cur, g).Mod(cur, P)
		i.Add(i, one)
	}
}

func GetGenerator(P *big.Int) *big.Int {
	g := big.NewInt(2)
	return g
}

func Sqrt(n *big.Int) *big.Int {
	cur := big.NewInt(1)
	one := big.NewInt(1)
	i := big.NewInt(1)
	for {
		if big.NewInt(0).Mul(cur,cur).Cmp(n) > 0 {
			break
		}
		cur.Add(cur, one)
	}
	return i
}

func Shanks(g *big.Int, h *big.Int, P *big.Int) *big.Int {
	N := getOrder(g, P)
	n := Sqrt(N)
	u := big.NewInt(0).ModInverse(g, P)
	u.Exp(u, n, P)
	vals := make(map[string]*big.Int)
	first := big.NewInt(1)
	second := big.NewInt(0).Set(h)
	one := big.NewInt(1)
	i := big.NewInt(1)
	for {
		first.Mul(first, g).Mod(first, P)
		second.Mul(second, u).Mod(second, P)
		if val, ok := vals[first.String()]; ok == true {
			fmt.Println("Term:", first)
			fmt.Println("First:", i)
			fmt.Println("Second:", val)
			x := big.NewInt(0).Mul(val, big.NewInt(2))
			x.Add(x, i)
			return x

		}
		vals[first.String()] = big.NewInt(0).Set(i)
		if val, ok := vals[second.String()]; ok == true {
			fmt.Println("Term:", second)
			fmt.Println("First:", val)
			fmt.Println("Second:", i)
			x := big.NewInt(0).Set(val)
			x.Add(x, big.NewInt(0).Mul(big.NewInt(2), i))
			return x
		}
		vals[second.String()] = big.NewInt(0).Set(i)
		i.Add(i, one)
	}
}


func main() {
	// get a large prime P
	P := big.NewInt(13)
	P = NextPrime(P)
	// get a generator g
	g := GetGenerator(P)
	// choose an abitrary x < |g|
	r := rand.New(rand.NewSource(19))
	x := big.NewInt(0).Rand(r, P)
	// calculate g^x = h
	h := big.NewInt(0).Exp(g, x, P)
	// call shanks with (g, h, P) => h
	shanksX := Shanks(g, h, P)
	fmt.Println("P:", P, "H:", h, "Real X:", x, "Shanks X:", shanksX)
}
