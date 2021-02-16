package main

import (
	"log"
	"os"
	"golang.org/x/sys/unix"
	"fmt"
)

func showTermio(termio *unix.Termios) {
	fmt.Printf("Iflag %d\n", termio.Iflag)
	fmt.Printf("Oflag %d\n", termio.Oflag)
	fmt.Printf("Cflag %d\n", termio.Cflag)
	fmt.Printf("Lflag %d\n", termio.Lflag)
	fmt.Printf("Line %d\n", termio.Line)
	fmt.Printf("Ispeed %d\n", termio.Ispeed)
	for i, Cc := range(termio.Cc) {
		fmt.Printf("Cc[%02x] %d\n", i, Cc)
	}
	fmt.Printf("Ospeed %d\n", termio.Ospeed)
}

func main() {
	device := 0

	termio, err := unix.IoctlGetTermios(device, unix.TCGETS)
	if err != nil {
		log.Fatal(err)
	}
	termio.Lflag &= ^uint32(unix.ECHO)
	termio.Lflag &= ^uint32(unix.ICANON)
	showTermio(termio)



	err = unix.IoctlSetTermios(device, unix.TCSETS, termio)
	if err != nil {
		log.Fatal(err)
	}

	b := make([]byte, 1)
	for {
		os.Stdin.Read(b)
		fmt.Println(b)
	}
}
