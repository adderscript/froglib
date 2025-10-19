#include "Staff.h"
#include "Bullet.h"
#include "Player.h"
#include "core/SceneManager.h"
#include "graphics/AssetManager.h"
#include "graphics/Renderer.h"
#include "math/Vec2.h"
#include <cmath>
#include <raylib.h>

Staff::Staff()
{
	this->tag = "staff";

	this->position = Vec2::zero();
	this->scale = 4.0f;
	this->rotation = 0.0f;

	this->distance = 30.0f;

	this->shootForce = 500.0f;
	this->shootDelay = 0.35f;
	this->shootTimer = 0.0f;

	this->origin = Vec2(0.5f, 0.5f);
	this->rotationOffset = 0.0f;
}

Staff::~Staff() { UnloadTexture(texture); }

void Staff::load()
{
	texture = AssetManager::loadTexture("assets/sprites/staff.png");
	player = SceneManager::getEntity<Player>("player");
}

void Staff::update()
{
	// point towards mouse
	Vec2 diff =
		Vec2((Vec2)GetMousePosition() - player->getPosition()).normalized();
	rotation = atan2(diff.y, diff.x);

	// rotate around player
	position =
		player->getPosition() + Vec2(cos(rotation), sin(rotation)) * distance;

	// handle shooting with timer
	shootTimer += GetFrameTime();
	if (IsMouseButtonDown(MOUSE_LEFT_BUTTON) && shootTimer >= shootDelay)
	{
		shoot();
		shootTimer = 0.0f;
	}
}

void Staff::draw()
{
	Renderer::drawTexture(texture, position, scale, rotation + rotationOffset,
						  origin, WHITE);
}

void Staff::shoot()
{
	Bullet *bullet = new Bullet(position, rotation);

	// apply force in facing direction
	Vec2 dir = Vec2(cos(rotation), sin(rotation)).normalized();
	bullet->getRigidbody()->applyImpulse(dir * shootForce);

	SceneManager::addEntity(bullet);
}
