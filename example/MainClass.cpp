#include "MainClass.h"

#include <iostream>
#include <fstream>
#include <ctime>

#include <vie/FileManager.h>
#include <vie/Texture.h>
#include <vie/Input.h>
#include <vie/ObjectsManager.h>
#include <vie/Camera2D.h>
#include <vie/Window.h>
#include <vie/Layer.h>
#include <vie/SpriteFont.h>
#include <vie/Logger.h>
#include <Box2D/Box2D.h>

#include "Car.h"
#include "Map.h"
#include "CarFollower.h"
#include "Renderer.h"


MainClass::MainClass() :
	mainMap(nullptr),
	carFollower(nullptr),
	fpsPrintTimer(1000)
{
	runEngine("Example vie Application", 1024, 728, vie::WindowFlags::DEFAULT);
}

MainClass::~MainClass()
{
	delete mainMap;
	delete carFollower;
}

void MainClass::onMouseClick() 
{
	std::cout << "Mouse Click! " << vie::Input::getMousePosition().x << " | " << vie::Input::getMousePosition().y << std::endl;
}

void MainClass::onCreate()
{
	setFPSLimit(60);
	createWorld();

	Car* playerCar = new Car(objectsManager, b_world);
	objectsManager->appendObject(playerCar);
	objectsManager->appendKeyListener(playerCar);

	mainMap = new Map(objectsManager, b_world);
	carFollower = new CarFollower(mainCamera, playerCar);
	renderer = new Renderer();

	graphics->setBackgroundColor(vie::Color(10, 30, 20));

	graphics->createLayer("ground", mainCamera);
	graphics->createLayer("car", mainCamera);
	graphics->createLayer("renderer", renderer->getCamera());

	graphics->switchLayer("ground");
	graphics->getCurrentLayer()->setIsRemovingGlyphs(false);
	mainMap->render(graphics);

	mainCamera->setScale(24.0f);

	graphics->setFont(new vie::SpriteFont("Fonts/calibri.ttf", 64));
}

void MainClass::update(float et)
{	
	objectsManager->update(et);
	carFollower->update(et);
	renderer->update();

	if (fpsPrintTimer.tick())
	{
		fpsPrintTimer.restart();
		std::cout << "FPS: " << getFpsCount() << std::endl;
	}
}

void MainClass::render(vie::Graphics* g)
{
	graphics->switchLayer("car");
	objectsManager->render(g);

	if(vie::Input::isKeyPressed(SDLK_t))
		renderer->render(g);
}

void MainClass::onKeyRelease()
{
	switch (vie::Input::getLastKey())
	{
	case SDLK_ESCAPE:
		destroyEngine();
		break;
	case SDLK_l:
		vie::Logger::log("Test log...");
		break;
	case SDLK_k:
		vie::Logger::fatalError("Test error!");
		break;
	}
}

void MainClass::onLog(const std::string& logMsg)
{
	logToFile("LOG: " + logMsg);
}

void MainClass::onFatalError(const std::string& errMsg)
{
	logToFile("FATAL ERROR: " + errMsg);
}

void MainClass::logToFile(const std::string& logMsg)
{
	std::string date = getCurrentDate();
	std::string lineToSave = "At " + date + ": " + logMsg;

	std::ofstream file;
	file.open("vielogs.log", std::ios::out | std::ios::app);

	if (file.good())
		file << lineToSave << std::endl;

	file.close();
}

std::string MainClass::getCurrentDate()
{
	time_t t = time(NULL);

	tm ct;
	localtime_s(&ct, &t);

	std::string year = std::to_string(ct.tm_year + 1900);
	std::string month = std::to_string(ct.tm_mon + 1);
	std::string day = std::to_string(ct.tm_mday);

	std::string hour = ct.tm_hour < 10 ? '0'+std::to_string(ct.tm_hour) : std::to_string(ct.tm_hour);
	std::string min = ct.tm_min < 10 ? '0'+std::to_string(ct.tm_min) : std::to_string(ct.tm_min);
	std::string sec = ct.tm_sec < 10 ? '0'+std::to_string(ct.tm_sec) : std::to_string(ct.tm_sec);

	// Format: YYYY-MM-DD HH:MM:SS
	std::string date =
		year + '-' + month + '-' + day + ' ' +
		hour + ':' + min + ':' + sec;

	return date;
}