#pragma once

#include "glm/glm.hpp"

#include "WindowFlags.h"

namespace vie
{
	class Graphics;

	class Engine
	{
	public:
		Engine();
		~Engine();

	protected:
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

		virtual void onKeyPress(unsigned int keyID);
		virtual void onKeyRelease(unsigned int keyID);
		virtual void onMousePress(unsigned int keyID, glm::vec2 mousePos);
		virtual void onMouseRelease(unsigned int keyID, glm::vec2 mousePos);
		virtual void onMouseMove(glm::vec2 mousePos);
		virtual void onMouseDrag(glm::vec2 mousePos);

		void destroyEngine();

	private:
		bool isRunning;

		// Frames per second
		unsigned int FPS;

		// Maximum Frames per second
		unsigned int maxFPS;

		// Draw all stuff with this
		Graphics* g;

		// Grab mouse and key events
		void processInput();

		// Init all systems (title, screen width, screen height, window type)
		void initSDLAndWindow(const char* title,
			unsigned int sw,
			unsigned int sh,
			WindowFlags windowFlags);

		void createGlewContextAndCatchErrors();

		void mainLoop();
		void limitFPS(unsigned int elapsedMillis);
	};

}

