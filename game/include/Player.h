#pragma once
#include "entities/Entity.h"
#include "math/Vec2.h"
#include "physics/CircleCollider.h"
#include "physics/Rigidbody.h"
#include <raylib.h>

class Player : public Entity
{
  public:
	Player(Vec2 position);
	~Player();

	void load() override;
	void update() override;
	void draw() override;

	Vec2 getPosition() { return position; }

  private:
	Vec2 position;
	float scale;
	float rotation;

	float speed;

	CircleCollider collider;
	Rigidbody rigidbody;

	Texture2D texture;
	Vec2 origin;
};
