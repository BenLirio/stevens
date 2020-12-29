package room

import (
	"log"
	"fmt"
	"math/rand"
)

type Direction uint32
const (
	UP Direction = iota
	RIGHT
	DOWN
	LEFT
)
func (d Direction) GetVector() Vector {
	switch d {
	case UP:
		return NewVector(-1, 0)
	case RIGHT:
		return NewVector(0, 1)
	case DOWN:
		return NewVector(1, 0)
	case LEFT:
		return NewVector(0, -1)
	default:
		log.Fatalf("Direction should be one of UP, RIGHT, DOWN, LEFT. Got %d\n", d)
		return NewVector(0, 0)
	}
}
type Row []bool
type Matrix []Row
func newMatrix(x int, y int) Matrix {
	if x == 0 || y == 0 {
		log.Fatal("Can not make matrix of size 0,0")
	}
	matrix := make(Matrix, x)
	for i := 0; i < x; i++ {
		matrix[i] = make(Row, y)
	}
	return matrix
}
func (m Matrix) Get(v Vector) bool {
	return m[v.X][v.Y]
}
func (m Matrix) Set(v Vector, val bool) {
	m[v.X][v.Y] = val
}
func (m Matrix) Size() Vector {
	return NewVector(len(m), len(m[0]))
}
func (m Matrix) InBounds(v Vector) bool {
	size := m.Size()
	if v.X < 0 || v.Y < 0 { return false }
	if v.X >= size.X || v.Y >= size.Y { return false }
	return true
}

type Vector struct {
	X int
	Y int
}
func NewVector(x int, y int) Vector {
	return Vector{x,y}
}
func (v1 Vector) Add(v2 Vector) Vector {
	return NewVector(v1.X + v2.X, v1.Y + v2.Y)
}
func (v1 Vector) Max(v2 Vector) Vector {
	xMax := v1.X
	yMax := v1.Y
	if v2.X > xMax { xMax = v2.X }
	if v2.Y > yMax { yMax = v2.Y }
	return NewVector(xMax, yMax)
}
func (v1 Vector) Min(v2 Vector) Vector {
	xMin := v1.X
	yMin := v1.Y
	if v2.X < xMin { xMin = v2.X }
	if v2.Y < yMin { yMin = v2.Y }
	return NewVector(xMin, yMin)
}
func (v1 Vector) Minus(v2 Vector) Vector {
	diffX := v1.X - v2.X
	diffY := v1.Y - v2.Y
	return NewVector(diffX, diffY)
}

func (v Vector) Copy() Vector {
	return NewVector(v.X, v.Y)
}

type Roomba struct {
	pos Vector
	direction Direction
}

type Room struct {
	size Vector
	roomba Roomba
	walls Matrix
	clean Matrix
}


func NewRoom(x int, y int, seed int64) *Room {
	rand.Seed(seed)
	var room Room
	room.size = NewVector(x, y)
	room.walls = newMatrix(x, y)
	room.roomba = Roomba{direction: UP}
	start := NewVector(rand.Intn(x), rand.Intn(y))
	room.roomba.pos = start

	var isUnreachable func() bool
	isUnreachable = func() bool {
		visited := newMatrix(x, y)
		var traverse func(Vector)
		traverse = func(pos Vector) {
			if room.walls.Get(pos) == true { return }
			for i := -1; i <= 1; i++ {
				for j := -1; j <= 1; j++ {
					idx := NewVector(i, j)
					if idx.X != 0 && idx.Y != 0 { continue }
					offset := pos.Add(idx)
					if visited.InBounds(offset) == false { continue }
					if visited.Get(offset) == true { continue }
					visited.Set(offset, true)
					traverse(offset)
				}
			}
		}
		traverse(room.roomba.pos)
		for i := 0; i < len(visited); i++ {
			for j := 0; j < len(visited[i]); j++ {
				idx := NewVector(i, j)
				if visited.Get(idx) == false {
					return true
				}
			}
		}
		return false
	}
	for i := 0; i < x; i++ {
		for j := 0; j < y; j++ {
			idx := NewVector(i, j)
			v := rand.Intn(4)
			if v != 0 { continue }
			//if room.roomba.pos.X == idx.X && room.roomba.pos.Y == idx.Y { continue }
			if room.roomba.pos == idx { continue }
			room.walls.Set(idx, true)
			if isUnreachable() == false { continue }
			room.walls.Set(idx, false)
		}
	}
	room.clean = newMatrix(x, y)
	for i := 0; i < x; i++ {
		for j := 0; j < y; j++ {
			idx := NewVector(i, j)
			if room.walls.Get(idx) == true {
				room.clean.Set(idx, true)
			}
		}
	}
	return &room
}
func (room *Room) IsClean() bool {
	size := room.clean.Size()
	for i := 0; i < size.X; i++ {
		for j := 0; j < size.Y; j++ {
			idx := NewVector(i, j)
			if room.clean.Get(idx) == false {
				return false
			}
		}
	}
	return true
}
func (room *Room) Clean() {
	room.clean.Set(room.roomba.pos, true)
}
func (room *Room) Right() {
	room.roomba.direction = (room.roomba.direction + 1) % 4
}
func (room *Room) Left() {
	room.roomba.direction = (room.roomba.direction - 1) % 4
}
func (room *Room) Forward() bool {
	directionVector := room.roomba.direction.GetVector()
	prevPos := room.roomba.pos
	if room.walls.InBounds(room.roomba.pos.Add(directionVector)) == false {
		return false
	}
	room.roomba.pos = room.roomba.pos.Add(directionVector)
	if room.walls.Get(room.roomba.pos) == false { return true }
	room.roomba.pos = prevPos
	return false
}
func (room *Room) Show() {
	size := room.walls.Size()
	for i := 0; i < size.X; i++ {
		for j := 0; j < size.Y; j++ {
			idx := NewVector(i, j)
			if room.roomba.pos == idx {
				switch room.roomba.direction {
				case UP:
					fmt.Print("^ ")
				case RIGHT:
					fmt.Print("> ")
				case DOWN:
					fmt.Print("v ")
				case LEFT:
					fmt.Print("< ")
				}
			} else if room.walls.Get(idx) == true {
				fmt.Print("• ")
			} else if room.clean.Get(idx) == false {
				fmt.Print("º ")
			} else {
				fmt.Print("  ")
			}
		}
		fmt.Println()
	}
}
