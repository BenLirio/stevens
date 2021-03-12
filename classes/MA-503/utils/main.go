package main

import (
	"fmt"
	"math/big"
	"os"
	"strconv"
)

func check(e error) {
	if e != nil {
		panic(e)
	}
}

func main() {
	var err error
	if len(os.Args) < 4 {
		fmt.Println("Usage: ./main [ base ] [ exponent ] [ mod ]");
		return
	}
	b, err := strconv.Atoi(os.Args[1])
	check(err)
	e, err := strconv.Atoi(os.Args[2])
	check(err)
	m, err := strconv.Atoi(os.Args[3])
	check(err)
	base := big.NewInt(int64(b))
	exponent := big.NewInt(int64(e))
	mod := big.NewInt(int64(m))
	out := big.NewInt(0)
	out.Exp(base, exponent, mod)
	fmt.Println(out)
}

