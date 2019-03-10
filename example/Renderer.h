#pragma once

#include "Swordman.h"

namespace vie
{
	class Graphics;
	class Camera2D;
}

class Renderer
{
public:
	Renderer();
	~Renderer();

	void update();
	void render(vie::Graphics* g);

	vie::Camera2D* getCamera() const;

private:
	vie::Camera2D* camera;
	Swordman swordman;
	vie::Timer timer;

};

