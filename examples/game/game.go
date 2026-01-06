package main

import (
	. "froglib/examples/game/entities"

	"github.com/hajimehoshi/ebiten/v2"
)

type Game struct {
	player *Player
}

func NewGame() *Game {
	game := Game{
		player: NewPlayer(100.0, 100.0),
	}

	return &game
}

func (g *Game) Update() error {
	g.player.Update()

	return nil
}

func (g *Game) Draw(screen *ebiten.Image) {
	g.player.Draw(screen)
}

func (g *Game) Layout(outsideWidth, outsideHeight int) (int, int) {
	return 640, 480
}
