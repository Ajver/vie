#include "Engine.h"

#include <SDL/SDL.h>
#include <GL/glew.h>
#include <Box2D/Box2D.h>

#include <string>

#include "Window.h"
#include "Errors.h"
#include "Graphics.h"
#include "ObjectsManager.h"
#include "Input.h"
#include "Camera2D.h"

namespace vie
{
	
	Engine::Engine() :
		isRunning(false),
		FPS(0),
		maxFPS(60),
		graphics(nullptr),
		mainCamera(nullptr),
		b_world(nullptr),
		velocityIterations(8),
		positionIterations(3)
	{
	}

	Engine::~Engine()
	{
		delete objectsManager;
		delete graphics;
		delete mainCamera;
		delete b_world;
	}

	void Engine::runEngine(const char* title, WindowFlags windowFlags)
	{
		runEngine(title, 728, 480, windowFlags);
	}

	void Engine::runEngine(const char *title, unsigned int sw, unsigned int sh, WindowFlags windowFlags)
	{
		if (isRunning)
		{
			printf("Error: The Engine is running\n");
			return;
		}

		initSDLAndWindowAndGraphics(title, sw, sh, windowFlags);

		onCreate();

		isRunning = true;
		mainLoop();
		
		destroy();
	}

	void Engine::initSDLAndWindowAndGraphics(const char *title, unsigned int sw, unsigned int sh, WindowFlags windowFlags) {
		SDL_Init(SDL_INIT_EVERYTHING);

		Window::create(title, sw, sh, windowFlags);

		createGlewContextAndCatchErrors();
		
		mainCamera = new Camera2D();
		mainCamera->init();

		graphics = new Graphics();
		graphics->init(mainCamera);

		objectsManager = new ObjectsManager();
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

		unsigned int fpsCount = 0;
		unsigned int timer = SDL_GetTicks();

		while (isRunning)
		{
			startTicks = SDL_GetTicks();
			fpsCount++;

			processInput();
			processUpdate(elapsedTimeFromPreviousFrame);
			processRender();

			stopTicks = SDL_GetTicks();
			limitFPS(stopTicks - startTicks);

			// Count elapsed time AFTER FPS limit
			elapsedTimeFromPreviousFrame = (SDL_GetTicks() - startTicks) / 1000.0f;

			if (stopTicks - timer >= 1000)
			{
				timer += 1000;
				FPS = fpsCount;
				fpsCount = 0;
			}
		}
	}

	void Engine::processUpdate(float elapsedTimeFromPreviousFrame)
	{
		Window::updateScreenSizeFromSDL();
		update(elapsedTimeFromPreviousFrame);
		if (b_world != nullptr)
		{
			if(getFpsCount() != 0)
				b_world->Step(1.0f / getFpsCount(), velocityIterations, positionIterations);
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
				destroy();
				break;
			case SDL_KEYDOWN:
				Input::setKey(evnt.key.keysym.sym, true);
				objectsManager->onKeyPress();
				onKeyPress();
				break;
			case SDL_KEYUP:
				Input::setKey(evnt.key.keysym.sym, false);
				objectsManager->onKeyRelease();
				onKeyRelease();
				break;
			case SDL_MOUSEBUTTONDOWN:
				Input::setKey(evnt.button.button, true);
				objectsManager->onMousePress();
				onMousePress();
				break;
			case SDL_MOUSEBUTTONUP:
				Input::setKey(evnt.button.button, false);
				objectsManager->onMouseRelease();
				onMouseRelease();
				break;
			case SDL_MOUSEMOTION:
				Input::setMousePosition(evnt.motion.x, evnt.motion.y);

				if (Input::isSomeMouseButtonPressed())
				{
					onMouseDrag();
					objectsManager->onMouseDrag();
				}
				else
				{
					onMouseMove();
					objectsManager->onMouseMove();
				}
				break;
			}
		}
	}

	void Engine::processRender()
	{
		render(graphics);
		graphics->render();
		Window::swapSDLWindowBuffer();
	}

	void Engine::limitFPS(unsigned int elapsedMillis)
	{
		if (maxFPS < 0)
			return;

		float maxET = 1000.0f / maxFPS;
		if (maxET > elapsedMillis) 
			SDL_Delay(maxET - elapsedMillis);
	}

	void Engine::destroy()
	{
		onDestroy();

		Window::destroySDLWindow();
		SDL_Quit();
		exit(0);
	}

	void Engine::destroyEngine()
	{
		isRunning = false;
	}

	unsigned int Engine::getFpsCount() 
	{ 
		return FPS; 
	}

	char* Engine::getOpenGLVersion()
	{
		return (char*)glGetString(GL_VERSION);
	}

	void Engine::setFPSLimit(unsigned int nMaxFps)
	{
		maxFPS = nMaxFps;
	}

	void Engine::createWorld(const glm::vec2& gravity)
	{
		b_world = new b2World(b2Vec2(gravity.x, gravity.y));
	}

	// Default bodies (it's not necessary to use them)
	void Engine::onCreate() {}
	void Engine::onDestroy() {}
	void Engine::onKeyPress() {}
	void Engine::onKeyRelease() {}
	void Engine::onMousePress() {}
	void Engine::onMouseRelease() {}
	void Engine::onMouseMove() {}
	void Engine::onMouseDrag() {}
}