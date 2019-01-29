#pragma once

#include <vie/Engine.h>
#include <vie/Texture.h>

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

private:
	Map* map;
	CarFollower* carFollower;
};