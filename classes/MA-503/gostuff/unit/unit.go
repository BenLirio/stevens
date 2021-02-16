package unit

import (
	"math/rand"
)

var MAX_PRIME uint64 = 1000
var SEED int64 = 0

type Unit struct {
	val uint64
	factors []uint64
}

func NewPrimesGenerator(primeMax uint64, seed int64) func() uint64 {
	rand.Seed(seed)
	options := make([]bool, primeMax)
	for i := 0; i < len(options); i++ {
		options[i] = true
	}
	for i := 2; i < len(options); i++ {
		j := 2
		for {
			num := i*j
			if num < len(options) {
				options[num] = false
				j = j + 1
				continue
			}
			break
		}
	}
	var primes []uint64
	for i := 0; i < len(options); i++ {
		if options[i] == true {
			primes = append(primes, uint64(i))
		}
	}
	return func() uint64 {
		return primes[rand.Intn(len(primes))]
	}
}
var primesGenerator func() uint64 = NewPrimesGenerator(MAX_PRIME, SEED)


func NewUnit() *Unit {
	unit := new(Unit)
	unit.val = primesGenerator()
	unit.factors = append(unit.factors, unit.val)
	return unit
}

func Combine(a *Unit, b *Unit) *Unit {
	c := new(Unit)
	c.val = a.val * b.val
	return c
}

func Mix(u1 *Unit, u2 *Unit, u3 *Unit) *Unit {
	var a, b, n, r, i uint64
	a = u1.val
	b = u2.val
	n = u3.val

	r = a % n
	for i = 1; i < b; i++ {
		r = (r * a) % n
	}
	d := new(Unit)
	d.val = r
	return d
}

func (unit *Unit) UnitOf(of *Unit) bool {
	if of.val % unit.val == 0 { return true }
	return false
}
