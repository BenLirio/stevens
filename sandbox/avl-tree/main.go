package avl

import (
)
func main() {}
type Balance uint
const (
	LEFT_HEAVY Balance = iota
	BALANCED
	RIGHT_HEAVY
)
type Node struct {
	id string
	Val uint64
	height uint
	Left *Node
	Right *Node
	Parent *Node
	balance Balance
}
func (node *Node) updateHeight(height uint) {
	node.height = height
	if node.Parent != nil {
		node.Parent.updateHeight(height + 1)
	}
}
func (node *Node) Insert(val uint64) {
	if val > node.Val {
		if node.Right == nil {
			n := &Node{Val: val, Parent: node}
			n.updateHeight(0)
			node.Right = n
			return
		}
		node.Right.Insert(val)
		return
	}
	if node.Left == nil {
		n := &Node{Val: val, Parent: node}
		n.updateHeight(0)
		node.Left = n
		return
	}
	node.Left.Insert(val)
	return
}

func (node *Node) leftRotate() {
	var rootPointer **Node = &node.Parent.Right
	if node.Parent.Left == node {
		rootPointer = &node.Parent.Left
	}
	*(rootPointer) = node.Right
	tmp := node.Right.Left
	tmp.Parent = node
	node.Right.Left = node
	node.Right.Parent = node.Parent
	node.Parent = node.Right
	node.Right = tmp
}

type Avl struct {
	Root *Node
}
func (avl Avl) Insert(val uint64) Avl {
	if avl.Root == nil {
		avl.Root = &Node{Val: val}
		return avl
	}
	avl.Root.Insert(val)
	return avl
}
func NewAvl() Avl {
	avl := Avl{}
	return avl
}
