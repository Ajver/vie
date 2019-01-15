#include "MainClass.h"

#include <iostream>

#include <vie/IOManager.h>
#include <vie/Texture.h>
#include <vie/Graphics.h>
#include <vie/InputManager.h>
#include <vie/ObjectsManager.h>

/*
Link those libs:

vie.lib
SDL2.lib
SDL2main.lib
Opengl32.lib
glew32.lib

*/

MainClass::MainClass()
{
	runEngine("Example Engine Application", 1280, 728, vie::WindowFlags::DEFAULT);
}

MainClass::~MainClass()
{
}

void MainClass::onCreate()
{
	//g->setScale(6.0f);
	mainCamera->setScale(0.1f);

	Player *player = new Player();
	player->create(objectsManager);
	player->setPosition(glm::vec2(0, 0));
	player->setSize(glm::vec2(32, 32));

	objectsManager->appendObject(player);
	objectsManager->appendMouseInteractiveObject(player);
	objectsManager->appendKeyInteractiveObject(player);
}

void MainClass::update(float et)
{
	//mainCamera->scaleUp(1.01f);
	//std::cout << ".";
}

void MainClass::render(vie::Graphics* g)
{
	float speed = 100.0f / g->getScale();
	float scaleSpeed = 1.02f;

	if (vie::InputManager::isKeyPressed(SDLK_w))
		g->translate(glm::vec2(0, -speed));
	if (vie::InputManager::isKeyPressed(SDLK_s))
		g->translate(glm::vec2(0, speed));

	if (vie::InputManager::isKeyPressed(SDLK_a))
		g->translate(glm::vec2(-speed, 0));
	if (vie::InputManager::isKeyPressed(SDLK_d))
		g->translate(glm::vec2(speed, 0));

	if (vie::InputManager::isKeyPressed(SDLK_q))
		g->scaleDown(scaleSpeed);
	if (vie::InputManager::isKeyPressed(SDLK_e))
		g->scaleUp(scaleSpeed);
}

void MainClass::onKeyPress()
{
	//std::cout << "Key press: " << keyID << std::endl;

	if (vie::InputManager::getLastKey() == SDLK_ESCAPE)
		destroy();
}

void MainClass::onKeyRelease()
{
	//std::cout << "Key release: " << keyID << std::endl;
}


/*
void MainClass::onMousePress()
{
	std::cout << "Mouse press: " << keyID << " xy: " << mousePos.x << " | " << mousePos.y << std::endl;
}

void MainClass::onMouseRelease()
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

