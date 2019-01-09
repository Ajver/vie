#pragma once

#include <vie/Engine.h>
#include <vie/Texture.h>

class MainClass : public vie::Engine
{
public:
	MainClass();
	~MainClass();

	void onCreate();

	void update(float et) override;
	void render(vie::Graphics* g) override;

	/*
	void onKeyPress(unsigned int keyID);
	void onKeyRelease(unsigned int keyID);
	void onMousePress(unsigned int keyID, glm::vec2 mousePos);
	void onMouseRelease(unsigned int keyID, glm::vec2 mousePos);
	void onMouseMove(glm::vec2 mousePos);
	void onMouseDrag(glm::vec2 mousePos);
	*/

private:
	glm::vec2 playerPosition;
	glm::vec2 playerSize;
	vie::Texture playerTexture;
};

