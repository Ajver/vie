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
	class Window
	{
	public:
		Window() : sdlWindow(nullptr), 
			screenWidth(0), 
			screenHeight(0) 
		{
		}

		void create(const char* title, unsigned int sw, unsigned int sh, Engine::WindowFlags wFlags)
		{
			saveWindowProperties(title, sw, sh, wFlags);

			createSDLWindow();
			
			if (sdlWindow == nullptr)
			{
				fatalError(SDL_GetError());
			}
		}

		void setWindowSize(unsigned int sw, unsigned int sh)
		{
			screenWidth = sw;
			screenHeight = sh;
			updateScreenSize();
		}

		void setWindowTitle(const char* title)
		{
			windowTitle = title;
		}

		SDL_GLContext getSDLGLContext()
		{
			return SDL_GL_CreateContext(sdlWindow);
		}

		void swapSDLWindowBuffer()
		{
			SDL_GL_SwapWindow(sdlWindow);
		}

		void destroySDLWindow()
		{
			SDL_DestroyWindow(sdlWindow);
		}

		unsigned int getScreenWidth()
		{
			return screenWidth;
		}

		unsigned int getScreenHeight()
		{
			return screenHeight;
		}

		bool isWindowInvisible()
		{
			return windowFlags & Engine::WindowFlags::INVISIBLE;
		}

		bool isWindowFullscreen()
		{
			return windowFlags & Engine::WindowFlags::FULLSCREEN;
		}

		bool isWindowBorderless()
		{
			return windowFlags & Engine::WindowFlags::BORDERLESS;
		}

		bool isWindowResizable()
		{
			return windowFlags & Engine::WindowFlags::RESIZABLE;
		}

	private:
		SDL_Window* sdlWindow;
		const char* windowTitle;
		unsigned int screenWidth;
		unsigned int screenHeight;
		Engine::WindowFlags windowFlags;

		void saveWindowProperties(const char* title, unsigned int sw, unsigned int sh, Engine::WindowFlags wFlags)
		{
			windowTitle = title;
			screenWidth = sw;
			screenHeight = sh;
			windowFlags = wFlags;
		}

		void createSDLWindow()
		{
			Uint32 sdlFlags = getSDLWindowFlags();
			sdlWindow = SDL_CreateWindow(
				windowTitle, 
				SDL_WINDOWPOS_CENTERED, 
				SDL_WINDOWPOS_CENTERED, 
				screenWidth, 
				screenHeight, 
				sdlFlags);
		}

		Uint32 getSDLWindowFlags()
		{
			Uint32 sdlFlags = SDL_WINDOW_OPENGL;

			if (isWindowInvisible())
				sdlFlags |= SDL_WINDOW_HIDDEN;

			if (isWindowFullscreen())
				sdlFlags |= SDL_WINDOW_FULLSCREEN_DESKTOP;

			if (isWindowBorderless())
				sdlFlags |= SDL_WINDOW_BORDERLESS;

			if (isWindowResizable())
				sdlFlags |= SDL_WINDOW_RESIZABLE;

			return sdlFlags;
		}

		void updateScreenSize()
		{
			SDL_SetWindowSize(sdlWindow, screenWidth, screenHeight);
		}

		void updateWindowTitle()
		{
			SDL_SetWindowTitle(sdlWindow, windowTitle);
		}
	};

	Engine::Engine() :
		isRunning(false),
		window(nullptr),
		FPS(0),
		maxFPS(60)
	{
	}

	Engine::~Engine()
	{
	}

	void Engine::run(const char *title, unsigned int sw, unsigned int sh, WindowFlags windowFlags)
	{
		if (isRunning)
		{
			printf("Error: The Engine is running");
			return;
		}

		init(title, sw, sh, windowFlags);

		onCreate();

		float elapsedTimeFromPreviousFrame = 0.0f;

		int fpsCount = 0;
		unsigned int timer = SDL_GetTicks();

		isRunning = true;

		while (isRunning) 
		{
			unsigned int startTicks = SDL_GetTicks();

			fpsCount++;

			processInput();
			update(elapsedTimeFromPreviousFrame);

			g->begin();
			
			render(g);

			g->end();
			g->renderBatch();

			window->swapSDLWindowBuffer();

			unsigned int stopTicks = SDL_GetTicks();

			// Count elapsed time
			elapsedTimeFromPreviousFrame = (stopTicks - startTicks);// / 1000.0f;
			
			// Limit the fps to the max fps
			float maxET = 1000.0f / maxFPS;
			if (maxET > elapsedTimeFromPreviousFrame) {
				SDL_Delay(maxET - elapsedTimeFromPreviousFrame);
			}

			// Count elapsed time AFTER FPS limited
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
		
		window->destroySDLWindow();
		delete window;

		// Exit program
		SDL_Quit();
		exit(0);
	}

	void Engine::init(const char *title, unsigned int sw, unsigned int sh, WindowFlags windowFlags) {
		SDL_Init(SDL_INIT_EVERYTHING);

		window = new Window();
		window->create(title, sw, sh, windowFlags);

		// Setup Glew
		SDL_GLContext glContext = window->getSDLGLContext();

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

		glClearColor(0.25f, 0.25f, 0.25f, 1.0f);

		// Enable alpha blend
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

		g = new Graphics();
		g->init(getScreenWidth(), getScreenHeight());
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
		return window->getScreenWidth();
	}

	unsigned int Engine::getScreenHeight() 
	{
		return window->getScreenHeight();
	}

	unsigned int Engine::getFpsCount() 
	{
		return FPS;
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