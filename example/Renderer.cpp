#include "Renderer.h"

#include <vie/Graphics.h>
#include <vie/Camera2D.h>
#include <vie/Window.h>

Renderer::Renderer() :
	camera(new vie::Camera2D()),
	swordman({ 600.0f, 400.0f }),
	timer(2500)
{
	camera->setPosition(vie::Window::getScreenSize() * 0.5f);
}

Renderer::~Renderer()
{
}

void Renderer::update()
{
	camera->update();
	swordman.update(0);

	if (timer.tick())
		timer.restart();
}

void Renderer::render(vie::Graphics* g)
{
	g->switchLayer("renderer");

	//////////// RECTANGLES //////////

	static const glm::vec2 RECT_POS = { 10, 20 };
	static const glm::vec2 RECT_SIZE = { 120, 70 };

	g->setColor(vie::COLOR::RED);
	g->fillRect(RECT_POS, RECT_SIZE);

	g->setColor(vie::COLOR::YELLOW * vie::Color(255, 255, 255, 128));
	g->drawRect(RECT_POS, RECT_SIZE, 10.0f);

	g->setColor(vie::Color(128, 128, 255, 128));
	g->fillOval(RECT_POS, { 10.0f, 10.0f });
	g->fillOval(RECT_POS + RECT_SIZE, { 10.0f, 10.0f });

	/////////// TRIANGLES /////////////

	static const glm::vec2 POS_A = { 30, 200 };
	static const glm::vec2 POS_B = { 180, 180 };
	static const glm::vec2 POS_C = { 100, 350 };

	g->setColor(vie::COLOR::GREEN);
	g->fillTriangle(POS_A, POS_B, POS_C);

	g->setColor(vie::COLOR::RED * vie::Color(255, 255, 255, 128));
	g->drawTriangle(POS_A, POS_B, POS_C, 10.0f);

	g->setColor(vie::Color(128, 128, 255, 128));
	g->fillOval(POS_A, { 10.0f, 10.0f });
	g->fillOval(POS_B, { 10.0f, 10.0f });
	g->fillOval(POS_C, { 10.0f, 10.0f });

	///////////// OVALS ////////////////

	static const glm::vec2 OVAL_POS = { 300, 400 };
	static const glm::vec2 OVAL_SIZE = { 100, 50 };

	g->setColor(vie::COLOR::ORANGE);
	g->fillOval(OVAL_POS, OVAL_SIZE);

	g->setColor(vie::COLOR::BLUE * vie::Color(255, 255, 255, 128));
	g->drawOval(OVAL_POS, OVAL_SIZE, 10.0f);

	g->setColor(vie::Color(128, 128, 255, 128));
	g->fillOval(OVAL_POS, { 10.0f, 10.0f });

	///////////// POLYGONS ////////////////

	static const std::vector<glm::vec2> polygon = {
		{ 400, 80 },
		{ 460, 110 },
		{ 510, 170 },
		{ 450, 230 },
		{ 320, 170 },
		{ 360, 110 }
	};

	g->setColor(vie::COLOR::WHITE);
	g->fillPolygon(polygon);

	g->setColor(vie::Color(255, 128, 0, 128));
	g->drawPolygon(polygon, 10.0f);

	g->setColor(vie::Color(128, 128, 255, 128));
	for (auto& p : polygon)
		g->fillOval(p, { 10.0f, 10.0f });

	///////////// SWORDMAN //////////////////

	swordman.render(g);

	//////////// TIMER ///////////////////////

	g->setColor(vie::COLOR::YELLOW);
	g->fillRect({ timer.getDecreasingProgressINV() * (vie::Window::getScreenWidth() - 64), 500.0f }, { 64, 64 });
}

vie::Camera2D* Renderer::getCamera() const
{
	return camera;
}