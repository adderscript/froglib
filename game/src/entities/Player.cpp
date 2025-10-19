#include "Player.h"
#include "graphics/AssetManager.h"
#include "graphics/Renderer.h"
#include "math/Vec2.h"
#include "physics/CircleCollider.h"
#include "physics/PhysicsManager.h"
#include "physics/Rigidbody.h"
#include <raylib.h>

Player::Player(Vec2 position)
{
	this->tag = "player";

	this->position = position;
	this->scale = 4.0f;
	this->rotation = 0.0f;

	this->speed = 1500.0f;

	this->collider = CircleCollider(position, 10.0f);
	this->rigidbody = Rigidbody(1.0f, 7.5f, false);

	this->origin = Vec2(0.5f, 0.5f);
}

Player::~Player()
{
	PhysicsManager::unregisterBody(id);
	UnloadTexture(texture);
}

void Player::load()
{
	texture = AssetManager::loadTexture("assets/sprites/player.png");
	PhysicsManager::registerBody(id, &rigidbody, &position);
}

void Player::update()
{
	// get input
	Vec2 input = Vec2::zero();
	if (IsKeyDown(KEY_D)) input.x += 1.0f;
	if (IsKeyDown(KEY_A)) input.x -= 1.0f;
	if (IsKeyDown(KEY_S)) input.y += 1.0f;
	if (IsKeyDown(KEY_W)) input.y -= 1.0f;

	// apply forces
	rigidbody.applyForce(input * speed);
	collider.setPosition(position);
}

void Player::draw()
{
	Renderer::drawTexture(texture, position, scale, rotation, origin, WHITE);
}
