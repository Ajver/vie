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
	player.create();
	player.setPosition(glm::vec2(0, 100));
	player.setSize(glm::vec2(128, 128));
}

void MainClass::update(float et)
{
	//std::cout << ".";

	player.update(et);
}

void MainClass::render(vie::Graphics* g)
{
	player.render(g);
}

void MainClass::onKeyPress(unsigned int keyID)
{
	//std::cout << "Key press: " << keyID << std::endl;

	if (keyID == SDLK_ESCAPE)
		destroy();
	
	player.onKeyPress(keyID);
}

void MainClass::onKeyRelease(unsigned int keyID)
{
	//std::cout << "Key release: " << keyID << std::endl;

	player.onKeyRelease(keyID);
}


/*
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

