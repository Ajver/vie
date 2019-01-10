#pragma once

#include <vie/Object.h>
#include <vie/Texture.h>

class Player : public vie::Object
{
public:
	Player();
	~Player();

	void create();
	void update(float et) override;
	void render(vie::Graphics* g) override;

	void onKeyPress(unsigned int keyID);
	void onKeyRelease(unsigned int keyID);

private:
	vie::Texture texture;

	void setVelocityByInput();
};

