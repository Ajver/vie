#include "MainClass.h"

#include <vie/Window.h>
#include <vie/Layer.h>
#include <vie/ObjectsManager.h>

MainClass::MainClass()
{
	runEngine("Tic Tac Toe", 400, 540);
}

MainClass::~MainClass() {}

void MainClass::onCreate() 
{
	Tile::loadTextures();

	const glm::vec2 TILE_SIZE(96, 96);

	const float boardWidth = TILE_SIZE.x * 3;
	const float windowWidth = vie::Window::getScreenWidth();
	const float rightMargin = windowWidth - boardWidth;
	const float expectedMargin = rightMargin * 0.5f;

	for (int y = 0; y < 3; y++)
	{
		for (int x = 0; x < 3; x++)
		{
			Tile* tile = new Tile();
			tile->setPosition(glm::vec2(x * TILE_SIZE.x + expectedMargin, y * TILE_SIZE.y + expectedMargin));
			tile->setSize(TILE_SIZE);
			board[x][y] = tile;
			//objectsManager->appendObject(tile);
			objectsManager->appendMouseListener(tile);
		}
	}

	mainCamera->setPosition(vie::Window::getScreenSize() * 0.5f);
	//graphics->getCurrentLayer()->setSortType(vie::GlyphSortType::TEXTURE);
	//graphics->createLayer("signs", mainCamera);
}

void MainClass::onFatalError(const std::string& errMsg)
{
	system("pause");
}

void MainClass::update(float et) {}

void MainClass::render(vie::Graphics* g)
{
	g->setBackgroundColor(vie::COLOR::BLUE);

	for (int y = 0; y < 3; y++)
	{
		for (int x = 0; x < 3; x++)
		{
			board[x][y]->render(g);
		}
	}

	//objectsManager->render(g);
}