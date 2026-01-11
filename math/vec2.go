package math

import "math"

type Vec2 struct {
	X, Y float64
}

func NewVec2(x, y float64) Vec2 {
	vec2 := Vec2{
		X: x, Y: y,
	}

	return vec2
}

func (v Vec2) Add(other Vec2) Vec2 {
	return NewVec2(
		v.X+other.X,
		v.Y+other.Y,
	)
}

func (v *Vec2) AddInPlace(other Vec2) {
	v.X += other.X
	v.Y += other.Y
}

func (v Vec2) Subtract(other Vec2) Vec2 {
	return NewVec2(
		v.X-other.X,
		v.Y-other.Y,
	)
}

func (v Vec2) Scale(scalar float64) Vec2 {
	return NewVec2(
		v.X*scalar,
		v.Y*scalar,
	)
}

func (v Vec2) Length() float64 {
	return math.Hypot(v.X, v.Y)
}
