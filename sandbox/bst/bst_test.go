package main

import (
	"../tree"
	"testing"
	"os"
)
func TestNode(t *testing.T) {
	t.Skip()
	root := &Node{
		val: 4,
		left: &Node{
			val: 5,
		},
	}
	tree.Show(root, os.Stdout)
}
func TestNewBinarySearchTree(t *testing.T) {
	NewBinarySearchTree()
}
func TestInsert(t *testing.T) {
	bst := NewBinarySearchTree()
	bst.Insert(10)
	bst.Insert(20)
	bst.Insert(4)
	t.Skip()
	bst.Show(os.Stdout)
}
func TestSearch(t *testing.T) {
	bst := NewBinarySearchTree()
	bst.Insert(5)
	bst.Insert(4)
	bst.Insert(6)
	if n, ok := bst.Search(5); ok == false {
		t.Errorf("5 should be in the tree\n")
		if n.val != 5 {
			t.Errorf("Search should give the correct node\n")
		}
	}
	if n, ok := bst.Search(6); ok == false {
		t.Errorf("6 should be in the tree\n")
		if n.val != 6 {
			t.Errorf("Search should give the correct node\n")
		}
	}
	if n, ok := bst.Search(4); ok == false {
		t.Errorf("4 should be in the tree\n")
		if n.val != 4 {
			t.Errorf("Search should give the correct node\n")
		}
	}
	if _, ok := bst.Search(7); ok == true {
		t.Errorf("7 should not be in the tree\n")
	}
}
