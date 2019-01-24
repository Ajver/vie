#include "MainClass.h"

#include <iostream>

#include <vie/FileManager.h>
#include <vie/Texture.h>
#include <vie/Graphics.h>
#include <vie/Input.h>
#include <vie/ObjectsManager.h>
#include <vie/Camera2D.h>

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
	Player *player = new Player();
	player->create(objectsManager);
	player->setPosition(glm::vec2(0, 0));
	player->setSize(glm::vec2(256, 256));

	objectsManager->appendObject(player);
	objectsManager->appendMouseListener(player);
	objectsManager->appendKeyListener(player);
}

void MainClass::update(float et)
{
	//mainCamera->scaleUp(1.01f);
	//std::cout << ".";
}

void MainClass::render(vie::Graphics* g)
{
	g->setBackgroundColor(vie::COLOR::DARK_GRAY);

	float speed = 8.0f / g->getScale();
	float scaleSpeed = 1.02f;
	float rotateSpeed = 0.01f;

	if (vie::Input::isKeyPressed(SDLK_w))
		mainCamera->move(glm::vec2(0, speed / mainCamera->getScale()));
	if (vie::Input::isKeyPressed(SDLK_s))
		mainCamera->move(glm::vec2(0, -speed / mainCamera->getScale()));

	if (vie::Input::isKeyPressed(SDLK_a))
		mainCamera->move(glm::vec2(-speed / mainCamera->getScale(), 0));
	if (vie::Input::isKeyPressed(SDLK_d))
		mainCamera->move(glm::vec2(speed / mainCamera->getScale(), 0));

	if (vie::Input::isKeyPressed(SDLK_q))
		mainCamera->scaleDown(scaleSpeed);
	if (vie::Input::isKeyPressed(SDLK_e))
		mainCamera->scaleUp(scaleSpeed);

	if (vie::Input::isKeyPressed(SDLK_z))
		mainCamera->rotate(-rotateSpeed);
	if (vie::Input::isKeyPressed(SDLK_x))
		mainCamera->rotate(rotateSpeed);

	static vie::Texture chessBoard("Graphics/HugeSquare.png");

	g->drawTexture(chessBoard, 0.5f * glm::vec2(-(float)chessBoard.getWidth(), -(float)chessBoard.getHeight()));
}

void MainClass::onKeyPress()
{
	//std::cout << "Key press: " << keyID << std::endl;

	if (vie::Input::getLastKey() == SDLK_ESCAPE)
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

