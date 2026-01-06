package input

import (
	. "froglib/math"

	"github.com/hajimehoshi/ebiten/v2"
	"github.com/hajimehoshi/ebiten/v2/inpututil"
)

func IsKeyDown(key ebiten.Key) bool {
	return ebiten.IsKeyPressed(key)
}

func IsKeyPressed(key ebiten.Key) bool {
	return inpututil.IsKeyJustPressed(key)
}

func GetVector(negativeX, positiveX, negativeY, positiveY ebiten.Key) Vec2 {
	vec2 := NewVec2(
		BoolToFloat(ebiten.IsKeyPressed(positiveX))-BoolToFloat(ebiten.IsKeyPressed(negativeX)),
		BoolToFloat(ebiten.IsKeyPressed(positiveY))-BoolToFloat(ebiten.IsKeyPressed(negativeY)),
	)

	return vec2
}
