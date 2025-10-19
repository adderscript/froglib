#pragma once
#include "Player.h"
#include "core/Game.h"

class Game1 : public Game
{
  public:
	Game1();
	~Game1();

	void load() override;
	void unload() override;
	void update() override;
	void draw() override;
};
