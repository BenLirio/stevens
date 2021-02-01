package matrix

import (
	"fmt"
	"reflect"
	"errors"
)

type Index []uint64
func (idx Index) Count() uint64 {
	var count uint64 = 1
	for _, dim := range idx {
		count *= dim
	}
	return count
}
func (idx Index) Flatten(size Index) uint64 {
	multiplier := size.Count()
	var flattenedIdx uint64 = 0
	for i, dim := range idx {
		multiplier /= size[i]
		flattenedIdx += dim*multiplier
	}
	return flattenedIdx
}

type Matrix struct {
	dtype reflect.Kind
	size Index
	data interface{}
}
func NewMatrix(size Index, dtype reflect.Kind) *Matrix {
	m := &Matrix{
		dtype: dtype,
		size: size,
	}
	switch dtype {
	case reflect.Int:
		m.data = make([]int, size.Count())
	case reflect.Float64:
		m.data = make([]float64, size.Count())
	default:
		panic(errors.New(fmt.Sprintf("Data type %v unknown\n", dtype)))
	}
	return m
}
func (m *Matrix) Get(idx Index) interface{} {
	if len(idx) != len(m.size) {
		panic(fmt.Sprintf("Index %v is invalid on matrix size %v\n", idx, m.size))
	}
	switch m.dtype {
	case reflect.Int:
		return m.data.([]int)[idx.Flatten(m.size)]
	case reflect.Float64:
		return m.data.([]float64)[idx.Flatten(m.size)]
	default:
		panic("Should not be valid dtype")
		return nil
	}
}
func (m *Matrix) Set(idx Index, val interface{}) {
	switch m.dtype {
	case reflect.Int:
		m.data.([]int)[idx.Flatten(m.size)] = val.(int)
	case reflect.Float64:
		m.data.([]float64)[idx.Flatten(m.size)] = val.(float64)
	default:
		panic("Should not be valid dtype")
	}
}
