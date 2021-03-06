#include "Map.h"

#include <vie/Window.h>
#include <vie/Graphics.h>
#include <vie/ObjectsManager.h>

#include "Block.h"

Map::Map(vie::ObjectsManager* om, b2World* b_world) :
	TILE_SIZE(14.0f),
	size(vie::Window::getScreenSize() * 0.5f)
{
	glm::vec2 haflSize = size * 0.5f;
	for (int i = 0; i < size.y; i += TILE_SIZE * 2.0f)
		for (int j = 0; j < size.x; j += TILE_SIZE * 2.0f)
		{
			vie::Object* o = new Block(glm::vec2(j, i) - haflSize, { TILE_SIZE, TILE_SIZE }, b_world);
			om->appendObject(o);
		}
}

Map::~Map()
{
}

void Map::render(vie::Graphics* g)
{
	g->translate(-size * 0.5f);

	g->setColor(vie::COLOR::DARK_GRAY);
	for (int i = -TILE_SIZE * 0.5f; i < size.y; i += TILE_SIZE * 2.0f)
		for (int j = -TILE_SIZE * 0.5f; j < size.x; j += TILE_SIZE * 2.0f)
			g->fillRect({ j, i }, { TILE_SIZE, TILE_SIZE });
			
	g->translate(size * 0.5f);
}