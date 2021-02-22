package main

import (
	"bufio"
	"strings"
	"os"
	"fmt"
)


func main() {
	scanner := bufio.NewScanner(os.Stdin)
	for scanner.Scan() {
		line := strings.Split(scanner.Text(), " ")
		fmt.Println(line)
	}
}
