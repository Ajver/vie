//
// pch.cpp
// Include the standard header and generate the precompiled header.
//

#include "pch.h"

#include <SDL/SDL.h>
#include <GL/glew.h>
#include <vie/Errors.h>
#include <vie/Window.h>

int main(int argc, char *args[])
{
	SDL_Init(SDL_INIT_EVERYTHING);

	vie::Window::create("", SCREEN_W, SCREEN_H, vie::WindowFlags::INVISIBLE);

	SDL_GLContext glContext = vie::Window::getSDLGLContext();

	if (glContext == nullptr)
		vie::fatalError("SDL_GL context could not be created!");

	if (glewInit() != GLEW_OK)
		vie::fatalError("Glew could not be initialized!");

	testing::InitGoogleTest(&argc, args);

	return RUN_ALL_TESTS();
}