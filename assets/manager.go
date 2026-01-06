package assets

import (
	"log"

	"github.com/hajimehoshi/ebiten/v2"
	"github.com/hajimehoshi/ebiten/v2/ebitenutil"
)

var images = make(map[string]*ebiten.Image)

func CacheImage(path, key string) {
	image, _, err := ebitenutil.NewImageFromFile(path)
	if err != nil {
		log.Fatal(err)
	}

	// asign image to key
	images[key] = image
}

func GetImage(key string) *ebiten.Image {
	return images[key]
}
