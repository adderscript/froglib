#include "Game1.h"
#include "EnemyManager.h"
#include "Player.h"
#include "Staff.h"
#include "core/SceneManager.h"
#include "math/Vec2.h"
#include "physics/PhysicsManager.h"
#include <raylib.h>

Game1::Game1() {}
Game1::~Game1() {}

void Game1::load()
{
	InitWindow(1280, 720, "Game");
	SetTargetFPS(60);

	// Initialize multi-threaded physics system (60 FPS physics updates)
	PhysicsManager::init(1.0f / 60.0f);

	Player *player = new Player(Vec2::zero());
	SceneManager::addEntity(player);
	Staff *staff = new Staff();
	SceneManager::addEntity(staff);
	EnemyManager *enemyManager = new EnemyManager();
	SceneManager::addEntity(enemyManager);
}

void Game1::unload()
{
	// Shutdown physics thread before closing
	PhysicsManager::shutdown();
	CloseWindow();
}

void Game1::update() { SceneManager::update(); }

void Game1::draw()
{
	ClearBackground(BLACK);
	SceneManager::draw();
}
