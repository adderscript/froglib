#pragma once
#include "entities/Entity.h"

class EnemyManager : public Entity
{
  public:
	EnemyManager();
	~EnemyManager();

	void load() override;
	void update() override;
	void draw() override;

  private:
	void spawnEnemy();

	float spawnDelay;
	float spawnTimer;
};
