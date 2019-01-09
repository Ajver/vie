#include "Engine.h"

#include <SDL/SDL.h>
#include <GL/glew.h>

#include <string>
#include <iostream>

#include "Window.h"
#include "Errors.h"
#include "Graphics.h"
#include "InputManager.h"

namespace vie
{
	
	Engine::Engine() :
		isRunning(false),
		FPS(0),
		maxFPS(60)
	{
	}

	Engine::~Engine()
	{
	}

	void Engine::runEngine(const char *title, unsigned int sw, unsigned int sh, WindowFlags windowFlags)
	{
		if (isRunning)
		{
			printf("Error: The Engine is running");
			return;
		}

		initSDLAndWindow(title, sw, sh, windowFlags);

		onCreate();

		isRunning = true;
		mainLoop();
		
		destroyEngine();
	}

	void Engine::initSDLAndWindow(const char *title, unsigned int sw, unsigned int sh, WindowFlags windowFlags) {
		SDL_Init(SDL_INIT_EVERYTHING);

		Window::create(title, sw, sh, windowFlags);

		createGlewContextAndCatchErrors();

		printf("*** OpenGL Version: %s ***\n", glGetString(GL_VERSION));

		glClearColor(0.25f, 0.25f, 0.25f, 1.0f);

		g = new Graphics();
		g->init(Window::getScreenWidth(), Window::getScreenHeight());
	}

	void Engine::createGlewContextAndCatchErrors()
	{
		SDL_GLContext glContext = Window::getSDLGLContext();

		if (glContext == nullptr)
			fatalError("SDL_GL context could not be created!");

		if (glewInit() != GLEW_OK)
			fatalError("Glew could not be initialized!");
	}

	void Engine::mainLoop()
	{
		unsigned int startTicks, stopTicks;
		float elapsedTimeFromPreviousFrame = 0.0f;

		int fpsCount = 0;
		unsigned int timer = SDL_GetTicks();

		while (isRunning)
		{
			startTicks = SDL_GetTicks();
			fpsCount++;

			processInput();
			update(elapsedTimeFromPreviousFrame);
			Window::updateScreenSizeFromSDL();

			g->begin();
			render(g);
			g->end();
			g->renderBatch();
			Window::swapSDLWindowBuffer();

			stopTicks = SDL_GetTicks();
			limitFPS(stopTicks - startTicks);

			// Count elapsed time AFTER FPS limit
			elapsedTimeFromPreviousFrame = (SDL_GetTicks() - startTicks) / 1000.0f;

			if (stopTicks - timer >= 1000)
			{
				timer += 1000;
				FPS = fpsCount;
				fpsCount = 0;

				printf("FPS: %d\n", FPS);
				printf("ET: %f\n\n", elapsedTimeFromPreviousFrame);
			}
		}
	}

	void Engine::processInput()
	{
		SDL_Event evnt;

		while (SDL_PollEvent(&evnt))
		{
			switch (evnt.type)
			{
			case SDL_QUIT:
				destroyEngine();
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
					onMouseDrag(glm::vec2(evnt.motion.x, evnt.motion.y));
				else
					onMouseMove(glm::vec2(evnt.motion.x, evnt.motion.y));
				break;
			}
		}
	}

	void Engine::limitFPS(unsigned int elapsedMillis)
	{
		float maxET = 1000.0f / maxFPS;
		if (maxET > elapsedMillis) 
			SDL_Delay(maxET - elapsedMillis);
	}

	void Engine::destroyEngine()
	{
		onDestroy();

		Window::destroySDLWindow();
		SDL_Quit();
		exit(0);
	}

	unsigned int Engine::getFpsCount() 
	{ return FPS; }

	// Default bodies (it's not necessary to use them)
	void Engine::onCreate() {}
	void Engine::onDestroy() {}
	void Engine::onKeyPress(unsigned int keyID) {}
	void Engine::onKeyRelease(unsigned int keyID) {}
	void Engine::onMousePress(unsigned int keyID, glm::vec2 mousePos) {}
	void Engine::onMouseRelease(unsigned int keyID, glm::vec2 mousePos) {}
	void Engine::onMouseMove(glm::vec2 mousePos) {}
	void Engine::onMouseDrag(glm::vec2 mousePos) {}
}