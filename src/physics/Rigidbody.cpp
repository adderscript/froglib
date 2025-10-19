#include "physics/Rigidbody.h"
#include "math/Vec2.h"

Rigidbody::Rigidbody()
{
	this->velocity = Vec2::zero();
	this->acceleration = Vec2::zero();
	this->mass = 1.0f;
	this->drag = 0.1f;
	this->isStatic = false;
	this->inverseMass = (isStatic || mass == 0.0f) ? 0.0f : 1.0f / mass;
}

Rigidbody::Rigidbody(float mass, float drag, bool isStatic)
{
	this->velocity = Vec2::zero();
	this->acceleration = Vec2::zero();
	this->mass = mass;
	this->drag = drag;
	this->isStatic = isStatic;
	this->inverseMass = (isStatic || mass == 0.0f) ? 0.0f : 1.0f / mass;
}

Rigidbody::~Rigidbody() {}

void Rigidbody::applyForce(const Vec2 &force)
{
	if (isStatic) return;
	acceleration += force * inverseMass;
}

void Rigidbody::applyImpulse(const Vec2 &impulse)
{
	if (isStatic) return;
	velocity += impulse * inverseMass;
}

void Rigidbody::integrate(Vec2 &position, float dt)
{
	if (isStatic) return;

	// update velocity and position
	velocity += acceleration * dt;
	position += velocity * dt;

	// apply drag
	velocity *= (1.0f - drag * dt);

	// reset acceleration for next frame
	acceleration = Vec2(0, 0);
}
