#pragma once

#include "glm/glm.hpp"

#include "WindowFlags.h"

namespace vie
{
	class Graphics;
	class ObjectsManager;

	class Engine
	{
	public:
		Engine();
		~Engine();

		void printOpenGLVersion();

	protected:
		ObjectsManager* objectsManager;

		// Runs once after all systems init
		virtual void onCreate();

		// Runs every frame
		// Update all object (Elapsed Time from previous frame)
		virtual void update(float et) abstract;

		// Runs every frame after update()
		// Render all stuff (graphics object for displaying everything)
		virtual void render(Graphics* g) abstract;

		virtual void onDestroy();

		// Init all systems and run the vEngine (title, screen width, screen height, window type)
		void runEngine(const char* title = "vie Engine", 
			unsigned int sw = 640, 
			unsigned int sh = 480, 
			WindowFlags windowFlags = WindowFlags::DEFAULT);

		// Get FPS count from previous frame (updated after each second)
		unsigned int getFpsCount();

		virtual void onKeyPress();
		virtual void onKeyRelease();
		virtual void onMousePress();
		virtual void onMouseRelease();
		virtual void onMouseMove();
		virtual void onMouseDrag();

		void destroy();

	private:
		bool isRunning;

		// Frames per second
		unsigned int FPS;

		// Maximum Frames per second
		unsigned int maxFPS;

		// Draw all stuff with this
		Graphics* g;

		// Init all systems (title, screen width, screen height, window type)
		void initSDLAndWindowAndGraphics(const char* title,
			unsigned int sw,
			unsigned int sh,
			WindowFlags windowFlags);
		void createGlewContextAndCatchErrors();

		void mainLoop();
		void processInput();
		void manageUpdates(float elapsedTimeFromPreviousFrame);
		void manageRendering();
		void limitFPS(unsigned int elapsedMillis);

		void destroyEngine();
	};

}

