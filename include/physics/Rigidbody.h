#pragma once
#include "math/Vec2.h"

class Rigidbody
{
  public:
	Vec2 velocity;
	Vec2 acceleration;
	float mass;
	float inverseMass;
	float drag;
	bool isStatic;

	Rigidbody();
	Rigidbody(float mass, float drag, bool isStatic);
	~Rigidbody();

	void applyForce(const Vec2 &force);
	void applyImpulse(const Vec2 &impulse);
	void integrate(Vec2 &position, float dt);
};
