//
// pch.cpp
// Include the standard header and generate the precompiled header.
//

#include "pch.h"

#include <SDL/SDL.h>
#include <GL/glew.h>
#include <vie/Logger.h>
#include <vie/Window.h>
#include <vie/Engine.h>

class MainClass : public vie::Engine
{
public:
	MainClass()
	{
	}
};

int main(int argc, char *args[])
{
	SDL_Init(SDL_INIT_EVERYTHING);

	vie::Window::create("", SCREEN_W, SCREEN_H, vie::WindowFlags::INVISIBLE);

	SDL_GLContext glContext = vie::Window::getSDLGLContext();

	if (glContext == nullptr)
		vie::Logger::fatalError("SDL_GL context could not be created!");

	if (glewInit() != GLEW_OK)
		vie::Logger::fatalError("Glew could not be initialized!");

	testing::InitGoogleTest(&argc, args);

	return RUN_ALL_TESTS();
}