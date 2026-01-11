package math

import (
	"image"

	"github.com/hajimehoshi/ebiten/v2"
)

func BoolToFloat(value bool) float64 {
	if value {
		return 1.0
	}
	return 0.0
}

func SliceSpriteSheet(spriteSheet *ebiten.Image, frameCount int) []*ebiten.Image {
	sheetWidth, sheetHeight := spriteSheet.Size()
	frameWidth := sheetWidth / frameCount

	frames := make([]*ebiten.Image, frameCount)

	for frameIndex := 0; frameIndex < frameCount; frameIndex++ {
		x := frameIndex * frameWidth
		frameRect := image.Rect(
			x,
			0,
			x+frameWidth,
			sheetHeight,
		)
		frames[frameIndex] = spriteSheet.SubImage(frameRect).(*ebiten.Image)
	}

	return frames
}
