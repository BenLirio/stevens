package matrix

import (
	"testing"
	"fmt"
	"reflect"
)

func TestNewMatrix(t *testing.T) {
	newMatrixParams := []struct{
		dims []uint64
		dtype reflect.Kind
	}{
		{[]uint64{1,2,3}, reflect.Float64},
		{[]uint64{0}, reflect.Int},
		{[]uint64{1,1,1}, reflect.Float64},
		{[]uint64{0,0,0,0,0,0}, reflect.Int},
		{[]uint64{0,9,0,7,0,2}, reflect.Float64},
		{[]uint64{1,2,3,4,5,6,7,8}, reflect.Int},
	}
	for _, matrixParam := range newMatrixParams {
		NewMatrix(matrixParam.dims, matrixParam.dtype)
	}
}

func TestGetItem(t *testing.T) {
	getItemParams := []struct{
		dims []uint64
		dtype reflect.Kind
		idx []uint64
		valid bool
	}{
		{[]uint64{1,2,3}, reflect.Float64, []uint64{0,1,2}, true},
		{[]uint64{0}, reflect.Int, []uint64{0}, false},
		{[]uint64{1}, reflect.Float64, []uint64{0}, true},
		{[]uint64{2,5,9}, reflect.Int, []uint64{0,0,0}, true},
		{[]uint64{2,5,9,10}, reflect.Int, []uint64{1,2,3}, false},
		{[]uint64{2,5}, reflect.Int, []uint64{1,2,3}, false},
		{[]uint64{2,5}, reflect.Int, []uint64{1}, false},
	}
	for _, itemParam := range getItemParams {
		m := NewMatrix(itemParam.dims, itemParam.dtype)
		if itemParam.valid == false {
			f := func() {
				m.Get(itemParam.idx)
			}
			message := fmt.Sprintf("Index %v on matrix size %v should be invalid\n", itemParam.idx, m.size)
			assertPanic(t, f, message)
		} else {
			m.Get(itemParam.idx)
		}

	}
}
func assertPanic(t *testing.T, f func(), message string) {
	defer func() {
		if r := recover(); r == nil {
			t.Error(message)
		}
	}()
	f()
}

func TestFlattenIdx(t *testing.T) {
	var size Index = []uint64{10, 5, 2}
	var idx Index = []uint64{2, 3, 1}
	flattenedIdx := idx.Flatten(size)
	if flattenedIdx != 2*5*2 + 3*2 + 1 {
		t.Errorf("Expected flatten of 2,3,1 and 10,5,2 to be %d, got %d\n", 2*5*2 + 3*2 + 1, flattenedIdx)
	}
}

func TestSetItem(t *testing.T) {
	size := []uint64{1}
	m := NewMatrix(size, reflect.Int)
	m.Set([]uint64{0}, 1)
	item := m.Get([]uint64{0})
	if item != 1 {
		t.Errorf("Item should be 1, got %v\n", item)
	}
}

