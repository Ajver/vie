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

	void onMouseEnter() override;
	void onMouseLeave() override;
	void onMouseMove() override;
	void onMouseDrag() override;
	void onMousePress(unsigned int keyID) override;
	void onMouseRelease(unsigned int keyID) override;
	void onKeyPress(unsigned int keyID) override;
	void onKeyRelease(unsigned int keyID) override;

private:
	vie::Texture texture;

	void setVelocityByInput();
};

