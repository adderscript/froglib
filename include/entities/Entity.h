#pragma once

#include <string>
class Entity
{
  public:
	Entity() = default;
	virtual ~Entity() = default;

	virtual void load() = 0;
	virtual void update() = 0;
	virtual void draw() = 0;

	void setId(int newId) { id = newId; }
	int getId() { return id; }
	std::string getTag() { return tag; }

  protected:
	int id;
	std::string tag;
};
