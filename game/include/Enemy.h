#pragma once
#include "Player.h"
#include "entities/Entity.h"
#include "math/Vec2.h"
#include "physics/CircleCollider.h"
#include "physics/Rigidbody.h"
#include <raylib.h>

class Enemy : public Entity
{
  public:
	Enemy(Vec2 position);
	~Enemy();

	void load() override;
	void update() override;
	void draw() override;

	void takeDamage(float amount, Vec2 damagerPosition, float knockbackForce);

	CircleCollider getCollider() { return collider; }

  private:
	Vec2 position;
	float scale;
	float rotation;

	float speed;

	float maxHealth;
	float health;

	CircleCollider collider;
	Rigidbody rigidbody;

	Texture2D texture;
	Vec2 origin;

	Player *player;
};
