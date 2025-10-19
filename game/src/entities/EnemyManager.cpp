#include "EnemyManager.h"
#include "Enemy.h"
#include "core/SceneManager.h"
#include "math/Vec2.h"
#include <raylib.h>

EnemyManager::EnemyManager()
{
	this->spawnDelay = 2.0f;
	this->spawnTimer = 0.0f;
}

EnemyManager::~EnemyManager() {}
void EnemyManager::load() {}
void EnemyManager::draw() {}

void EnemyManager::update()
{
	// spawn enemies with timer
	spawnTimer += GetFrameTime();
	if (spawnTimer >= spawnDelay)
	{
		spawnEnemy();
		spawnTimer = 0.0f;
	}
}

void EnemyManager::spawnEnemy()
{
	Enemy *enemy = new Enemy(Vec2::zero());
	enemy->load();
	SceneManager::addEntity(enemy);
}
