package main

import (
	"os/exec"
	"syscall"
	"os/signal"
	"io/ioutil"
	"strings"
	"fmt"
	"os"
	"net/http"
)

func Compile(src string, outFolder string) error {
	cmd := exec.Command("latex", "--output-format", "pdf", "--output-directory", outFolder, src)
	err := cmd.Run()
	if err != nil {
		fmt.Println("Error compiling")
		return err
	}
	return nil

}

var dir string = ""
func cleanup() {
	if dir != "" {
		os.RemoveAll(dir)
	}
}
func main() {
	var err error
	c := make(chan os.Signal)
	signal.Notify(c, os.Interrupt, syscall.SIGTERM)
	go func() {
		<-c
		cleanup()
		os.Exit(1)
	}()
	if len(os.Args) != 2 {
		fmt.Println("Usage: serve [.tex]")
		return
	}
	src := os.Args[1]
	dir, err = ioutil.TempDir(".", "static")
	if err != nil {
		fmt.Println(err)
		return
	}
	err = Compile(src, dir)
	if err != nil {
		fmt.Println(err)
		return
	}
	fs := http.FileServer(http.Dir(dir))
	http.Handle("/", fs)
	name := strings.Split(src, ".")[0]
	fmt.Println(fmt.Sprintf("http://localhost:3000/%s.pdf", name))
	err = http.ListenAndServe(":3000", nil)
	if err != nil {
		fmt.Println(err)
		return
	}
}
