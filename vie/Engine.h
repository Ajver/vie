#pragma once

#include <glm/glm.hpp>

#include "WindowFlags.h"
#include "Graphics.h"


class b2World;

namespace vie
{
	class ObjectsManager;
	class Camera2D;

	class Engine
	{
	public:
		Engine();
		~Engine();

		char* getOpenGLVersion();

		// Get FPS count from previous frame (updated after each second)
		unsigned int getFpsCount();

	protected:
		ObjectsManager* objectsManager;

		// Draw all stuff with this
		Graphics* graphics;
		Camera2D* mainCamera;

		// Physics world from Box2D lib. 
		// It is NOT automaticly created!
		b2World* b_world;

		// Runs once after all systems init
		virtual void onCreate();

		// Runs every frame
		// Update all object (Elapsed Time from previous frame)
		virtual void update(float et);

		// Runs every frame after update()
		// Render all stuff (graphics object for displaying everything)
		virtual void render(Graphics* g);

		// Runs once before all systems destroy
		virtual void onDestroy();

		// Init all systems and run the vEngine (title, screen width, screen height, window type)
		void runEngine(const char* title = "vie Engine", 
			unsigned int sw = 728, 
			unsigned int sh = 480, 
			WindowFlags windowFlags = WindowFlags::DEFAULT);

		void runEngine(const char* title = "vie Engine",
			WindowFlags windowFlags = WindowFlags::DEFAULT);

		// If nMaxFps < 0 then no limits!
		// (Default 60)
		void setFPSLimit(unsigned int nMaxFps);

		// Create world with specific gravity (default - no gravity)
		void createWorld(const glm::vec2& gravity = { 0.0f, 0.0f });

		void setVelocityIterations(unsigned int it);
		void setPositionIterations(unsigned int it);
		void setIsWorldUpdating(bool flag);

		unsigned int getVelocityIterations() const;
		unsigned int getPositionIterations() const;
		unsigned int getIsWorldUpdating() const;

		virtual void onKeyPress();
		virtual void onKeyRelease();
		virtual void onMousePress();
		virtual void onMouseRelease();
		virtual void onMouseMove();
		virtual void onMouseDrag();

		// Stop main loop and destroy engine
		void destroyEngine();

	private:
		// Is main loop running?
		bool isRunning;

		// Frames per second
		unsigned int FPS;

		// Maximum Frames per second (default 60)
		unsigned int maxFPS;

		// Variables for Box2D 
		unsigned int b_velocityIterations;
		unsigned int b_positionIterations;
		bool isWorldUpdating;

		// Init all systems (title, screen width, screen height, window type)
		void initSDLAndWindowAndGraphics(const char* title,
			unsigned int sw,
			unsigned int sh,
			WindowFlags windowFlags);
		void createGlewContextAndCatchErrors();

		void mainLoop();
		void processInput();
		void processUpdate(float elapsedTimeFromPreviousFrame);
		void processRender();
		void limitFPS(unsigned int elapsedMillis);

		void destroy();
	};

}

