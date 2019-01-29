#pragma once

#include <vie/Engine.h>
#include <vie/Texture.h>
#include <vie/Timer.h>

class Map;
class CarFollower;

class MainClass : public vie::Engine
{
public:
	MainClass();
	~MainClass();


	void onCreate() override;
	void update(float et) override;
	void render(vie::Graphics* g) override;

	void onKeyPress() override;
	void onKeyRelease() override;

private:
	Map* map;
	CarFollower* carFollower;
	vie::Timer someTimer;

	void renderChessboard(vie::Graphics* g);
	void renderAxis(vie::Graphics* g);
};