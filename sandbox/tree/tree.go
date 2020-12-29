package tree

import (
	"text/template"
	"io"
	"os/exec"
)
type BinaryTreeNode interface {
	Id() string
	Left() BinaryTreeNode
	Right() BinaryTreeNode
}
var TreeTemplate string = `
digraph TREE {
	{{range .Edges}}
		{{.From}} -> {{.To}};
	{{end}}
}
`
func init() {
	tmpl = template.Must(template.New("dot").Parse(TreeTemplate))
}

type Edge struct {
	From string
	To string
}

type Graph struct {
	Edges []Edge
}

var tmpl *template.Template

func getEdges(n BinaryTreeNode) []Edge {
	edges := []Edge{}
	que := []BinaryTreeNode{n}
	for len(que) != 0 {
		cur := que[0]
		que = que[1:]
		if left := cur.Left(); left != nil {
			edges = append(edges, Edge{From: cur.Id(), To: left.Id()})
			que = append(que, left)
		}
		if right := cur.Right(); right != nil {
			edges = append(edges, Edge{From: cur.Id(), To: right.Id()})
			que = append(que, right)
		}
	}
	return edges
}

func generateGraph(n BinaryTreeNode) Graph {
	edges := getEdges(n)
	graph := Graph{ Edges: edges }
	return graph
}
func writeTemplateFromBinaryTreeNode(wr io.Writer, n BinaryTreeNode) {
	graph := generateGraph(n)
	err := tmpl.Execute(wr, graph)
	if err != nil { panic(err) }
}

func Show(n BinaryTreeNode, w io.Writer) {
	templateReader, templateWriter := io.Pipe()
	pngReader, pngWriter := io.Pipe()
	go func() {
		writeTemplateFromBinaryTreeNode(templateWriter, n)
		templateWriter.Close()
	}()
	go func() {
		dot(templateReader, pngWriter)
		templateReader.Close()
		pngWriter.Close()
	}()
	imgcat(pngReader, w)
	pngReader.Close()
}

func dot(r io.Reader, w io.Writer) {
	cmd := exec.Command("dot", "-Tpng")
	cmd.Stdin = r
	cmd.Stdout = w
	cmd.Run()
}

func imgcat(r io.Reader, w io.Writer) {
	cmd := exec.Command("imgcat")
	cmd.Stdin = r
	cmd.Stdout = w
	cmd.Run()
}
