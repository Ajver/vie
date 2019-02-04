#include "Map.h"

#include <vie/Window.h>
#include <vie/Graphics.h>
#include <vie/ObjectsManager.h>

Map::Map(vie::ObjectsManager* om) : 
	TILE_SIZE(200.0f),
	size(vie::Window::getScreenSize() * 6.0f)
{
	for (int i = 0; i < size.y; i += TILE_SIZE * 2.0f)
		for (int j = 0; j < size.x; j += TILE_SIZE * 2.0f)
		{
			vie::Object* o = new vie::Object();
			o->setPosition({ j, i });
			o->setSize({ TILE_SIZE, TILE_SIZE });
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
	for (int i = 0; i < size.y; i += TILE_SIZE * 2.0f)
		for (int j = 0; j < size.x; j += TILE_SIZE * 2.0f)
		{
			g->fillRect(glm::vec2(j, i), glm::vec2(TILE_SIZE, TILE_SIZE));
		}

	g->translate(size * 0.5f);
}