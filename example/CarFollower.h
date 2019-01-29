#pragma once

namespace vie
{
	class Camera2D;
}

class Car;

class CarFollower
{
public:
	CarFollower(vie::Camera2D* camera, Car* car);
	~CarFollower();

	void update(float et);

private:
	vie::Camera2D* camera;
	Car* car;

	const float FOLLOW_SPEED = 10.0f;
	const float ROTATE_SPEED = 5.0f;

	void updateCameraPosition(float et);
	void updateCameraRotate(float et);
};

