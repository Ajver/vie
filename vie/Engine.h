#pragma once

#include "glm/glm.hpp"

namespace vie
{
	class Graphics;
	class Window;

	class Engine
	{
	public:
		Engine();
		~Engine();

		// Runs once after all systems init
		virtual void onCreate();

		// Runs every frame
		// Update all object (Elapsed Time from previous frame)
		virtual void update(float et) abstract;

		// Runs every frame after update()
		// Render all stuff (graphics object for displaying everything)
		virtual void render(Graphics* g) abstract;

		enum WindowFlags : unsigned int
		{
			// Noresizable, visible window
			DEFAULT = 0x0,

			// Window invisible
			INVISIBLE = 0x1,

			// Borderless and fillign the screen
			FULLSCREEN = 0x2,

			// Noresizable
			BORDERLESS = 0x4,

			// Resizable, with border
			RESIZABLE = 0x8
		};

	protected:
		
		// Init all systems and run the vEngine (title, screen width, screen height, window type)
		void run(const char* title = "vie Engine", 
			unsigned int sw = 640, 
			unsigned int sh = 480, 
			WindowFlags windowFlags = WindowFlags::DEFAULT);

		// Get Window Width
		unsigned int getScreenWidth();

		// Get Window Height
		unsigned int getScreenHeight();

		// Get FPS count from previous frame (updated after each second)
		unsigned int getFpsCount();

		virtual void onKeyPress(unsigned int keyID);
		virtual void onKeyRelease(unsigned int keyID);
		virtual void onMousePress(unsigned int keyID, glm::vec2 mousePos);
		virtual void onMouseRelease(unsigned int keyID, glm::vec2 mousePos);
		virtual void onMouseMove(glm::vec2 mousePos);
		virtual void onMouseDrag(glm::vec2 mousePos);

	private:
		bool isRunning;

		// Frames per second
		unsigned int FPS;

		// Maximum Frames per second
		unsigned int maxFPS;

		Window* window;

		// Draw all stuff with this
		Graphics* g;

		// Grab mouse and key events
		void processInput();

		// Init all systems (title, screen width, screen height, window type)
		void init(const char* title,
			unsigned int sw,
			unsigned int sh,
			WindowFlags windowFlags);
	};

}

