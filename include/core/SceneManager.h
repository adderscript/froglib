#pragma once
#include "entities/Entity.h"
#include <memory>
#include <string>
#include <vector>

class SceneManager
{
  public:
	static void load();
	static void update();
	static void draw();

	static void addEntity(Entity *entity);
	static void deleteEntity(Entity *entity);
	template <typename T> static T *getEntity(const std::string &tag);
	template <typename T>
	static std::vector<T *> getEntities(const std::string &tag);

  private:
	static std::vector<std::unique_ptr<Entity>> entities;
	static int idCounter;
};

// Template implementation must be in header file
template <typename T> T *SceneManager::getEntity(const std::string &tag)
{
	for (auto &entity : entities)
	{
		if (entity->getTag() == tag)
		{
			return dynamic_cast<T *>(entity.get());
		}
	}
	return nullptr;
}

template <typename T>
std::vector<T *> SceneManager::getEntities(const std::string &tag)
{
	std::vector<T *> toReturn = std::vector<T *>();

	for (auto &entity : entities)
	{
		if (entity->getTag() == tag)
		{
			toReturn.push_back(dynamic_cast<T *>(entity.get()));
		}
	}
	return toReturn;
}
