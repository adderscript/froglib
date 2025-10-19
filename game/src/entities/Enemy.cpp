#include "Enemy.h"
#include "Player.h"
#include "core/SceneManager.h"
#include "graphics/AssetManager.h"
#include "graphics/Renderer.h"
#include "math/Vec2.h"
#include "physics/CircleCollider.h"
#include "physics/PhysicsManager.h"
#include "physics/Rigidbody.h"
#include <raylib.h>

Enemy::Enemy(Vec2 position)
{
	this->tag = "enemy";

	this->position = position;
	this->scale = 4.0f;
	this->rotation = 0.0f;

	this->speed = 500.0f;

	this->maxHealth = 2.0f;
	this->health = maxHealth;

	this->collider = CircleCollider(position, 10.0f);
	this->rigidbody = Rigidbody(1.0f, 2.5f, false);

	this->origin = Vec2(0.5f, 0.5f);
}

Enemy::~Enemy()
{
	PhysicsManager::unregisterBody(id);
	UnloadTexture(texture);
}

void Enemy::load()
{
	texture = AssetManager::loadTexture("assets/sprites/enemy.png");
	player = SceneManager::getEntity<Player>("player");
	PhysicsManager::registerBody(id, &rigidbody, &position);
}

void Enemy::update()
{
	// move towards player
	Vec2 dir = Vec2(player->getPosition() - position).normalized();
	rigidbody.applyForce(dir * speed);
	collider.setPosition(position);

	// check if out of health
	if (health <= 0.0f) SceneManager::deleteEntity(this);
}

void Enemy::draw()
{
	Renderer::drawTexture(texture, position, scale, rotation, origin, WHITE);
}

void Enemy::takeDamage(float amount, Vec2 damagerPosition, float knockbackForce)
{
	health -= amount;

	// apply knockback
	Vec2 dir = Vec2(position - damagerPosition).normalized();
	rigidbody.applyImpulse(dir * knockbackForce);
}
