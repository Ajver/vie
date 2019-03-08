#include "Tile.h"

#include <iostream>

#include <vie/FileManager.h>
#include <vie/Random.h>

vie::Texture Tile::X_TEXTURE;
vie::Texture Tile::O_TEXTURE;

Tile::Tile()
{
}

Tile::~Tile()
{
}

void Tile::loadTextures()
{
	X_TEXTURE = vie::FileManager::getTexture("Graphics/x.png");
	O_TEXTURE = vie::FileManager::getTexture("Graphics/o.png");
}

void Tile::onMousePress()
{
	if(vie::Random::nextInt(2) == 0)
		state = TileState::X;
	else
		state = TileState::O;
}

void Tile::render(vie::Graphics* g)
{
	if (isMouseHover)
		g->setColor(vie::COLOR::WHITE);
	else
		g->setColor(vie::COLOR::LIGHT_GRAY);

	g->fillRect(position, size);

	g->setColor(vie::COLOR::GRAY);
	g->drawRect(position, size, 4.0f);

	switch (state)
	{
	case TileState::X:
		g->drawTexture(X_TEXTURE, position, size);
		break;
	case TileState::O:
		g->drawTexture(O_TEXTURE, position, size);
		break;
	}
}