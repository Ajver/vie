#pragma once

#include <vie/Object.h>

class b2World;
class b2Body;
class b2Fixture;

class Block : public vie::Object
{
public:
	Block(const glm::vec2& npos, const glm::vec2& nsize, b2World* b_world);
	~Block();

	void render(vie::Graphics* g) override;

private:
	b2Body* b_body;
	b2Fixture* b_fixture;
};

