#include "MainClass.h"

#include <iostream>

#include <vie/FileManager.h>
#include <vie/Texture.h>
#include <vie/Input.h>
#include <vie/ObjectsManager.h>
#include <vie/Camera2D.h>
#include <vie/Window.h>
#include <vie/Layer.h>

#include "Car.h"
#include "Map.h"
#include "CarFollower.h"

/*
Link those libs:

vie.lib
SDL2.lib
SDL2main.lib
Opengl32.lib
glew32.lib

*/

MainClass::MainClass() :
	mainMap(nullptr),
	carFollower(nullptr),
	fpsPrintTimer(1000)
{
	runEngine("Example Engine Application", 1024, 728, vie::WindowFlags::DEFAULT);
}

MainClass::~MainClass()
{
	delete mainMap;
	delete carFollower;
}

void MainClass::onCreate()
{
	setFPSLimit(-1);

	Car* playerCar = new Car(objectsManager);
	objectsManager->appendObject(playerCar);
	objectsManager->appendKeyListener(playerCar);

	mainMap = new Map(objectsManager);
	carFollower = new CarFollower(mainCamera, playerCar);

	graphics->setBackgroundColor(vie::Color(10, 30, 20));

	graphics->createLayer("ground", mainCamera);
	graphics->createLayer("car", mainCamera);

	graphics->switchLayer("ground");
	graphics->getCurrentLayer()->setIsRemovingGlyphs(false);
	mainMap->render(graphics);
}

void MainClass::update(float et)
{	
	objectsManager->update(et);
	carFollower->update(et);

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
}

void MainClass::onKeyRelease()
{
	switch (vie::Input::getLastKey())
	{
	case SDLK_ESCAPE:
		destroyEngine();
		break;
	}
}
