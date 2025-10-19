#pragma once
#include "entities/Entity.h"
#include "math/Vec2.h"
#include "physics/CircleCollider.h"
#include "physics/Rigidbody.h"
#include <raylib.h>

class Bullet : public Entity
{
  public:
	Bullet(Vec2 position, float rotation);
	~Bullet();

	void load() override;
	void update() override;
	void draw() override;

	Rigidbody *getRigidbody() { return &rigidbody; }

  private:
	Vec2 position;
	float scale;
	float rotation;

	float damage;
	float knockbackForce;

	CircleCollider collider;
	Rigidbody rigidbody;

	Texture2D texture;
	Vec2 origin;
};
