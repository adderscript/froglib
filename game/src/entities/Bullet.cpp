#include "Bullet.h"
#include "Enemy.h"
#include "core/SceneManager.h"
#include "graphics/AssetManager.h"
#include "graphics/Renderer.h"
#include "math/Vec2.h"
#include "physics/CircleCollider.h"
#include "physics/PhysicsManager.h"
#include "physics/Rigidbody.h"
#include <raylib.h>
#include <vector>

Bullet::Bullet(Vec2 position, float rotation)
{
	this->position = position;
	this->scale = 4.0f;
	this->rotation = rotation;

	this->damage = 1.0f;
	this->knockbackForce = 350.0f;

	this->collider = CircleCollider(position, 7.5f);
	this->rigidbody = Rigidbody(1.0f, 0.0f, false);

	this->origin = Vec2(0.5f, 0.5f);
}

Bullet::~Bullet()
{
	PhysicsManager::unregisterBody(id);
	UnloadTexture(texture);
}

void Bullet::load()
{
	texture = AssetManager::loadTexture("assets/sprites/bullet.png");
	PhysicsManager::registerBody(id, &rigidbody, &position);
}

void Bullet::update()
{
	// update collider position
	collider.setPosition(position);

	// check collision
	std::vector<Enemy *> enemies = SceneManager::getEntities<Enemy>("enemy");
	for (auto &enemy : enemies)
	{
		if (collider.overlaps(enemy->getCollider()))
		{
			enemy->takeDamage(damage, position, knockbackForce);
			SceneManager::deleteEntity(this);
		}
	}
}

void Bullet::draw()
{
	Renderer::drawTexture(texture, position, scale, rotation, origin, WHITE);
}
