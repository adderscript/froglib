package components

import (
	"math"

	. "froglib/math"

	"github.com/hajimehoshi/ebiten/v2"
)

type Transform struct {
	Position Vec2
	Scale    float64
	Rotation float64
}

func NewTransform(position Vec2, scale, rotation float64) *Transform {
	transform := Transform{
		Position: position,
		Scale:    scale,
		Rotation: rotation,
	}

	return &transform
}

func (t *Transform) Forward() Vec2 {
	vec2 := NewVec2(
		math.Cos(t.Rotation),
		math.Sin(t.Rotation),
	)

	return vec2
}

func (t *Transform) Apply(options *ebiten.DrawImageOptions, size, origin Vec2) {
	options.GeoM.Translate(-float64(size.X)*origin.X, -float64(size.Y)*origin.Y)
	options.GeoM.Scale(t.Scale, t.Scale)
	options.GeoM.Rotate(t.Rotation)
	options.GeoM.Translate(t.Position.X, t.Position.Y)
}
