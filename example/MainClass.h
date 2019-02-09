#pragma once

#include <vie/Engine.h>
#include <vie/Texture.h>
#include <vie/Timer.h>
#include <vie/Sound.h>
#include <vie/SpriteFont.h>

class Map;
class CarFollower;

class MainClass : public vie::Engine
{
public:
	MainClass();
	~MainClass();

	void onKeyRelease();

	void onCreate();
	void update(float et);
	void render(vie::Graphics* g);

private:
	Map* mainMap;
	CarFollower* carFollower;
	vie::Timer fpsPrintTimer;
	vie::SpriteFont* sf;
};