package img

import (
	"os"
	"fmt"
	"os/exec"
	"io"
	"image"
	"image/png"
)

func check(e error) {
	if e != nil {
		fmt.Println(e)
		os.Exit(1)
	}
}

func ShowImg() {
	fp, err := os.Open("king.png")
	check(err)
	m, _, err := image.Decode(fp)
	fmt.Println(m.ColorModel())
	check(err)
	wcCmd := exec.Command("imgcat")

	reader, writer := io.Pipe()

	// set the output of "cat" command to pipe writer
	go func() {
		png.Encode(writer, m)
		writer.Close()
	}()
	// set the input of the "wc" command pipe reader
	wcCmd.Stdin = reader

	wcCmd.Stdout = os.Stdout


	wcCmd.Start()


	wcCmd.Wait()
	reader.Close()

}
