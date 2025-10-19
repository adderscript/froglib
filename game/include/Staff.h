#pragma once
#include "Player.h"
#include "entities/Entity.h"
#include "math/Vec2.h"
#include <raylib.h>

class Staff : public Entity
{
  public:
	Staff();
	~Staff();

	void load() override;
	void update() override;
	void draw() override;

  private:
	void shoot();

	Vec2 position;
	float scale;
	float rotation;

	float distance;

	float shootDelay;
	float shootTimer;
	float shootForce;

	Texture2D texture;
	Vec2 origin;
	float rotationOffset;

	Player *player;
};
