#pragma once

#include <vie/Graphics.h>

class Map
{
public:
	Map();
	~Map();

	void render(vie::Graphics* g);

private:
	const float TILE_SIZE;
};

