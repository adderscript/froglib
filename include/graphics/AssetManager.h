#pragma once
#include <raylib.h>
#include <string>

class AssetManager
{
  public:
	static Texture2D loadTexture(const std::string &filePath);
};
