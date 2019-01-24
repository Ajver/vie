#include "Player.h"

#include <vie/FileManager.h>
#include <vie/Input.h>
#include <vie/Window.h>
#include <vie/ObjectsManager.h>
#include <vie/Color.h>

#include <iostream>

Player::Player()
{
}


Player::~Player()
{
}

void write2DArr(const unsigned char* arr, GLuint size)
{
	for (int i = 0; i < size; i++)
		std::cout << (int)arr[i] << " ";
}

void Player::create(vie::ObjectsManager* om)
{
	objectsManager = om;
	texture = vie::FileManager::getTexture("Graphics/Player.png");

	setPosition(glm::vec2(0, 0));
	setSize(glm::vec2(256, 256));
}

void Player::update(float et)
{
	//position += velocity * et;

	if (position.x < 0)
		position.x = 0;
	else if (position.x + size.x > vie::Window::getScreenWidth())
		position.x = vie::Window::getScreenWidth() - size.x;

	if (position.y < 0)
		position.y = 0;
	else if (position.y + size.y > vie::Window::getScreenHeight())
		position.y = vie::Window::getScreenHeight() - size.y;
}

void Player::render(vie::Graphics* g)
{
	g->switchLayer("ground");
	g->setColor(vie::COLOR::PINK);
	g->fillRect(position, size);

	g->setColor(vie::COLOR::RED);
	g->drawRect(position, size, 6.0f);

	g->drawTexture(texture, position, size);
}

void Player::onMouseEnter()
{
}

void Player::onMouseLeave()
{
}

void Player::onMouseMove()
{
}

void Player::onMouseDrag()
{
	position = vie::Input::getMousePosition() - size * 0.5f;
}

void Player::onMousePress()
{
}

void Player::onMouseRelease()
{
	if (vie::Input::getLastKey() == SDL_BUTTON_RIGHT)
	{
		Player *player = new Player();
		player->create(objectsManager);
		player->setPosition(glm::vec2(0, 100));
		player->setSize(glm::vec2(128, 128));
		objectsManager->appendObject(player);
	}
}

void Player::onKeyPress()
{
	setVelocityByInput();
}

void Player::onKeyRelease()
{
	setVelocityByInput();
}

void Player::setVelocityByInput()
{
	velocity.x = velocity.y = 0;

	if (vie::Input::isKeyPressed(SDLK_w) || vie::Input::isKeyPressed(SDLK_UP))
		velocity.y -= 1.0f;

	if (vie::Input::isKeyPressed(SDLK_s) || vie::Input::isKeyPressed(SDLK_DOWN))
		velocity.y += 1.0f;

	if (vie::Input::isKeyPressed(SDLK_a) || vie::Input::isKeyPressed(SDLK_LEFT))
		velocity.x -= 1.0f;

	if (vie::Input::isKeyPressed(SDLK_d) || vie::Input::isKeyPressed(SDLK_RIGHT))
		velocity.x += 1.0f;

	if (glm::length(velocity))
		velocity = glm::normalize(velocity) * 200.0f;
}