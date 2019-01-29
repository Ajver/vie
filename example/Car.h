#pragma once

#include <vie/Object.h>

class Car : public vie::Object
{
public:
	Car();
	~Car();


	void update(float et) override;
	void render(vie::Graphics* g) override;

	void updatePosition(float et);
	void calculateVelocity();

	float getRotate() const;

private:
	vie::Texture texture;
	float speed;
	float rotate;

	const float MAX_SPEED;
	const float ACCELERATION;
	const float TURN_SPEED;
};

