#pragma once

#include <vie/Object.h>
#include <vie/Texture.h>

namespace vie
{
	class ObjectsManager;
}

class Player : public vie::Object
{
public:
	Player();
	~Player();

	void create(vie::ObjectsManager* om);

	void update(float et) override;
	void render(vie::Graphics* g) override;

	void onMouseEnter() override;
	void onMouseLeave() override;
	void onMouseMove() override;
	void onMouseDrag() override;
	void onMousePress() override;
	void onMouseRelease() override;
	void onKeyPress() override;
	void onKeyRelease() override;

private:
	vie::Texture texture;
	vie::ObjectsManager* objectsManager;

	void setVelocityByInput();
};

