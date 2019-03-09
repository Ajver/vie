#include "Swordman.h"

#include <vie/FileManager.h>

vie::Texture SWORDMAN_SS;
std::vector<vie::Texture*> textures;

Swordman::Swordman(glm::vec2 npos) :
	animation({}, 1000)
{
	position = npos;
	size = { 32, 48 };
	size *= 2.0f;

	SWORDMAN_SS = vie::FileManager::getTexture("Graphics/AttackAnimationSS.png");

	for (int i = 0; i < SWORDMAN_SS.getSize().x; i += 32)
	{
		vie::Texture* ntex = new vie::Texture(SWORDMAN_SS.getSubTexture(i, 0, 32, 48));
		textures.push_back(ntex);
	}
	animation.setTextures(textures);
}

Swordman::~Swordman()
{
}

void Swordman::update(float et)
{
	if (animation.update())
		animation.restart();
}

void Swordman::render(vie::Graphics* g)
{
	g->drawTexture(*animation.getCurrentTexture(), position, size);
}
