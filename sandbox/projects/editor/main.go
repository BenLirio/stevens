package main

import (
	"golang.org/x/sys/unix"
	"os"
	"log"
)
func check(e error) {
	if e != nil {
		log.Fatal(e)
	}
}

func ConfigureTermio() {
	termio, err := unix.IoctlGetTermios(unix.Stdin, unix.TCGETS)
	check(err)
	termio.Lflag &= ^uint32(unix.ECHO)
	termio.Lflag &= ^uint32(unix.ICANON)
	err = unix.IoctlSetTermios(unix.Stdin, unix.TCSETS, termio)
	check(err)
}

func main() {
	ConfigureTermio()
	b := make([]byte, 1)
	for {
		os.Stdin.Read(b)
		os.Stdout.Write(b)
	}
}
