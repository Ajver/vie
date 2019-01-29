#include "Map.h"

#include <vie/Window.h>
#include <vie/Graphics.h>


Map::Map() : 
	TILE_SIZE(200.0f)
{
}


Map::~Map()
{
}

void Map::render(vie::Graphics* g)
{
	g->setColor(vie::Color(30, 30, 30));
	for (int i = 0; i < vie::Window::getScreenHeight(); i += TILE_SIZE * 2.0f)
		for (int j = 0; j < vie::Window::getScreenWidth(); j += TILE_SIZE * 2.0f)
		{
			g->fillRect(glm::vec2(j, i), glm::vec2(TILE_SIZE, TILE_SIZE));
		}
}