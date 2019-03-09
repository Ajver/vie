#pragma once

#include <vie/Object.h>
#include <vie/Animation.h>

class Swordman : public vie::Object
{
public:
	Swordman(glm::vec2 npos);
	~Swordman();

	void update(float et);
	void render(vie::Graphics* g);
	
private:
	vie::Animation animation;
};

