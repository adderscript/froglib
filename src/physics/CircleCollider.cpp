#include "physics/CircleCollider.h"
#include "math/Vec2.h"
#include <raylib.h>

CircleCollider::CircleCollider(Vec2 position, float radius)
{
	this->position = position;
	this->radius = radius;
}

CircleCollider::~CircleCollider() {}

bool CircleCollider::overlaps(CircleCollider other)
{
	Vec2 diff(other.position.x - position.x, other.position.y - position.y);
	float dist = diff.x * diff.x + diff.y * diff.y;
	return dist < (radius + other.radius) * (radius + other.radius);
}

void CircleCollider::debugDraw(Color color)
{
	DrawCircleV(position, radius, color);
}
