package main

import (
	"io/ioutil"
	"log"
	"os"
	"fmt"
	"bufio"
	"strings"
)

func main() {
	os.RemoveAll("/tmp/myShell")
	err := os.Mkdir("/tmp/myShell", 0755)
	if err != nil {
		panic(err)
	}
	defer os.RemoveAll("/tmp/myShell")
	os.Chdir("/tmp/myShell")
	if err != nil {
		panic(err)
	}
	scanner := bufio.NewScanner(os.Stdin)
	for scanner.Scan() {
		text := scanner.Text()
		args := strings.Split(text, " ")
		if len(args) >= 1 {
			if args[0] == "ls" {
				fmt.Println("LIST")
				files, err := ioutil.ReadDir(".")
				if err != nil {
					log.Fatal(err)
				}
				for _, file := range files {
					fmt.Println(file.Name())
				}
			}
			if len(args) == 2 {
				if args[0] == "touch" {
					_, err := os.Create(args[1])
					if err != nil {
						log.Fatal(err)
					}
				}
			}
		}
	}

}
