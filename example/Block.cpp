#include "Block.h"

#include <vie/CollisionBody.h>

Block::Block(const glm::vec2& npos, const glm::vec2& nsize)
{
	position = npos;
	size = nsize;

	createDefaultCollisionBody();
	collisionBody->setIsStatic(true);
}

Block::~Block()
{
}

void Block::render(vie::Graphics* g)
{
	//g->setColor(vie::COLOR::DARK_GRAY);
	//g->fillRect(position, size);
}