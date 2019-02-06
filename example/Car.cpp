#include "Car.h"

#include <vie/FileManager.h>
#include <vie/Input.h>
#include <vie/ObjectsManager.h>

#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtx/rotate_vector.hpp>

#include <Box2D/Box2D.h>

Car::Car(vie::ObjectsManager* nom, b2World* b_world) :
	MAX_SPEED(100.0f),
	ACCELERATION(60.0f),
	TURN_ACCELERATION(0.5f),
	MAX_TURN_SPEED(1.5f),
	om(nom),
	color(vie::COLOR::WHITE)
{
	texture = vie::FileManager::getTexture("Graphics/car.png");
	position = { 0.0f, 0.0f };
	size.x = 2.0f;
	size.y = texture.getSize().y / (texture.getSize().x / size.x);

	b2BodyDef bodyDef;
	bodyDef.position.Set(position.x, position.y);
	bodyDef.type = b2_dynamicBody;

	b_body = b_world->CreateBody(&bodyDef);
	
	b2PolygonShape box;
	box.SetAsBox(size.x * 0.5f, size.y * 0.5f);

	b2FixtureDef fixtureDef;
	fixtureDef.shape = &box;
	fixtureDef.density = 1.0f;
	fixtureDef.friction = 0.3f;

	b_fixture = b_body->CreateFixture(&fixtureDef);
}

Car::~Car()
{
}

void Car::update(float et)
{
	processMoving(et);
	processTurning(et);
	processBreaking();
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
	{
		speed *= 1.0f - et * 2.0f;

		runBreak(12.0f);
	}

	if (speed > MAX_SPEED)
		speed = MAX_SPEED;
	else if (speed < -MAX_SPEED)
		speed = -MAX_SPEED;

	calculateVelocity();

	b_body->ApplyForceToCenter(b_vel, true);
}

float Car::getSpeedAcc(float et)
{
	return ACCELERATION * et;
}

void Car::calculateVelocity()
{
	velocity = glm::vec2(0, -speed);
	velocity = glm::rotate(velocity, rotate);
	b_vel = { velocity.x, velocity.y };
}

void Car::processTurning(float et)
{
	bool wasTurning = false;

	if (vie::Input::isKeyPressed(SDLK_a))
	{
		turnSpeed -= getTurnAcc(et);

		wasTurning = true;
	}

	if (vie::Input::isKeyPressed(SDLK_d))
	{
		turnSpeed += getTurnAcc(et);

		wasTurning = true;
	}

	if(!wasSpeedIncreased || !wasTurning)
		turnSpeed *= (1.0f - et) * 0.1f;

	if (turnSpeed > MAX_TURN_SPEED)
		turnSpeed = MAX_TURN_SPEED;
	else if (turnSpeed < -MAX_TURN_SPEED)
		turnSpeed = -MAX_TURN_SPEED;

	if (wasTurning)
	{
		runBreak(10.0f);
		calculateVelocity();
		b_vel *= 1.0f;
		b_body->ApplyForceToCenter(b_vel, true);
	}

	b_body->SetAngularVelocity(turnSpeed);
}

float Car::getTurnAcc(float et)
{
	return TURN_ACCELERATION * speed * et;
}

void Car::render(vie::Graphics* g)
{
	position = { b_body->GetPosition().x, b_body->GetPosition().y };
	rotate = b_body->GetAngle();

	g->rotate(rotate);
	g->translate(position);
	g->drawTexture(texture, -size * 0.5f, size, color);
	g->translate(-position);
	g->rotate(-rotate);
}

void Car::runBreak(float breakForce)
{
	b2Vec2 breakFoce = b_body->GetLinearVelocity();
	breakFoce.x *= -breakForce;
	breakFoce.y *= -breakForce;

	b_body->ApplyForceToCenter(breakFoce, true);
}

void Car::processBreaking()
{
	b2Vec2 vel = b_body->GetLinearVelocity();
	vel.Normalize();

	b2Vec2 targetVel = { cos(b_body->GetAngle()), sin(b_body->GetAngle()) };
	targetVel.Normalize();

	b2Vec2 diff = targetVel - vel;

	runBreak(diff.Length() * 10.0f);
}