#include "Map.h"

#include <vie/Window.h>
#include <vie/Graphics.h>


Map::Map() : 
	TILE_SIZE(200.0f)
{
	size.x = vie::Window::getScreenWidth() * 6.0f;
	size.y = vie::Window::getScreenHeight() * 6.0f;
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