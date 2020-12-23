package room

import (
	"log"
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
		return newVector(-1, 0)
	case RIGHT:
		return newVector(0, 1)
	case DOWN:
		return newVector(1, 0)
	case LEFT:
		return newVector(0, -1)
	default:
		log.Fatalf("Direction should be one of UP, RIGHT, DOWN, LEFT. Got %d\n", d)
		return newVector(0, 0)
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
	return m[v.x][v.y]
}
func (m Matrix) Set(v Vector, val bool) {
	m[v.x][v.y] = val
}
func (m Matrix) Size() Vector {
	return newVector(len(m), len(m[0]))
}
func (m Matrix) InBounds(v Vector) bool {
	size := m.Size()
	if v.x < 0 || v.y < 0 { return false }
	if v.x >= size.x || v.y >= size.y { return false }
	return true
}

type Vector struct {
	x int
	y int
}
func newVector(x int, y int) Vector {
	return Vector{x,y}
}
func (v1 Vector) Add(v2 Vector) Vector {
	return newVector(v1.x + v2.x, v1.y + v2.y)
}

func (v Vector) Copy() Vector {
	return newVector(v.x, v.y)
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


func newRoom(x int, y int, seed int64) *Room {
	rand.Seed(seed)
	var room Room
	room.size = newVector(x, y)
	room.walls = newMatrix(x, y)
	room.roomba = Roomba{direction: UP}
	start := newVector(rand.Intn(x), rand.Intn(y))
	room.roomba.pos = start

	var isUnreachable func() bool
	isUnreachable = func() bool {
		visited := newMatrix(x, y)
		var traverse func(Vector)
		traverse = func(pos Vector) {
			if room.walls.Get(pos) == true { return }
			for i := -1; i <= 1; i++ {
				for j := -1; j <= 1; j++ {
					idx := newVector(i, j)
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
				idx := newVector(i, j)
				if visited.Get(idx) == false {
					return true
				}
			}
		}
		return false
	}
	for i := 0; i < x; i++ {
		for j := 0; j < y; j++ {
			idx := newVector(i, j)
			v := rand.Intn(2)
			if v == 0 { continue }
			//if room.roomba.pos.x == idx.x && room.roomba.pos.y == idx.y { continue }
			if room.roomba.pos == idx { continue }
			room.walls.Set(idx, true)
			if isUnreachable() == false { continue }
			room.walls.Set(idx, false)
		}
	}
	room.clean = newMatrix(x, y)
	for i := 0; i < x; i++ {
		for j := 0; j < y; j++ {
			idx := newVector(i, j)
			if room.walls.Get(idx) == true {
				room.clean.Set(idx, true)
			}
		}
	}
	return &room
}
func (room *Room) IsClean() bool {
	size := room.clean.Size()
	for i := 0; i < size.x; i++ {
		for j := 0; j < size.y; j++ {
			idx := newVector(i, j)
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
	room.roomba.pos = room.roomba.pos.Add(directionVector)
	if room.walls.Get(room.roomba.pos) == false { return true }
	room.roomba.pos = prevPos
	return false
}
