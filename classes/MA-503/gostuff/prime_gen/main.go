package main

import (
	"math"
	"fmt"
	"math/rand"
)

type num_T= uint64

// Simple Primality test
func SimplePrimalityTest(N num_T) bool {
	return false
}
// Fermat primality test
func FermatPrimalityTest(N num_T) bool {
	return false
}
// Carmichael numbers
func CarmichaelNumbers(N num_T) bool {
	return false
}
// Miller-Rabin primality test. Efficiency.
func MillerRabinPrimalityTest(N num_T) bool {
	return false
}

// Random prime generation
var actualValues map[num_T]num_T = map[num_T]num_T{
	1000: 168,
	10000: 1229,
	100000: 9592,
	1000000: 78498,
}
func Log(N num_T) num_T {
	cur := math.E
	var i num_T= 0
	for cur < float64(N) {
		i += 1
		cur *= math.E
	}
	return i
}
func NumPrimes(N num_T) num_T {
	return N / Log(N)
}
func RandomPrimeGeneration(N num_T) num_T {
	numPrimes := NumPrimes(N)
	primePer := N/numPrimes
	buf := make([]byte, 8)
	for i := 0; i < primePer; i++ {
		rand.Read(buf)
		binary.LittleEndian.Uint64(buf)
	}
	return primePer
}
// Pollard's p-1 method to factor N = pq
func PollardsFactorMethod(N num_T) (num_T, num_T, bool) {
	return 0, 0, false
}
// Factorization of N via difference of squares
func DifferenceOfSquares(N num_T) (num_T, num_T, bool) {
	return 0, 0, false
}
// Pollard's rho algorithm
func PollardsRhoAlgorithm(N num_T) (num_T, num_T, bool) {
	return 0, 0, false
}

func main() {
	fmt.Println(RandomPrimeGeneration(10000000))
}
