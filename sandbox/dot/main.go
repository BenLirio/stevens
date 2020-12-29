package main

import (
	"fmt"
	"io"
	"text/template"
)

type Edge struct {
	From string
	To string
}
type Graph struct {
	Edges []Edge
}

var inventoryTemplate string = `
graph {
{{range .Edges}}    {{.From}} -- {{.To}};
{{end}}
}
`

func main() {
	e1 := Edge{"a", "b"}
	e2 := Edge{"b", "a"}
	edges := []Edge{e1, e2}
	graph := Graph{edges}
	tmpl, err := template.New("test").Parse(inventoryTemplate)
	if err != nil { panic(err) }
	r, w := io.Pipe()
	//fmt.Println(r, w)
	err = tmpl.Execute(w, graph)
	fmt.Println(r)
	fmt.Println("done")
}
