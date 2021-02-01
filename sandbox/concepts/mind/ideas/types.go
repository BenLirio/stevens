package ideas

type Idea struct {
	val float64
	relations []*Idea
}

func newIdea() *Idea {
	idea := &Idea{}
	return idea
}
