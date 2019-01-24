#include "MainClass.h"

#include <iostream>

#include <vie/FileManager.h>
#include <vie/Texture.h>
#include <vie/Graphics.h>
#include <vie/Input.h>
#include <vie/ObjectsManager.h>
#include <vie/Camera2D.h>
#include <vie/Window.h>
#include <vie/Layer.h>

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

	graphics->createLayer("ground");
	graphics->createLayer("axis");

	graphics->getLayerByName("ground")->setCamera(mainCamera);
}

void MainClass::update(float et)
{
	float speed = 8.0f / graphics->getScale();
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
}

void MainClass::render(vie::Graphics* g)
{
	g->switchLayer("main");
	g->setBackgroundColor(vie::COLOR::DARK_GRAY);

	static vie::Texture chessBoard("Graphics/HugeSquare.png");
	g->drawTexture(chessBoard, 0.5f * glm::vec2(-(float)chessBoard.getWidth(), -(float)chessBoard.getHeight()));

	g->switchLayer("axis");
	float screenHeight = vie::Window::getScreenHeight();
	float screenWidth = vie::Window::getScreenWidth();
	g->setColor(vie::Color(0, 200, 100, 200));
	g->fillRect(glm::vec2(-1, -screenHeight*0.5f), glm::vec2(2, screenHeight));
	g->fillRect(glm::vec2(-screenWidth*0.5f, -1), glm::vec2(screenWidth, 2));
}

void MainClass::onKeyPress()
{
	if (vie::Input::getLastKey() == SDLK_ESCAPE)
		destroy();
}

void MainClass::onKeyRelease()
{
}


/*
void MainClass::onMousePress()
{
}

void MainClass::onMouseRelease()
{
}

void MainClass::onMouseMove()
{
}

void MainClass::onMouseDrag()
{
}
*/

