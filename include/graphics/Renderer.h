#pragma once
#include "math/Vec2.h"
#include <raylib.h>

class Renderer
{
  public:
	static void drawTexture(Texture2D texture, Vec2 position, Vec2 scale,
							float rotation, Vec2 originRatio, Color color);

	static void drawTexture(Texture2D texture, Vec2 position, float scale,
							float rotation, Vec2 originRatio, Color color);
};
