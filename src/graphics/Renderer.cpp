#include "graphics/Renderer.h"
#include "math/Vec2.h"
#include <cmath>
#include <raylib.h>

void Renderer::drawTexture(Texture2D texture, Vec2 position, Vec2 scale,
						   float rotation, Vec2 originRatio, Color color)
{
	Rectangle source = {0.0f, 0.0f, (float)texture.width,
						(float)texture.height};
	Rectangle dest = {position.x, position.y, texture.width * scale.x,
					  texture.height * scale.y};
	Vector2 origin = {texture.width * originRatio.x * scale.x,
					  texture.height * originRatio.y * scale.y};

	DrawTexturePro(texture, source, dest, origin, rotation * (180.0f / M_PI),
				   color);
}

void Renderer::drawTexture(Texture2D texture, Vec2 position, float scale,
						   float rotation, Vec2 originRatio, Color color)
{
	// Just call the main one, wrapping the float scale in a Vec2
	drawTexture(texture, position, Vec2(scale, scale), rotation, originRatio,
				color);
}
