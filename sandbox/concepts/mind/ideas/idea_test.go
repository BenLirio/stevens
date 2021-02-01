package ideas

import (
	"testing"
)

func TestTypes(t *testing.T) {
	newIdea()
}

func TestRange(t *testing.T) {
	a := &Idea{1, []*Idea{}}
	b := &Idea{2, []*Idea{}}
	b.relations = append(b.relations, a)
}
