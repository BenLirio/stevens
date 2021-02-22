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

func GetTerminalSettings() (*unix.Termios, error) {
	termios, err := unix.IoctlGetTermios(unix.Stdin, unix.TCGETS)
	if err != nil {
		return &unix.Termios{}, err
	}
	return termios, nil
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
	b := make([]byte, 1)
	for {
		os.Stdin.Read(b)
		os.Stdout.Write(b)
	}
}
