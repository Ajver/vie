#include "MainClass.h"

#include <iostream>

#include <vie/ResourceManager.h>
#include <vie/Texture.h>

MainClass::MainClass()
{
	run();
}

MainClass::~MainClass()
{
}

void MainClass::onCreate()
{
	vie::Texture playerTexture = vie::ResourceManager::getTexture("Graphics/Player.png");
	std::cout << "Texture ID: " << playerTexture.id << std::endl;
}

void MainClass::update(float et)
{
	//std::cout << ".";
}

void MainClass::render()
{

}
