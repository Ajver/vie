#include "Block.h"

#include <Box2D/Box2D.h>

Block::Block(const glm::vec2& npos, const glm::vec2& nsize, b2World* b_world)
{
	position = npos;
	size = nsize;

	b2BodyDef bodyDef;
	bodyDef.position.Set(npos.x, npos.y);
	
	b_body = b_world->CreateBody(&bodyDef);

	b2PolygonShape box;
	box.SetAsBox(size.x * 0.5f, size.y * 0.5f);

	b_fixture = b_body->CreateFixture(&box, 0.0f);
}

Block::~Block()
{
}

void Block::render(vie::Graphics* g)
{
	//g->setColor(vie::COLOR::DARK_GRAY);
	//g->fillRect(position, size);
}