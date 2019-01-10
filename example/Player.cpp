#include "Player.h"

#include <vie/IOManager.h>
#include <vie/InputManager.h>
#include <vie/Window.h>

Player::Player()
{
}


Player::~Player()
{
}

void Player::create()
{
	texture = vie::IOManager::getTexture("Graphics/Player.png");
}

void Player::update(float et)
{
	position += velocity * et;

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
	position = vie::InputManager::getMousePosition() - size * 0.5f;
}

void Player::onMousePress()
{
}

void Player::onMouseRelease()
{
}

void Player::onKeyPress(unsigned int keyID)
{
	setVelocityByInput();
}

void Player::onKeyRelease(unsigned int keyID)
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