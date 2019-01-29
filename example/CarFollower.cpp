#include "CarFollower.h"

#include <vie/Camera2D.h>

#include "Car.h"

CarFollower::CarFollower(vie::Camera2D* camera, Car* car) :
	camera(camera),
	car(car)
{
}


CarFollower::~CarFollower()
{
}

void CarFollower::update(float et)
{
	updateCameraRotate(et);
	updateCameraPosition(et);
}

void CarFollower::updateCameraPosition(float et)
{
	glm::vec2 currPos = camera->getPosition();
	glm::vec2 destPos = car->getPosition();
	glm::vec2 velocity = destPos - currPos;
	velocity *= et * FOLLOW_SPEED;

	camera->move(velocity);
}

void CarFollower::updateCameraRotate(float et)
{
	float currRot = camera->getRotate();
	float destRot = car->getRotate();
	float rotateVel = destRot - currRot;
	rotateVel *= et * ROTATE_SPEED;

	camera->rotate(rotateVel);
}
