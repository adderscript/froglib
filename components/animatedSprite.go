package components

import (
	. "froglib/math"

	"github.com/hajimehoshi/ebiten/v2"
)

type Animation struct {
	frames        []*ebiten.Image
	frameDuration float64
	looping       bool
}

func NewAnimation(frames []*ebiten.Image, frameDuration float64, looping bool) *Animation {
	animation := Animation{
		frames:        frames,
		frameDuration: frameDuration,
		looping:       looping,
	}

	return &animation
}

type AnimatedSprite struct {
	currentAnimation *Animation
	currentFrame     int
	frameTimer       float64
	playing          bool
}

func NewAnimatedSprite() *AnimatedSprite {
	animatedSprite := AnimatedSprite{
		playing: true,
	}

	return &animatedSprite
}

func (as *AnimatedSprite) Play(animation *Animation) {
	if as.currentAnimation == animation {
		return
	}

	as.currentAnimation = animation
	as.currentFrame = 0
	as.frameTimer = 0
	as.playing = true
}

func (as *AnimatedSprite) Update() {
	if !as.playing || as.currentAnimation == nil {
		return
	}

	as.frameTimer += 1.0 / 60.0

	for as.frameTimer >= as.currentAnimation.frameDuration {
		as.frameTimer -= as.currentAnimation.frameDuration
		as.currentFrame++

		if as.currentFrame >= len(as.currentAnimation.frames) {
			if as.currentAnimation.looping {
				as.currentFrame = 0
			} else {
				as.currentFrame = len(as.currentAnimation.frames) - 1
				as.playing = false
				break
			}
		}
	}
}

func (as *AnimatedSprite) Draw(
	screen *ebiten.Image,
	options *ebiten.DrawImageOptions,
) {
	if as.currentAnimation == nil {
		return
	}

	frame := as.currentAnimation.frames[as.currentFrame]
	screen.DrawImage(frame, options)
}

func (as *AnimatedSprite) Size() Vec2 {
	size := NewVec2(
		float64(as.currentAnimation.frames[0].Bounds().Dx()),
		float64(as.currentAnimation.frames[0].Bounds().Dy()),
	)

	return size
}
