package main

import (
	"fmt"
	"os"
	"bufio"
	"log"
	"os/exec"
	"io"
	"time"
)

func pause() {
	time.Sleep(30*time.Millisecond)
}


func main() {
	testData := []struct {
		Host string
		Port string
		Username string
		Messages []string
	}{
		{"127.0.0.1", "1234", "uname\n", []string{"one\n", "two\n", "three\n", "bye\n"}},
		{"127.0.90.1", "1234", "uname\n", []string{"one\n", "two\n", "three\n", "bye\n"}},
	}
	username := "bot\n"

	var out [2][1000]byte
	var finalByte [2]int

	for _, t := range(testData) {
		for i := 0; i < len(out); i++ {
			var target string
			if i == 0 {
				target = "./bin/chatclient"
			} else {
				target = "./bin/my_chatclient"
			}
			command := exec.Command(target, t.Host, t.Port)
			stdin, err := command.StdinPipe()
			if err != nil {
				log.Fatal(err)
			}
			stdout, err := command.StdoutPipe()
			if err != nil {
				log.Fatal(err)
			}
			// Write
			go func() {
				defer stdin.Close()
				io.WriteString(stdin, username)
				for _, message := range(t.Messages) {
					pause()
					io.WriteString(stdin, message)
				}
				for{}
			}()

			// Read
			cur := 0
			go func() {
				reader := bufio.NewReader(stdout)
				buf := make([]byte, 256)
				for {
					n, err := reader.Read(buf)
					if err != nil {
						if err == io.EOF {
							break
						}
						log.Fatal(err)
					}
					copy(out[i][cur:cur+n], buf[:n])

					cur += n
				}
			}()

			err = command.Run()
			finalByte[i] = cur
			if err != nil {
				log.Fatal(err)
			}
		}
		if finalByte[0] != finalByte[1] {
			fmt.Println("==========DIF===========")
			for i := 0; i < len(out); i++ {
				for j := 0; j < finalByte[i]; j++ {
					fmt.Print(string(out[i][j]))
				}
				fmt.Println("===============NEXT==============")
			}
			os.Exit(1)
		}
		fmt.Printf("Passed:\n\tHost: %s\n\tPort: %s\n\tUsername: %s\tMessages:\n", t.Host, t.Port, t.Username)
		for _, message := range(t.Messages) {
			fmt.Printf("\t\t%s", message)
		}
		fmt.Println()
	}
}
