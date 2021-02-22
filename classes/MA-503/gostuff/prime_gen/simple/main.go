package main
import (
	"fmt"
	"math/big"
)

var one *big.Int = big.NewInt(1)

func PollardTest(N *big.Int) (*big.Int, *big.Int, bool) {
	base := big.NewInt(2)
	n := big.NewInt(1)
	L := new(big.Int).SetUint64(1)
	i := 0
	for {
		L.Mul(L, n)
		a := big.NewInt(0).Exp(base, L, N)
		fmt.Println(a)
		n.Add(n, one)
		i = i+1
		if (i>10) { break }
	}
	p := big.NewInt(0)
	q := big.NewInt(0)
	return q, p, true
}



func main() {
	two := big.NewInt(2)
	n := big.NewInt(10001)
	for {
		n.Add(n, two)
		if (n.ProbablyPrime(0)) {
			p, q, found := PollardTest(n)
			if found == true {
				fmt.Println(p, q)
				break
			}
		}
	}
}
