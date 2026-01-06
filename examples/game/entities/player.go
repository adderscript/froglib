package entities

import (
	"log"

	. "froglib/components"
	"froglib/input"
	. "froglib/math"

	"github.com/hajimehoshi/ebiten/v2"
	"github.com/hajimehoshi/ebiten/v2/ebitenutil"
)

type Player struct {
	*Transform
	*Rigidbody
	sprite *Sprite

	speed  float64
	origin Vec2
}

func NewPlayer(x, y float64) *Player {
	image, _, err := ebitenutil.NewImageFromFile("examples/game/assets/player.png")
	if err != nil {
		log.Fatal(err)
	}

	player := Player{
		Transform: NewTransform(NewVec2(0.0, 0.0), 2.0, 0.0),
		Rigidbody: NewRigidbody(1.0, 0.5, false),
		sprite:    NewSprite(image),

		speed:  2.5,
		origin: NewVec2(0.5, 0.5),
	}

	return &player
}

func (p *Player) Update() {
	// get input
	dir := input.GetVector(ebiten.KeyA, ebiten.KeyD, ebiten.KeyW, ebiten.KeyS)
	p.ApplyForce(dir.Scale(p.speed))

	p.Integrate(&p.Position)
}

func (p *Player) Draw(screen *ebiten.Image) {
	options := &ebiten.DrawImageOptions{}
	p.Apply(options, p.sprite.Size(), p.origin)

	p.sprite.Draw(screen, options)
}
