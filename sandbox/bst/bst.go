package main

import (
	"fmt"
	"strings"
	"strconv"
	"bufio"
	"os"
	"../tree"
	"io"
)

type Node struct {
	val int
	left *Node
	right *Node
	parent *Node
}
func (n *Node) Left() tree.BinaryTreeNode {
	if n.left == nil { return nil }
	return n.left
}
func (n *Node) Right() tree.BinaryTreeNode {
	if n.right == nil { return nil }
	return n.right
}
func (n *Node) Id() string {
	return fmt.Sprintf("%d", n.val)
}

type BinarySearchTree struct {
	root *Node
}
func NewBinarySearchTree() *BinarySearchTree {
	bst := &BinarySearchTree{}
	return bst
}
func (bst *BinarySearchTree) Insert(val int) {
	cur := bst.root
	var prev *Node = nil
	for cur != nil {
		prev = cur
		if val > cur.val {
			cur = cur.right
		} else {
			cur = cur.left
		}
	}
	if prev == nil {
		bst.root = &Node{val: val}
		return
	}
	if val > prev.val {
		prev.right = &Node{val: val, parent: prev}
	} else {
		prev.left = &Node{val: val, parent: prev}
	}
}
func (bst *BinarySearchTree) Search(val int) (*Node, bool) {
	x := bst.root
	for x != nil {
		if x.val == val {
			return x, true
		} else if val > x.val {
			x = x.right
		} else {
			x = x.left
		}
	}
	return &Node{}, false
}
func (bst *BinarySearchTree) transplant(u *Node, v *Node) {
	if u.parent == nil {
		bst.root = v
	} else if u.parent.left == u {
		u.parent.left = v
	} else {
		u.parent.right = v
	}
	if v != nil {
		v.parent = u.parent
	}
}
func (n *Node) TreeMinimum() *Node {
	cur := n
	for {
		if cur.left == nil { return cur }
		cur = cur.left
	}
}
func (bst *BinarySearchTree) Delete(n *Node) {
	if n.left == nil {
		bst.transplant(n, n.right)
	} else if n.right == nil {
		bst.transplant(n, n.left)
	} else {
		successor := n.right.TreeMinimum()
		if successor != n.right {
			bst.transplant(successor, successor.right)
			successor.right = n.right
			successor.right.parent = successor
		}
		bst.transplant(n, successor)
		successor.left = n.left
		successor.left.parent = successor
	}
}
func (bst *BinarySearchTree) Show(wr io.Writer) {
	if bst.root == nil { return }
	tree.Show(bst.root, wr)
}
func main() {
	scanner := bufio.NewScanner(os.Stdin)
	bst := NewBinarySearchTree()
	for scanner.Scan() {
		args := strings.Split(scanner.Text(), " ")
		if args[0] == "insert" {
			i, err := strconv.Atoi(args[1])
			if err != nil { panic(err) }
			bst.Insert(i)
		}
		if args[0] == "delete" {
			i, err := strconv.Atoi(args[1])
			if err != nil { panic(err) }
			if n, ok := bst.Search(i); ok == true {
				bst.Delete(n)
			}
		}
		bst.Show(os.Stdout)
	}
}
