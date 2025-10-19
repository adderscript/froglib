#pragma once
#include "math/Vec2.h"
#include <raylib.h>

class CircleCollider
{
  public:
	CircleCollider() = default;
	CircleCollider(Vec2 position, float radius);
	~CircleCollider();

	bool overlaps(CircleCollider other);
	void debugDraw(Color color);

	void setPosition(Vec2 position) { this->position = position; }

  private:
	Vec2 position;
	float radius;
};
