#include "Engine.h"

#include <SDL/SDL.h>
#include <GL/glew.h>

#include <string>

namespace vie
{

	Engine::Engine() :
		isRunning(false),
		window(nullptr),
		screenWidth(0),
		screenHeight(0),
		FPS(0)
	{
	}

	Engine::~Engine()
	{
	}

	void Engine::run(const char *title, unsigned int sw, unsigned int sh, WindowFlags wType)
	{
		if (isRunning)
		{
			message("Error: The Engine is running");
			return;
		}

		init(title, sw, sh, wType);

		onCreate();

		float elapsedTime = 0.0f;

		int fpsCount = 0;
		unsigned int timer = SDL_GetTicks();

		isRunning = true;

		while (isRunning) 
		{
			unsigned int start = SDL_GetTicks();

			fpsCount++;

			update(elapsedTime);
			render();

			SDL_GL_SwapWindow(window);

			// Update the surface
			SDL_UpdateWindowSurface(window);

			unsigned int stop = SDL_GetTicks();

			// Count elapsed time
			elapsedTime = (stop - start) / 1000.0f;

			if (stop - timer >= 1000) 
			{
				timer += 1000;
				FPS = fpsCount;
				fpsCount = 0;
			}
		}
		
		// Free the memory
		SDL_DestroyWindow(window);

		// Exit program
		SDL_Quit();
		exit(0);
	}

	void Engine::init(const char *title, unsigned int sw, unsigned int sh, WindowFlags wType) {
		SDL_Init(SDL_INIT_EVERYTHING);

		Uint32 sdlFlags = SDL_WINDOW_OPENGL;

		if (wType & WindowFlags::INVISIBLE)
			sdlFlags |= SDL_WINDOW_HIDDEN;

		if(wType & WindowFlags::FULLSCREEN)
			sdlFlags |= SDL_WINDOW_FULLSCREEN_DESKTOP;

		if (wType & WindowFlags::BORDERLESS)
			sdlFlags |= SDL_WINDOW_BORDERLESS;

		if (wType & WindowFlags::RESIZABLE)
			sdlFlags |= SDL_WINDOW_RESIZABLE;

		window = SDL_CreateWindow(title, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, sw, sh, sdlFlags);

		if (window == nullptr) 
		{
			fatalError(SDL_GetError());
		}
		
		// Setup Glew
		SDL_GLContext glContext = SDL_GL_CreateContext(window);

		if (glContext == nullptr)
		{
			fatalError("SDL_GL context could not be created!");
		}

		if (glewInit() != GLEW_OK)
		{
			fatalError("Glew could not be initialized!");
		}

		// Chech the OpenGL version
		printf("*** Open GL Version: %s ***\n", glGetString(GL_VERSION));

		updateScreenSize();

		glClearColor(0.25f, 0.25f, 0.25f, 1.0f);

		// Enable alpha blend
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

		//g = new Graphics(window);
	}

	void Engine::fatalError(const char *err) 
	{
		printf(err);
		SDL_Quit();
		exit(-1);
	}

	void Engine::message(const char* err)
	{
		printf(err);
	}

	unsigned int Engine::getScreenWidth() 
	{
		return screenWidth;
	}

	unsigned int Engine::getScreenHeight() 
	{
		return screenHeight;
	}

	unsigned int Engine::getFpsCount() 
	{
		return FPS;
	}

	void Engine::updateScreenSize()
	{
		SDL_GetWindowSize(window, (int*)&screenWidth, (int*)&screenHeight);
	}

	// Default body (it's not necessary to use it)
	void Engine::onCreate() {}

}