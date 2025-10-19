#include "physics/PhysicsManager.h"
#include "math/Vec2.h"
#include "physics/Rigidbody.h"
#include <algorithm>
#include <atomic>
#include <chrono>
#include <mutex>
#include <thread>
#include <vector>

// Static member initialization
std::thread PhysicsManager::physicsThread;
std::atomic<bool> PhysicsManager::running(false);
std::atomic<bool> PhysicsManager::shouldStop(false);
std::vector<PhysicsBody> PhysicsManager::bodies;
std::mutex PhysicsManager::bodiesMutex;
float PhysicsManager::fixedTimestep = 1.0f / 60.0f;
float PhysicsManager::accumulator = 0.0f;

void PhysicsManager::init(float timestep)
{
	if (running)
	{
		return; // Already running
	}

	fixedTimestep = timestep;
	accumulator = 0.0f;
	shouldStop = false;
	running = true;

	// Start the physics thread
	physicsThread = std::thread(physicsLoop);
}

void PhysicsManager::shutdown()
{
	if (!running)
	{
		return;
	}

	// Signal the thread to stop
	shouldStop = true;

	// Wait for the thread to finish
	if (physicsThread.joinable())
	{
		physicsThread.join();
	}

	running = false;

	// Clear all bodies
	std::lock_guard<std::mutex> lock(bodiesMutex);
	bodies.clear();
}

void PhysicsManager::registerBody(int entityId, Rigidbody *rigidbody,
								  Vec2 *position)
{
	std::lock_guard<std::mutex> lock(bodiesMutex);

	// Check if already registered
	for (const auto &body : bodies)
	{
		if (body.entityId == entityId)
		{
			return; // Already registered
		}
	}

	// Add new body
	PhysicsBody body;
	body.entityId = entityId;
	body.rigidbody = rigidbody;
	body.position = position;
	bodies.push_back(body);
}

void PhysicsManager::unregisterBody(int entityId)
{
	std::lock_guard<std::mutex> lock(bodiesMutex);

	bodies.erase(std::remove_if(bodies.begin(), bodies.end(),
								[entityId](const PhysicsBody &body)
								{ return body.entityId == entityId; }),
				 bodies.end());
}

bool PhysicsManager::isRunning() { return running; }

float PhysicsManager::getTimestep() { return fixedTimestep; }

void PhysicsManager::physicsLoop()
{
	using clock = std::chrono::high_resolution_clock;
	auto lastTime = clock::now();

	while (!shouldStop)
	{
		auto currentTime = clock::now();
		float deltaTime = std::chrono::duration<float>(currentTime - lastTime)
							  .count();
		lastTime = currentTime;

		// Accumulate time
		accumulator += deltaTime;

		// Fixed timestep updates
		while (accumulator >= fixedTimestep)
		{
			updatePhysics(fixedTimestep);
			accumulator -= fixedTimestep;
		}

		// Sleep briefly to avoid busy-waiting
		std::this_thread::sleep_for(std::chrono::microseconds(100));
	}
}

void PhysicsManager::updatePhysics(float dt)
{
	std::lock_guard<std::mutex> lock(bodiesMutex);

	// Update all physics bodies
	for (auto &body : bodies)
	{
		if (body.rigidbody && body.position && !body.rigidbody->isStatic)
		{
			body.rigidbody->integrate(*body.position, dt);
		}
	}
}
