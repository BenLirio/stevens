package tree

import (
	"os"
	"testing"
)

type Node struct {
	id string
	left *Node
	right *Node
}
func (n *Node) Id() string {
	return n.id
}
func (n *Node) Left() BinaryTreeNode {
	if n.left == nil { return nil }
	return n.left
}
func (n *Node) Right() BinaryTreeNode {
	if n.right == nil { return nil }
	return n.right
}


func TestShowTree(t *testing.T) {
	c := &Node{id: "C"}
	d := &Node{id: "D"}
	a := &Node{id: "A", left: c, right: d}
	b := &Node{id: "B"}
	root := &Node{id: "root", left: b, right: a}
	Show(root, os.Stdout)
}
