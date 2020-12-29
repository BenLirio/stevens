package main

import (
	"fmt"
	"reflect"
)

func main() {
	var i int = 3
	var p *int = &i
	fmt.Println(p, i)

	v := reflect.ValueOf(p)
	fmt.Println(v.Interface())

	v2 := v.Elem()
	fmt.Println(v2.Interface())
}
