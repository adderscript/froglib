#pragma once
#include "math/Vec2.h"
#include "physics/Rigidbody.h"
#include <atomic>
#include <mutex>
#include <thread>
#include <vector>

// Struct to hold physics data for an entity
struct PhysicsBody
{
	int entityId;
	Rigidbody *rigidbody;
	Vec2 *position; // pointer to the entity's position
};

class PhysicsManager
{
  public:
	// Initialize and start the physics thread
	static void init(float fixedTimestep = 1.0f / 60.0f);

	// Stop the physics thread and clean up
	static void shutdown();

	// Register an entity's physics body with the manager
	static void registerBody(int entityId, Rigidbody *rigidbody,
							 Vec2 *position);

	// Unregister an entity's physics body
	static void unregisterBody(int entityId);

	// Check if physics system is running
	static bool isRunning();

	// Get the current physics timestep
	static float getTimestep();

  private:
	// The physics update loop (runs on separate thread)
	static void physicsLoop();

	// Update all registered physics bodies
	static void updatePhysics(float dt);

	// Thread control
	static std::thread physicsThread;
	static std::atomic<bool> running;
	static std::atomic<bool> shouldStop;

	// Physics bodies and synchronization
	static std::vector<PhysicsBody> bodies;
	static std::mutex bodiesMutex;

	// Fixed timestep
	static float fixedTimestep;
	static float accumulator;
};
