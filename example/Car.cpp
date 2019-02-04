#include "Car.h"

#include <vie/FileManager.h>
#include <vie/Input.h>
#include <vie/ObjectsManager.h>
#include <vie/CollisionBody.h>

#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtx/rotate_vector.hpp>

Car::Car(vie::ObjectsManager* nom) :
	MAX_SPEED(1100.0f),
	ACCELERATION(200.0f),
	TURN_ACCELERATION(0.5f),
	MAX_TURN_SPEED(1.5f),
	om(nom),
	color(vie::COLOR::WHITE)
{
	texture = vie::FileManager::getTexture("Graphics/car.png");
	position = glm::vec2(0, 0);
	size = texture.getSize() * 3.0f;

	glm::vec2 halfSize = size * 0.5f;
	collisionBody = new vie::CollisionBody(this, 
		{
			-halfSize,
			{ 0.0f, -halfSize.y-2.0f },
			{ halfSize.x, -halfSize.y },
			{ halfSize.x+2.0f, 0.0f},
			halfSize,
			{ 0.0f, halfSize.y+2.0f },
			{ -halfSize.x, halfSize.y },
			{ -halfSize.x-2.0f, 0.0f}
		});
}

Car::~Car()
{
}

void Car::update(float et)
{
	processMoving(et);
	processTurning(et);
	//float speed = 200.0f;
	//if (vie::Input::isKeyPressed(SDLK_w))
	//	position.y -= speed * et;
	//if (vie::Input::isKeyPressed(SDLK_s))
	//	position.y += speed * et;
	//
	//if (vie::Input::isKeyPressed(SDLK_a))
	//	position.x -= speed * et;
	//if (vie::Input::isKeyPressed(SDLK_d))
	//	position.x += speed * et;

	updatePosition(et);
	updateRotate(et);

	color = vie::COLOR::WHITE;
	processCollision();
}

void Car::processMoving(float et)
{
	speed *= 1.0f - et;

	if (vie::Input::isKeyPressed(SDLK_w))
	{
		speed += getSpeedAcc(et);
		
		if (speed > 0)
			speed *= 1.0f + et;

		wasSpeedIncreased = true;
	}
	else if (vie::Input::isKeyPressed(SDLK_s))
	{
		speed -= getSpeedAcc(et);

		if (speed < 0)
			speed *= 1.0f + et;

		wasSpeedIncreased = true;
	}
	else
		wasSpeedIncreased = false;

	if (vie::Input::isKeyPressed(SDLK_SPACE))
		speed *= 1.0f - et * 2.0f;

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
	bool wasTurning = false;

	if (vie::Input::isKeyPressed(SDLK_a))
	{
		turnSpeed -= getTurnAcc(et);

		speed *= 1.0f - et;

		wasTurning = true;
	}

	if (vie::Input::isKeyPressed(SDLK_d))
	{
		turnSpeed += getTurnAcc(et);

		speed *= 1.0f - et;

		wasTurning = true;
	}

	if(!wasSpeedIncreased || !wasTurning)
		turnSpeed *= (1.0f - et) * 0.1f;

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
	rotate += turnSpeed * et;
}

void Car::render(vie::Graphics* g)
{
	g->rotate(rotate);
	g->translate(position);
	g->drawTexture(texture, -size * 0.5f, size, color);
	g->translate(-position);
	g->rotate(-rotate);
}

float Car::getRotate() const
{
	return rotate;
}

void Car::processCollision()
{
	for (auto& other : om->getObjectsVector())
	{
		if (other != this)
		{
			if (other->hasCollisionBody())
			{
				processCollision(other);
			}
		}
	}
}

void Car::processCollision(vie::Object* other)
{
	if (collisionBody->bound(other->getCollisionBody()))
		color = vie::COLOR::GREEN;
}