#pragma once

#include <vie/Graphics.h>

namespace vie
{
	class ObjectsManager;
}

class Map
{
public:
	Map(vie::ObjectsManager* om);
	~Map();

	void render(vie::Graphics* g);

private:
	const float TILE_SIZE;
	glm::vec2 size;
};

