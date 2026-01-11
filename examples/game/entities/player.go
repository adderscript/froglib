package entities

import (
	"froglib/assets"
	. "froglib/components"
	"froglib/input"
	. "froglib/math"

	"github.com/hajimehoshi/ebiten/v2"
)

type Player struct {
	*Transform
	*Rigidbody
	sprite *Sprite

	speed  float64
	origin Vec2
}

func NewPlayer(x, y float64) *Player {
	player := Player{
		Transform: NewTransform(NewVec2(0.0, 0.0), 2.0, 0.0),
		Rigidbody: NewRigidbody(1.0, 0.5, false),
		sprite:    NewSprite(assets.GetImage("player")),

		speed:  1.0,
		origin: NewVec2(0.5, 0.5),
	}

	return &player
}

func (p *Player) Update() {
	// handle movement
	dir := input.GetVector(ebiten.KeyA, ebiten.KeyD, ebiten.KeyW, ebiten.KeyS)
	p.ApplyForce(dir.Scale(p.speed))

	p.Integrate(&p.Position)
}

func (p *Player) Draw(screen *ebiten.Image) {
	options := &ebiten.DrawImageOptions{}
	p.Apply(options, p.sprite.Size(), p.origin)

	p.sprite.Draw(screen, options)
}
