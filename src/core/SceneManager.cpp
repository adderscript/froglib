#include "core/SceneManager.h"
#include "entities/Entity.h"
#include <algorithm>
#include <memory>
#include <vector>

int SceneManager::idCounter = 1;
std::vector<std::unique_ptr<Entity>> SceneManager::entities;

void SceneManager::update()
{
	for (int i = entities.size() - 1; i >= 0; i--) entities[i]->update();
}

void SceneManager::draw()
{
	for (auto &entity : entities) entity->draw();
}

void SceneManager::addEntity(Entity *entity)
{
	entity->setId(idCounter);
	entity->load();
	entities.emplace_back(entity);

	idCounter++;
}

void SceneManager::deleteEntity(Entity *entity)
{
	int id = entity->getId();
	entities.erase(std::remove_if(entities.begin(), entities.end(),
								  [id](const std::unique_ptr<Entity> &entity)
								  { return entity->getId() == id; }),
				   entities.end());
}
