#pragma once

#include <vie/Object.h>

class Block : public vie::Object
{
public:
	Block(const glm::vec2& npos, const glm::vec2& nsize);
	~Block();

	void render(vie::Graphics* g) override;

private:

};

