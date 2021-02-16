package unit

import (
	"testing"
)

func TestUnit(t *testing.T) {
	NewUnit()
}

func TestCombine(t *testing.T) {
	a := NewUnit()
	b := NewUnit()
	c := Combine(a, b)
	if a.val * b.val != c.val {
		t.Errorf("a.val * b.val should be %d, got %d\n", c.val, a.val * b.val)
	}
}

func TestDivides(t *testing.T) {
	a := NewUnit()
	b := NewUnit()
	c := Combine(a, b)
	if a.UnitOf(c) == false {
		t.Errorf("a should be a unit of c")
	}
	if a.UnitOf(b) == true {
		t.Errorf("a should not be a unit of b")
	}
}

func TestMix(t *testing.T) {
	a := NewUnit()
	a.val = 5
	b := NewUnit()
	b.val = 3
	c := NewUnit()
	c.val = 7
	d := Mix(a, b, c)
	if d.val != 6 {
		t.Errorf("5^3 (mod 7) should be 6. got %d\n", d.val)
	}
}

func TestFactorization(t *testing.T) {
	a := NewUnit()
	if len(a.factors) != 1 || a.factors[0] != a.val {
		t.Errorf("A should have 1 factor with val %d, got %d factors with values %v\n", a.val, len(a.factors), a.factors)
	}
	b := NewUnit()
	c := Combine(a, b)
	cHasTwoFactors := len(c.factors) == 2
	if !cHasTwoFactors || 
}
