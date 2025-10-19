#pragma once

class Game
{
  public:
	Game();
	~Game();

	void run();

	virtual void load() = 0;
	virtual void unload() = 0;
	virtual void update() = 0;
	virtual void draw() = 0;
};
