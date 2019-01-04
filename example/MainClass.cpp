#include "MainClass.h"

#include <iostream>

#include <vie/ResourceManager.h>
#include <vie/Texture.h>
#include <vie/Graphics.h>

MainClass::MainClass()
{
	run();
}

MainClass::~MainClass()
{
}

void MainClass::onCreate()
{
	playerTexture = vie::ResourceManager::getTexture("Graphics/Player.png");
	std::cout << "Texture ID: " << playerTexture.id << std::endl;
}

void MainClass::update(float et)
{
	//std::cout << ".";
}

void MainClass::render(vie::Graphics* g)
{
	glm::vec4 position(0.0f, 0.0f, 32.0f, 32.0f);
	glm::vec4 uv(0.0f, 0.0f, 1.0f, 1.0f);

	g->draw(position, uv, playerTexture.id, 1.0f, vie::ORANGE);
}

/*
void MainClass::onKeyPress(unsigned int keyID)
{
	std::cout << "Key press: " << keyID << std::endl;
}

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

