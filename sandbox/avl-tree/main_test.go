package avl

import (
	"testing"
)

func TestNewAvl(t *testing.T) {
	avl := NewAvl()
	if avl.Root != nil {
		t.Errorf("AVL root should be nil\n")
	}
}

func TestInsert(t *testing.T) {
	avl := NewAvl()
	avl = avl.Insert(3)
	if avl.Root == nil {
		t.Errorf("AVL Root should be non nil\n")
		return
	}
	if avl.Root.Val != 3 {
		t.Errorf("AVL Root should have Val of 3, got %d\n", avl.Root.Val)
	}
}

func TestNumNodes(t *testing.T) {
	var countNodes func(node *Node) int
	countNodes = func(node *Node) int {
		if node == nil {
			return 0
		}
		return 1 + countNodes(node.Left) + countNodes(node.Right)
	}
	var avl Avl
	avl = NewAvl()
	if countNodes(avl.Root) != 0 {
		t.Errorf("NewAvl should have 0 nodes, got %d\n", countNodes(avl.Root))
	}
	avl = avl.Insert(3)
	if countNodes(avl.Root) != 1 {
		t.Errorf("AVL should have 1 nodes, got %d\n", countNodes(avl.Root))
	}
	avl = avl.Insert(6)
	if countNodes(avl.Root) != 2 {
		t.Errorf("AVL should have 2 nodes, got %d\n", countNodes(avl.Root))
	}
	avl = avl.Insert(4)
	if countNodes(avl.Root) != 3 {
		t.Errorf("AVL should have 3 nodes, got %d\n", countNodes(avl.Root))
	}
}

func TestBinarySearchTree(t *testing.T) {
	var nodeVals = []uint64{1,2,0,8,8,4,5,1,8}
	var isBinarySearchTree func(node *Node) bool
	isBinarySearchTree = func(node *Node) bool {
		if node == nil { return true }
		if node.Left != nil && node.Left.Val > node.Val { return false }
		if node.Right != nil && node.Right.Val < node.Val { return false }
		return isBinarySearchTree(node.Left) && isBinarySearchTree(node.Right)
	}
	var avl Avl
	for _, val := range nodeVals {
		avl = avl.Insert(val)
	}
	if isBinarySearchTree(avl.Root) == false {
		t.Errorf("Avl should be a binary search tree")
	}
}

func TestNodeHeight(t *testing.T) {
	var checkHeight func(node *Node) (uint, bool)
	checkHeight = func(node *Node) (uint, bool) {
		if node == nil { return 0, true }
		var lHeight uint
		var rHeight uint
		var ok bool
		lHeight, ok = checkHeight(node.Left)
		if ok != true { return 0, false }
		rHeight, ok = checkHeight(node.Right)
		if ok != true { return 0, false }
		height := lHeight
		if rHeight > height {
			height = rHeight
		}
		if node.height != height {
			return 0, false
		}
		return (height + 1), true
	}
	var nodeVals = []uint64{1,2,0,8,8,4,5,1,8}
	var avl Avl
	for _, val := range nodeVals {
		avl = avl.Insert(val)
	}
	if _, ok := checkHeight(avl.Root); ok != true {
		t.Errorf("Tree does no have correct height values\n")
	}
}

func TestBalencedTree(t *testing.T) {
	var isBalencedTree func(node *Node) bool
	isBalencedTree = func(node *Node) bool {
		if node == nil { return true }
		var rHeight uint = 0
		var lHeight uint = 0
		if node.Right != nil { rHeight = node.Right.height }
		if node.Left != nil { lHeight = node.Left.height }
		var diff int = int(rHeight) - int(lHeight)
		if diff > 1 || diff < -1 { return false }
		return isBalencedTree(node.Left) && isBalencedTree(node.Right)
	}
	var nodeVals = []uint64{1,2,0,8,8,4,5,1,8}
	var avl Avl
	for _, val := range nodeVals {
		avl = avl.Insert(val)
	}
	if isBalencedTree(avl.Root) == false {
		t.Errorf("Tree is not balenced\n")
	}
}

func TestLeftRotate(t *testing.T) {
	t1 := &Node{id: "t1", Val: 1}
	t23 := &Node{id: "t23", Val: 2}
	t4 := &Node{id: "t4", Val: 3}
	z := &Node{id: "z", Val: 4, Left: t23, Right: t4}
	x := &Node{id: "x", Val: 5, Left: t1, Right: z}
	root := &Node{id: "root", Val: 9, Left: x}
	x.Parent = root
	z.Parent = x
	t1.Parent = x
	t23.Parent = z
	t4.Parent = z
	before := []Rel{
		{root, x, nil},
		{x, t1, z},
		{z, t23, t4},
	}
	for _, rel := range before {
		checkRel(t, rel)
	}
	after := []Rel{
		{root, z, nil},
		{x, t1, t23},
		{z, x, t4},
	}
	x.leftRotate()
	for _, rel := range after {
		checkRel(t, rel)
	}
}

func TestRightRotate(t *testing.T) {
	root := &Node{
		id: "root",
		Right: &Node {
			id: "z",
			Left: &Node {
				id: "x",
				Left: &Node{id: "t1"},
				Right: &Node{id: "t23"},
			},
			Right: &Node {
				id: "t4",
			},
		},
	}
	z := root.Right
	z.Parent = root
	x := z.Left
	x.Parent = z
	t1 := x.Left
	t1.Parent = x
	t23 := x.Right
	t23.Parent = x
	t4 := z.Right
	t4.Parent = z
	nodeRelationsBeforeRightRotate := []Rel{
		{root, z, nil},
		{z, x, t4},
		{x, t1, t23},
	}
	for _, rel := range nodeRelationsBeforeRightRotate {
		checkRel(t, rel)
	}
}
