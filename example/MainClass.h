#pragma once

#include <vie/Engine.h>
#include <vie/Texture.h>

#include "Player.h"

class MainClass : public vie::Engine
{
public:
	MainClass();
	~MainClass();

	void onCreate();

	void update(float et) override;
	void render(vie::Graphics* g) override;

	
	void onKeyPress(unsigned int keyID);
	void onKeyRelease(unsigned int keyID);

	/*
	void onMousePress(unsigned int keyID);
	void onMouseRelease(unsigned int keyID);
	void onMouseMove();
	void onMouseDrag();
	*/

private:
};

