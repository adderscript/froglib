package main

import (
	"log"

	"github.com/hajimehoshi/ebiten/v2"
)

func main() {
	ebiten.SetWindowSize(1280.0, 960.0)
	ebiten.SetWindowTitle("Game")

	if err := ebiten.RunGame(NewGame()); err != nil {
		log.Fatal(err)
	}
}
