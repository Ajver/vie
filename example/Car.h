#pragma once

#include <vie/Object.h>
#include <Box2D/Box2D.h>

namespace vie
{
	class ObjectsManager;
}

class Car : public vie::Object
{
public:
	Car(vie::ObjectsManager* nom, b2World* b_world);
	~Car();

	void update(float et) override;
	void render(vie::Graphics* g) override;

private:
	vie::ObjectsManager* om;
	vie::Texture texture;
	float speed;
	bool wasSpeedIncreased;

	float turnSpeed;

	const float MAX_SPEED;
	const float ACCELERATION;
	const float TURN_ACCELERATION;
	const float MAX_TURN_SPEED;

	vie::Color color;
	
	b2Body* b_body;
	b2Fixture* b_fixture;
	b2Vec2 b_vel;

	void processMoving(float et);
	float getSpeedAcc(float et);
	void calculateVelocity();
	
	void processTurning(float et);
	float getTurnAcc(float et);

	void processBreaking();
	void runBreak(float breakForce);

};

