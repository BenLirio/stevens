package main

import (
	"../unit"
	"fmt"
)


func main() {
	alicePrivate := unit.NewUnit()
	bobPrivate := unit.NewUnit()

	publicVal := unit.NewUnit()
	publicMod := unit.NewUnit()

	aliceComputed := unit.Mix(publicVal, alicePrivate, publicMod)
	bobComputed := unit.Mix(publicVal, bobPrivate, publicMod)

	aliceSymetricKey := unit.Mix(bobComputed, alicePrivate, publicMod)
	bobSymetricKey := unit.Mix(aliceComputed, bobPrivate, publicMod)

	fmt.Println("ALICE:")
	fmt.Printf("Private: %v\nComputed: %v\nSymetricKey%v\n", alicePrivate, aliceComputed, aliceSymetricKey)
	fmt.Println()
	fmt.Println("BOB:")
	fmt.Printf("Private: %v\nComputed: %v\nSymetricKey:%v\n", bobPrivate, bobComputed, bobSymetricKey)
	fmt.Println()
	fmt.Println("PUBLIC:")
	fmt.Printf("Val: %v\nMod:%v\n", publicVal, publicMod)
}
