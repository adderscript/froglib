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

	speed float64

	sprite   *AnimatedSprite
	origin   Vec2
	idleAnim *Animation
	runAnim  *Animation
}

func NewPlayer(x, y float64) *Player {
	player := Player{
		Transform: NewTransform(NewVec2(0.0, 0.0), 2.0, 0.0),
		Rigidbody: NewRigidbody(1.0, 0.5, false),

		speed: 2.0,

		sprite: NewAnimatedSprite(),
		origin: NewVec2(0.5, 0.5),
		idleAnim: NewAnimation(
			SliceSpriteSheet(assets.GetImage("playerIdle"), 2),
			0.3,
			true,
		),
		runAnim: NewAnimation(
			SliceSpriteSheet(assets.GetImage("playerRun"), 2),
			0.2,
			true,
		),
	}

	return &player
}

func (p *Player) Update() {
	// handle movement
	dir := input.GetVector(ebiten.KeyA, ebiten.KeyD, ebiten.KeyW, ebiten.KeyS)
	p.ApplyForce(dir.Scale(p.speed))

	// animate
	if dir.Length() != 0.0 {
		p.sprite.Play(p.runAnim)
	} else {
		p.sprite.Play(p.idleAnim)
	}

	p.Integrate(&p.Position)
	p.sprite.Update()
}

func (p *Player) Draw(screen *ebiten.Image) {
	options := &ebiten.DrawImageOptions{}
	p.Apply(options, p.sprite.Size(), p.origin)

	p.sprite.Draw(screen, options)
}
