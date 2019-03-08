#pragma once

#include <vie/Object.h>

enum TileState
{
	EMPTY,
	X,
	O
};


class Tile : public vie::Object
{
public:
	Tile();
	~Tile();
	
	static void loadTextures();

	void render(vie::Graphics* g);
	void onMousePress();

private:
	TileState state;

	static vie::Texture X_TEXTURE;
	static vie::Texture O_TEXTURE;

};

