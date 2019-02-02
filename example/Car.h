#pragma once

#include <vie/Object.h>

class Car : public vie::Object
{
public:
	Car();
	~Car();

	void update(float et) override;
	void render(vie::Graphics* g) override;

	float getRotate() const;

private:
	vie::Texture texture;
	float speed;
	bool wasSpeedIncreased;

	float rotate;
	float turnSpeed;

	const float MAX_SPEED;
	const float ACCELERATION;
	const float TURN_ACCELERATION;
	const float MAX_TURN_SPEED;

	void processMoving(float et);
	float getSpeedAcc(float et);
	void calculateVelocity();
	
	void processTurning(float et);
	float getTurnAcc(float et);

	void updatePosition(float et);
	void updateRotate(float et);
};

