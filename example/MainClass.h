#pragma once

#include <vie/Engine.h>
#include <vie/Texture.h>
#include <vie/Timer.h>
#include <vie/Sound.h>

class Map;
class CarFollower;
class Renderer;

class MainClass : public vie::Engine
{
public:
	MainClass();
	~MainClass();

	void onKeyRelease();
	void onMouseClick();

	void onCreate();
	void update(float et);
	void render(vie::Graphics* g);

	void onLog(const std::string& logMsg);
	void onFatalError(const std::string& errMsg);

private:
	Map* mainMap;
	CarFollower* carFollower;
	Renderer* renderer;
	vie::Timer fpsPrintTimer;

	void logToFile(const std::string& logMsg);
	std::string getCurrentDate();
};