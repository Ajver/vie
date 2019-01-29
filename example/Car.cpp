#include "Car.h"

#include <vie/FileManager.h>
#include <vie/Input.h>

#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtx/rotate_vector.hpp>

Car::Car() :
	MAX_SPEED(300.0f),
	ACCELERATION(50.0f),
	TURN_ACCELERATION(0.01f),
	MAX_TURN_SPEED(0.02f)
{
	texture = vie::FileManager::getTexture("Graphics/car.png");
	position = glm::vec2(0, 0);
	size = glm::vec2(texture.getWidth(), texture.getHeight()) * 5.0f;
}


Car::~Car()
{
}

void Car::update(float et)
{
	processMoving(et);
	processTurning(et);

	updatePosition(et);
	updateRotate(et);
}

void Car::processMoving(float et)
{
	speed *= 0.99f;

	if (vie::Input::isKeyPressed(SDLK_w))
	{
		speed += getSpeedAcc(et);
		
		if(speed > 0)
			speed *= 1.05f;

		wasSpeedIncreased = true;
	}
	else if (vie::Input::isKeyPressed(SDLK_s))
	{
		speed -= getSpeedAcc(et);

		if (speed < 0)
			speed *= 1.05f;

		wasSpeedIncreased = true;
	}
	else
		wasSpeedIncreased = false;

	if (vie::Input::isKeyPressed(SDLK_SPACE))
		speed *= 0.92f;

	if (speed > MAX_SPEED)
		speed = MAX_SPEED;
	else if (speed < -MAX_SPEED)
		speed = -MAX_SPEED;
}

float Car::getSpeedAcc(float et)
{
	return ACCELERATION * et;
}

void Car::calculateVelocity()
{
	velocity = glm::vec2(0, -speed);
	velocity = glm::rotate(velocity, rotate);
}

void Car::processTurning(float et)
{
	turnSpeed *= 0.9f;

	if (vie::Input::isKeyPressed(SDLK_a))
	{
		turnSpeed -= getTurnAcc(et);

		speed *= 0.999f;
	}

	if (vie::Input::isKeyPressed(SDLK_d))
	{
		turnSpeed += getTurnAcc(et);

		speed *= 0.999f;
	}

	if(!wasSpeedIncreased)
		turnSpeed *= 0.1f;

	if (turnSpeed > MAX_TURN_SPEED)
		turnSpeed = MAX_TURN_SPEED;
	else if (turnSpeed < -MAX_TURN_SPEED)
		turnSpeed = -MAX_TURN_SPEED;
}

float Car::getTurnAcc(float et)
{
	return TURN_ACCELERATION * speed * et;
}

void Car::updatePosition(float et)
{
	calculateVelocity();
	position += velocity * et;
}

void Car::updateRotate(float et)
{
	rotate += turnSpeed;
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