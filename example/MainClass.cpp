#include "MainClass.h"

#include <iostream>

#include <vie/IOManager.h>
#include <vie/Texture.h>
#include <vie/Graphics.h>
#include <vie/InputManager.h>
#include <vie/ObjectsManager.h>


void runFnc(void* fnc())
{
	fnc();
}

void* foo()
{
	std::cout << "FOOO!" << std::endl;
	return nullptr;
}

MainClass::MainClass()
{
	runFnc(foo);

	runEngine("Example Engine Application", 1280, 728, vie::WindowFlags::DEFAULT);
}

MainClass::~MainClass()
{
}

void MainClass::onCreate()
{
	Player *player = new Player();
	player->create();
	player->setPosition(glm::vec2(0, 100));
	player->setSize(glm::vec2(128, 128));

	objectsManager->appendObject(player);
	objectsManager->appendMouseInteractiveObject(player);
	objectsManager->appendKeyInteractiveObject(player);
}

void MainClass::update(float et)
{
	//std::cout << ".";

	//player.update(et);
}

void MainClass::render(vie::Graphics* g)
{
	//player.render(g);
}

void MainClass::onKeyPress(unsigned int keyID)
{
	//std::cout << "Key press: " << keyID << std::endl;

	if (keyID == SDLK_ESCAPE)
		destroy();
}

void MainClass::onKeyRelease(unsigned int keyID)
{
	//std::cout << "Key release: " << keyID << std::endl;
}


/*
void MainClass::onMousePress(unsigned int keyID)
{
	std::cout << "Mouse press: " << keyID << " xy: " << mousePos.x << " | " << mousePos.y << std::endl;
}

void MainClass::onMouseRelease(unsigned int keyID)
{
	std::cout << "Mouse release: " << keyID << " xy: " << mousePos.x << " | " << mousePos.y << std::endl;
}

void MainClass::onMouseMove()
{
	std::cout << "Mouse move xy: " << mousePos.x << " | " << mousePos.y << std::endl;
}

void MainClass::onMouseDrag()
{
	std::cout << "Mouse drag xy: " << mousePos.x << " | " << mousePos.y << std::endl;
}
*/

