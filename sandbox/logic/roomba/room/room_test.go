package room

import (
	"testing"
)

func TestVector(t *testing.T) {
	vector := Vector{1,2}
	if vector.x != 1 {
		t.Errorf("Expected vector x to be %d, got %d\n", 1, vector.x)
	}
	if vector.y != 2 {
		t.Errorf("Expected vector x to be %d, got %d\n", 2, vector.y)
	}
}

func TestNewRoom(t *testing.T) {
	room := newRoom(4, 5, 42)
	if room.size.x != 4 {
		t.Errorf("Expected room x size to be %d, got %d\n", 4, room.size.x)
	}
	if room.size.y != 5 {
		t.Errorf("Expected room x size to be %d, got %d\n", 5, room.size.y)
	}
	if len(room.walls) != 4 {
		t.Errorf("Expected len(room.walls) to be %d, got %d\n", 4, len(room.walls))
	}
	if len(room.walls[0]) != 5 {
		t.Errorf("Expected len(room.walls) to be %d, got %d\n", 5, len(room.walls[0]))
	}
	if room.walls[room.roomba.pos.x][room.roomba.pos.y] == true {
		t.Errorf("Roomba started in a wall at pos %v\n", room.roomba.pos)
	}
}

func TestRoomTraversable(t *testing.T) {
	room := newRoom(5, 10, 42)
	if room.walls[room.roomba.pos.x][room.roomba.pos.y] == true {
		t.Errorf("Roomba started in a wall at pos %v\n", room.roomba.pos)
	}
	var visited [5][10]bool
	if len(visited) != len(room.walls) {
		t.Errorf("Expected Visited to be len %d, got %d\n", len(room.walls), len(visited))
	}
	if len(visited[0]) != len(room.walls[0]) {
		t.Errorf("Expected Visited[0] to be len %d, got %d\n", len(room.walls[0]), len(visited[0]))
	}
	var traverse func(int, int)
	traverse = func(x int, y int) {
		if room.walls[x][y] == true {
			return
		}
		for i := -1; i <= 1; i++ {
			for j := -1; j <= 1; j++ {
				xoff := x+i
				yoff := y+j
				if xoff >= len(visited) || xoff < 0 { continue }
				if yoff >= len(visited[0]) || yoff < 0 { continue }
				if visited[xoff][yoff] == true { continue }
				visited[xoff][yoff] = true
				traverse(xoff, yoff)
			}
		}
	}
	traverse(room.roomba.pos.x, room.roomba.pos.y)
	unreachable := [][2]int{}
	for i := 0; i < len(visited); i++ {
		for j := 0; j < len(visited[0]); j++ {
			if visited[i][j] != true {
				unreachable = append(unreachable, [2]int{i,j})
			}
		}
	}
	if len(unreachable) != 0 {
		t.Errorf("Can not get to %d of %d squares\n", len(unreachable), 25*30)
	}
	wallCount := 0
	for i := 0; i < len(room.walls); i++ {
		for j := 0; j < len(room.walls[i]); j++ {
			if room.walls[i][j] == false { continue }
			wallCount += 1
		}
	}
	if wallCount == 0 {
		t.Errorf("Warning no walls generated")
	}
}
