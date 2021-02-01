package avl

import (
	"testing"
)

type Rel struct {
	parent *Node
	left *Node
	right *Node
}
func areNodesEqual(n1 *Node, n2 *Node) bool {
	if (n1 == nil || n2 == nil) && (n1 != n2) {
		return false
	}
	if n1 == n2 { return true }
	return false
}
func checkRel(t *testing.T, rel Rel) {
	parent := rel.parent
	if parent == nil {
		t.Errorf("Parent must be set when checking node relations\n")
		return
	}
	left := rel.left
	right := rel.right
	if ok := areNodesEqual(left, parent.Left); ok == false {
		leftId := "None"
		parentLeftId := "None"
		if left != nil { leftId = left.id }
		if parent.Left != nil { parentLeftId = parent.Left.id }
		t.Errorf("Expected %s's left node to be %s, got %s\n", parent.id, leftId, parentLeftId)
	}
	if ok := areNodesEqual(parent.Right, right); ok == false {
		rightId := "None"
		parentRightId := "None"
		if right != nil { rightId = right.id }
		if parent.Right != nil { parentRightId = parent.Right.id }
		t.Errorf("Expected %s's right node to be %s, got %s\n", parent.id, rightId, parentRightId)
	}
	if (left != nil) && (left.Parent != parent) {
		t.Errorf("Expected parent of %s to be %s, got %s\n", left.id, parent.id, left.Parent.id)
	}
	if (right != nil) && (right.Parent != parent) {
		t.Errorf("Expected parent of %s to be %s, got %s\n", right.id, parent.id, right.Parent.id)
	}
}
