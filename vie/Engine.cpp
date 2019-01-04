#include "Engine.h"

#include <SDL/SDL.h>
#include <GL/glew.h>

#include <string>
#include <iostream>

#include "Errors.h"
#include "Graphics.h"
#include "InputManager.h"

namespace vie
{

	Engine::Engine() :
		isRunning(false),
		window(nullptr),
		screenWidth(0),
		screenHeight(0),
		FPS(0),
		maxFPS(60)
	{
	}

	Engine::~Engine()
	{
	}

	void Engine::run(const char *title, unsigned int sw, unsigned int sh, WindowFlags wType)
	{
		if (isRunning)
		{
			printf("Error: The Engine is running");
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
			unsigned int startTicks = SDL_GetTicks();

			fpsCount++;

			processInput();
			update(elapsedTime);

			g->begin();
			
			render(g);

			g->end();
			g->renderBatch();

			SDL_GL_SwapWindow(window);

			unsigned int stopTicks = SDL_GetTicks();

			// Count elapsed time
			elapsedTime = (stopTicks - startTicks);// / 1000.0f;
			
			// Limit the fps to the max fps
			float maxET = 1000.0f / maxFPS;
			if (maxET > elapsedTime) {
				SDL_Delay(maxET - elapsedTime);
			}

			// Count elapsed time AFTER FPS limited
			elapsedTime = (SDL_GetTicks() - startTicks) / 1000.0f;

			if (stopTicks - timer >= 1000)
			{
				timer += 1000;
				FPS = fpsCount;
				fpsCount = 0;

				printf("FPS: %d\n", FPS);
				printf("ET: %f\n\n", elapsedTime);
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

		if (wType & WindowFlags::FULLSCREEN)
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

		g = new Graphics();
		g->init(screenWidth, screenHeight);
	}
	   
	void Engine::processInput()
	{
		SDL_Event evnt;

		while (SDL_PollEvent(&evnt))
		{
			switch (evnt.type)
			{
			case SDL_QUIT:
				SDL_Quit();
				exit(0);
				break;
			case SDL_KEYDOWN:
				InputManager::setKey(evnt.key.keysym.sym, true);
				onKeyPress(evnt.key.keysym.sym);
				break;
			case SDL_KEYUP:
				InputManager::setKey(evnt.key.keysym.sym, false);
				onKeyRelease(evnt.key.keysym.sym);
				break;
			case SDL_MOUSEBUTTONDOWN:
				InputManager::setKey(evnt.button.button, true);
				onMousePress(evnt.button.button, glm::vec2(evnt.motion.x, evnt.motion.y));
				break;
			case SDL_MOUSEBUTTONUP:
				InputManager::setKey(evnt.button.button, false);
				onMouseRelease(evnt.button.button, glm::vec2(evnt.motion.x, evnt.motion.y));
				break;
			case SDL_MOUSEMOTION:
				InputManager::setMousePosition(evnt.motion.x, evnt.motion.y);

				if (InputManager::isKeyPressed(SDL_BUTTON_LEFT) ||
					InputManager::isKeyPressed(SDL_BUTTON_MIDDLE) ||
					InputManager::isKeyPressed(SDL_BUTTON_RIGHT))
				{
					onMouseDrag(glm::vec2(evnt.motion.x, evnt.motion.y));
				}
				else
				{
					onMouseMove(glm::vec2(evnt.motion.x, evnt.motion.y));
				}
				break;
			}
		}
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

	// Default bodies (it's not necessary to use them)
	void Engine::onCreate() {}
	void Engine::onKeyPress(unsigned int keyID) {}
	void Engine::onKeyRelease(unsigned int keyID) {}
	void Engine::onMousePress(unsigned int keyID, glm::vec2 mousePos) {}
	void Engine::onMouseRelease(unsigned int keyID, glm::vec2 mousePos) {}
	void Engine::onMouseMove(glm::vec2 mousePos) {}
	void Engine::onMouseDrag(glm::vec2 mousePos) {}
}