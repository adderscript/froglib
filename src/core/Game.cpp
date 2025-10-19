#include "core/Game.h"
#include <raylib.h>

Game::Game() {}
Game::~Game() {}

void Game::run()
{
	load();

	while (!WindowShouldClose())
	{
		update();
		BeginDrawing();
		draw();
		EndDrawing();
	}

	unload();
}
