#include "Player.h"

#include <vie/IOManager.h>
#include <vie/InputManager.h>
#include <vie/Window.h>
#include <vie/ObjectsManager.h>

#include <iostream>

Player::Player()
{
}


Player::~Player()
{
}

void Player::create(vie::ObjectsManager* om)
{
	objectsManager = om;
	texture = vie::IOManager::getTexture("Graphics/Player.png");

	for (int y = 0; y < texture.getHeight(); y++)
		for (int x = 0; x < texture.getWidth(); x++)
		{
			texture.setPixelColor(x, y, vie::ORANGE);
		}

	texture.refreshGLBuffer();
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
	g->setSortType(vie::GlyphSortType::FRONT_TO_BACK);
	g->setScale(3.0f);
	//g->translate(-size * 0.5f);
	//g->drawTexture(texture, position, size);
	//g->translate(size * 0.5f);

	g->translate(glm::vec2(-450, -300));
	g->fillRect(position, glm::vec2(60, 100), vie::PINK);
	g->drawRect(position, glm::vec2(60, 100), vie::Color(255, 255, 255, 100));
	g->translate(glm::vec2(450, 300));
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
	position = vie::InputManager::getMousePosition() - size * 0.5f;
}

void Player::onMousePress()
{
}

void Player::onMouseRelease()
{
	if (vie::InputManager::getLastKey() == SDL_BUTTON_RIGHT)
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

	if (vie::InputManager::isKeyPressed(SDLK_w) || vie::InputManager::isKeyPressed(SDLK_UP))
		velocity.y -= 1.0f;

	if (vie::InputManager::isKeyPressed(SDLK_s) || vie::InputManager::isKeyPressed(SDLK_DOWN))
		velocity.y += 1.0f;

	if (vie::InputManager::isKeyPressed(SDLK_a) || vie::InputManager::isKeyPressed(SDLK_LEFT))
		velocity.x -= 1.0f;

	if (vie::InputManager::isKeyPressed(SDLK_d) || vie::InputManager::isKeyPressed(SDLK_RIGHT))
		velocity.x += 1.0f;

	if (glm::length(velocity))
		velocity = glm::normalize(velocity) * 200.0f;
}