#pragma once

#include <vector>
#include "Texture.h"
#include "Timer.h"


namespace vie
{

	class Animation
	{
	public:
		Animation();

		// duration in milliseconds
		Animation(const std::vector<Texture*> ntextures, ulong duration);
		Animation(const std::vector<Texture*> ntextures, const Timer& ntimer);

		// Update animation. 
		// Returns false if still running 
		// Returns true if animation done 
		bool update();

		void start();
		void start(ulong duration);
		void restart();
		void pause();
		void stop();

		void setCurrentTexture(Texture* ntex);
		void setTextures(const std::vector<Texture*> ntextures);
		void setDuration(ulong duration);
		void setTimer(const Timer& ntimer);

		// progress should be in range <0; 1>. If out of range it will be shrinked.
		void setProgress(float progress);

		std::vector<Texture*> getTextures() const;
		Texture* getCurrentTexture() const;
		Timer getTimer() const;
		size_t getCurrentTextureIndex() const;

	private:
		std::vector<Texture*> textures;
		Timer timer;
	};

}
