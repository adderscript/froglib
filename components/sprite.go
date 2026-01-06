package components

import (
	. "froglib/math"

	"github.com/hajimehoshi/ebiten/v2"
)

type Sprite struct {
	image *ebiten.Image
}

func NewSprite(image *ebiten.Image) *Sprite {
	sprite := Sprite{
		image: image,
	}

	return &sprite
}

func (s *Sprite) Draw(screen *ebiten.Image, options *ebiten.DrawImageOptions) {
	screen.DrawImage(s.image, options)
}

func (s Sprite) Size() Vec2 {
	size := NewVec2(
		float64(s.image.Bounds().Dx()),
		float64(s.image.Bounds().Dy()),
	)

	return size
}
