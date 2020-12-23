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

func TestIsClean(t *testing.T) {
	room := newRoom(10, 11, 42)
	for i := 0; i < len(room.walls); i++ {
		for j := 0; j < len(room.walls[0]); j++ {
			if room.walls[i][j] == false && room.clean[i][j] == true {
				t.Errorf("Spot (%d, %d) has no wall so should not start clean\n", i, j)
			}
			if room.walls[i][j] == true && room.clean[i][j] == false {
				t.Errorf("Spot (%d, %d) has a wall so it should start clean\n", i, j)
			}
		}
	}
	if room.IsClean() == true {
		t.Errorf("Room should not start clean\n")
	}
	for i := 0; i < len(room.walls); i++ {
		for j := 0; j < len(room.walls[0]); j++ {
			room.clean[i][j] = true
		}
	}
	if room.IsClean() == false {
		t.Errorf("Room should be clean when all squares are\n")
	}
}

func TestRoombaClean(t *testing.T) {
	room := newRoom(10, 10, 42)
	numClean := 0
	for i := 0; i < len(room.walls); i++ {
		for j := 0; j < len(room.walls[0]); j++ {
			if room.clean[i][j] == true {
				numClean += 1
			}
		}
	}
	room.Clean()
	numClean2 := 0
	for i := 0; i < len(room.walls); i++ {
		for j := 0; j < len(room.walls[0]); j++ {
			if room.clean[i][j] == true {
				numClean2 += 1
			}
		}
	}
	room.Clean()
	numClean3 := 0
	for i := 0; i < len(room.walls); i++ {
		for j := 0; j < len(room.walls[0]); j++ {
			if room.clean[i][j] == true {
				numClean3 += 1
			}
		}
	}
	if numClean != (numClean2 - 1) {
		t.Errorf("Roomba should clean the square it is on and only that square\n")
	}
	if numClean2 != numClean3 {
		t.Errorf("Cleaning the same square twice should not do anything\n")
	}
}

func TestRotation(t *testing.T) {
	room := newRoom(8, 9, 42)
	if room.roomba.direction != UP {
		t.Errorf("Roomba should start going UP\n")
	}
	room.Right()
	if room.roomba.direction != RIGHT {
		t.Errorf("UP => Right() sould be RIGHT\n")
	}
	room.Right()
	if room.roomba.direction != DOWN {
		t.Errorf("RIGHT => Right() sould be DOWN\n")
	}
	room.Right()
	if room.roomba.direction != LEFT {
		t.Errorf("DOWN => Right() sould be LEFT\n")
	}
	room.Right()
	if room.roomba.direction != UP {
		t.Errorf("LEFT => Right() sould be UP\n")
	}
	room.Left()
	if room.roomba.direction != LEFT {
		t.Errorf("UP => Left() sould be LEFT\n")
	}
	room.Left()
	if room.roomba.direction != DOWN {
		t.Errorf("LEFT => Left() sould be LEFT\n")
	}
	room.Left()
	if room.roomba.direction != RIGHT {
		t.Errorf("DOWN => Left() sould be RIGHT\n")
	}
	room.Left()
	if room.roomba.direction != UP {
		t.Errorf("RIGHT => Left() sould be UP\n")
	}
}

func TestMove(t *testing.T) {
	room := newRoom(6, 8, 42)
	room.roomba.pos.x = 0
	room.roomba.pos.y = 0
	room.roomba.direction = DOWN
	room.walls[0][0] = false
	room.walls[1][0] = false
	room.walls[2][0] = true
	if room.roomba.pos.x != 0 || room.roomba.pos.y != 0 {
		t.Errorf("Should have put roomba in (0, 0)\n")
	}
	ok := room.Forward()
	if ok == false {
		t.Errorf("Forward() should return true when there is no wall\n")
	}
	if room.roomba.pos.x != 1 || room.roomba.pos.y != 0 {
		t.Errorf("Roomba should be a pos (1, 0), got %v\n", room.roomba.pos)
	}
	ok = room.Forward()
	if ok == true {
		t.Errorf("Forward() should return false when there is a wall\n")
	}
	if room.roomba.pos.x != 1 || room.roomba.pos.y != 0 {
		t.Errorf("Roomba should be a pos (1, 0), got %v\n", room.roomba.pos)
	}
}
