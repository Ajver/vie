#include "Car.h"

#include <vie/FileManager.h>
#include <vie/Input.h>

#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtx/rotate_vector.hpp>

Car::Car() :
	MAX_SPEED(300.0f),
	ACCELERATION(100.0f),
	TURN_SPEED(0.01f)
{
	texture = vie::FileManager::getTexture("Graphics/car.png");
	position = glm::vec2(0, 0);
	size = glm::vec2(45, 69);
}


Car::~Car()
{
}

void Car::update(float et)
{
	if (vie::Input::isKeyPressed(SDLK_w))
	{
		speed += ACCELERATION * et;
		if (speed > MAX_SPEED)
			speed = MAX_SPEED;
	}
	else if (vie::Input::isKeyPressed(SDLK_s))
	{
		speed -= ACCELERATION * et;
		if (speed < -MAX_SPEED)
			speed = -MAX_SPEED;
	}
	else
	{
		speed *= 0.99f;
	}

	if (vie::Input::isKeyPressed(SDLK_a))
	{
		rotate -= TURN_SPEED * speed * et * (speed > 0 ? 1 : -1);
		speed *= 0.999f;
	}

	if (vie::Input::isKeyPressed(SDLK_d))
	{
		rotate += TURN_SPEED * speed * et * (speed > 0 ? 1 : -1);
		speed *= 0.999f;
	}

	if(vie::Input::isKeyPressed(SDLK_SPACE))
	{
		speed *= 0.92f;
	}

	updatePosition(et);
}

void Car::updatePosition(float et)
{
	calculateVelocity();
	position += velocity * et;
}

void Car::calculateVelocity()
{
	velocity = glm::vec2(0, -speed);
	velocity = glm::rotate(velocity, rotate);
}

void Car::render(vie::Graphics* g)
{
	g->rotate(rotate);
	g->translate(position);
	g->drawTexture(texture, -size * 0.5f, size);
	g->translate(-position);
	g->rotate(-rotate);
}

float Car::getRotate() const
{
	return rotate;
}