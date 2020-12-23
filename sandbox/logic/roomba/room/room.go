package room

import (
	"math/rand"
)

type Direction uint32
const (
	UP Direction = iota
	RIGHT
	DOWN
	LEFT
)

type Vector struct {
	x int
	y int
}

type Roomba struct {
	pos Vector
	direction Direction
}

type Room struct {
	size Vector
	roomba Roomba
	walls [][]bool
}


func newRoom(x int, y int, seed int64) *Room {
	rand.Seed(seed)
	room := Room{}
	room.size = Vector{x, y}
	room.walls = make([][]bool, x)
	for i := 0; i < x; i++ {
		room.walls[i] = make([]bool, y)
	}
	room.roomba = Roomba{direction: UP}
	start := Vector{rand.Intn(x), rand.Intn(y)}
	room.roomba.pos = start
	var isUnreachable func() bool

	isUnreachable = func() bool {
		visited := make([][]bool, x)
		for i := 0; i < x; i++ {
			visited[i] = make([]bool, y)
		}
		var traverse func(int, int)
		traverse = func(x int, y int) {
			if room.walls[x][y] == true {
				return
			}
			for i := -1; i <= 1; i++ {
				for j := -1; j <= 1; j++ {
					xoff := x + i
					yoff := y + j
					if xoff < 0 || xoff >= len(visited) { continue }
					if yoff < 0 || yoff >= len(visited[0]) { continue }
					if visited[xoff][yoff] == true { continue }
					visited[xoff][yoff] = true
					traverse(xoff, yoff)
				}
			}
		}
		traverse(room.roomba.pos.x, room.roomba.pos.y)
		for i := 0; i < len(visited); i++ {
			for j := 0; j < len(visited[i]); j++ {
				if visited[i][j] == false {
					return true
				}
			}
		}
		return false
	}
	for i := 0; i < x; i++ {
		for j := 0; j < y; j++ {
			v := rand.Intn(2)
			if v == 0 { continue }
			if room.roomba.pos.x == i && room.roomba.pos.y == j { continue }
			room.walls[i][j] = true
			if isUnreachable() == false { continue }
			room.walls[i][j] = false
		}
	}
	return &room
}
