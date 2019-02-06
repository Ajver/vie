#pragma once

#include <vie/Graphics.h>

class b2World;
namespace vie
{
	class ObjectsManager;
}

class Map
{
public:
	Map(vie::ObjectsManager* om, b2World* b_world);
	~Map();

	void render(vie::Graphics* g);

private:
	const float TILE_SIZE;
	glm::vec2 size;
};

