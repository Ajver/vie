#include "MainClass.h"

#include <iostream>

#include <vie/IOManager.h>
#include <vie/Texture.h>
#include <vie/Graphics.h>
#include <vie/InputManager.h>

MainClass::MainClass()
{
	runEngine("Example Engine Application", 1280, 728, vie::WindowFlags::DEFAULT);
}

MainClass::~MainClass()
{
}

void MainClass::onCreate()
{
	playerPosition.x = 0;
	playerPosition.y = 100;

	playerSize.x = 128;
	playerSize.y = 128;

	playerTexture = vie::IOManager::getTexture("Graphics/Player.png");
	std::cout << "Texture ID: " << playerTexture.id << std::endl;
}

void MainClass::update(float et)
{
	//playerPosition.x += -100 * et;

	//std::cout << ".";
}

void MainClass::render(vie::Graphics* g)
{
	g->drawTexture(playerTexture, playerPosition, playerSize, vie::RED);
}

void MainClass::onKeyPress(unsigned int keyID)
{
	std::cout << "Key press: " << keyID << std::endl;

	if (keyID == SDLK_ESCAPE)
		destroyEngine();
	
}
/*
void MainClass::onKeyRelease(unsigned int keyID)
{
	std::cout << "Key release: " << keyID << std::endl;
}

void MainClass::onMousePress(unsigned int keyID, glm::vec2 mousePos)
{
	std::cout << "Mouse press: " << keyID << " xy: " << mousePos.x << " | " << mousePos.y << std::endl;
}

void MainClass::onMouseRelease(unsigned int keyID, glm::vec2 mousePos)
{
	std::cout << "Mouse release: " << keyID << " xy: " << mousePos.x << " | " << mousePos.y << std::endl;
}

void MainClass::onMouseMove(glm::vec2 mousePos)
{
	std::cout << "Mouse move xy: " << mousePos.x << " | " << mousePos.y << std::endl;
}

void MainClass::onMouseDrag(glm::vec2 mousePos)
{
	std::cout << "Mouse drag xy: " << mousePos.x << " | " << mousePos.y << std::endl;
}
*/

