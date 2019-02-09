#include "MainClass.h"

#include <iostream>

#include <vie/FileManager.h>
#include <vie/Texture.h>
#include <vie/Input.h>
#include <vie/ObjectsManager.h>
#include <vie/Camera2D.h>
#include <vie/Window.h>
#include <vie/Layer.h>
#include <vie/SpriteFont.h>

#include "Car.h"
#include "Map.h"
#include "CarFollower.h"

#include <Box2D/Box2D.h>

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
	runEngine("Example vie Application", 1024, 728, vie::WindowFlags::DEFAULT);
}

MainClass::~MainClass()
{
	delete mainMap;
	delete carFollower;
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

	graphics->setBackgroundColor(vie::Color(10, 30, 20));

	graphics->createLayer("ground", mainCamera);
	graphics->createLayer("car", mainCamera);
	graphics->createLayer("hud");

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

	g->switchLayer("hud");
	g->setColor(vie::COLOR::ORANGE);

	glm::vec2 posA(-100.0f, -10.0f);
	glm::vec2 posB(-150.0f, 60.0f);
	glm::vec2 posC(30.0f, 70.0f);
	glm::vec2 smallSize(15.0f);

	g->fillTriangle(posA, posB, posC);
	
	g->setColor(vie::COLOR::RED);
	//g->fillRect(posA - smallSize*0.5f, smallSize);
	//g->fillRect(posB - smallSize * 0.5f, smallSize);
	//g->fillRect(posC - smallSize * 0.5f, smallSize);

	g->setColor(vie::Color(255, 0, 0, 128));
	g->drawLine(posA, posB, 16.0f);
	g->drawLine(posA, posC, 16.0f);
	g->drawLine(posB, posC, 16.0f);

	g->setColor(vie::Color(255, 255, 0, 128));
	g->drawTriangle(posA, posB, posC, 8.0f);
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
