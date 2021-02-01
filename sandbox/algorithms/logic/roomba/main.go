package main

import (
	"./room"
	"time"
	"fmt"
)

func main() {
	fmt.Print("\033[2J")
	for {
		time.Sleep(time.Second/3)
		fmt.Print("\033[H")
		r.Show()
		step()
	}
}
var r *room.Room
var walls [][]bool
var maxBound room.Vector
var minBound room.Vector
var state *State
func init() {
	maxBound = room.NewVector(0, 0)
	minBound = room.NewVector(0, 0)
	r = room.NewRoom(4, 4, 12)
	walls = make([][]bool, 1)
	walls[0] = make([]bool, 1)
	state = &State{}
}

type State struct {
	direction room.Direction
	pos room.Vector
}

func Clean() {
	r.Clean()
}

func Right() {
	state.direction = (state.direction + 1) % 4
	r.Right()
}
func Forward() bool {
	v := state.direction.GetVector()
	ok := r.Forward()
	cur := state.pos.Add(v)
	maxBound = maxBound.Max(cur)
	minBound = minBound.Min(cur)
	UpdateWalls(v)
	if ok == true {
		state.pos = state.pos.Add(v)
		return true
	}
	walls[cur.X-minBound.X][cur.Y-minBound.Y] = true
	return false
}

func UpdateWalls(v room.Vector) {
	diff := maxBound.Minus(minBound)
	oldWalls := walls
	walls = make([][]bool, diff.X + 1)
	for i := 0; i < len(walls); i++ {
		walls[i] = make([]bool, diff.Y + 1)
	}
	for i := 0; i < len(oldWalls); i++ {
		for j := 0; j < len(oldWalls[i]); j++ {
			walls[i][j] = oldWalls[i][j]
		}
	}
}

func step() {
	Clean()
	fmt.Println(state)
	fmt.Println("REP")
	for i := minBound.X; i < maxBound.X; i++ {
		for j := minBound.Y; j < maxBound.Y; j++ {
			if walls[i-minBound.X][j-minBound.Y] == true {
				fmt.Print("• ")
			} else {
				fmt.Print("º ")
			}
		}
		fmt.Println()
	}
	for {
		ok := Forward()
		if ok == true { break }
		Right()
	}
}
