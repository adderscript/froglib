#include "graphics/AssetManager.h"
#include <raylib.h>
#include <stdexcept>
#include <string>

Texture2D AssetManager::loadTexture(const std::string &filePath)
{
	Texture2D texture = LoadTexture(filePath.c_str());
	if (texture.id == 0)
	{
		throw std::runtime_error("Failed to load texture: " + filePath);
	}
	return texture;
}
