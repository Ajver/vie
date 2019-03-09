#include "Animation.h"


namespace vie
{

	Animation::Animation()
	{
	}

	Animation::Animation(const std::vector<Texture*> ntextures, ulong duration) :
		textures(ntextures),
		timer(duration)
	{
	}

	Animation::Animation(const std::vector<Texture*> ntextures, const Timer& ntimer) :
		textures(ntextures),
		timer(ntimer)
	{
	}

	bool Animation::update()
	{
		return timer.tick();
	}

	void Animation::start()
	{
		timer.start();
	}

	void Animation::start(ulong duration)
	{
		timer.start(duration);
	}

	void Animation::restart()
	{
		timer.restart();
	}

	void Animation::pause()
	{
		timer.pause();
	}

	void Animation::stop()
	{
		timer.stop();
	}

	void Animation::setCurrentTexture(Texture* ntex)
	{
		textures[getCurrentTextureIndex()] = ntex;
	}

	void Animation::setTextures(const std::vector<Texture*> ntextures)
	{
		textures = ntextures;
	}

	void Animation::setDuration(ulong duration)
	{
		timer.setDuration(duration);
	}

	void Animation::setTimer(const Timer& ntimer)
	{
		timer = ntimer;
	}

	void Animation::setProgress(float progress)
	{
		timer.setProgress(progress);
	}

	std::vector<Texture*> Animation::getTextures() const
	{
		return textures;
	}

	Texture* Animation::getCurrentTexture() const
	{
		return textures[getCurrentTextureIndex()];
	}

	Timer Animation::getTimer() const
	{
		return timer;
	}

	size_t Animation::getCurrentTextureIndex() const
	{
		size_t idx = (int)(timer.getProgress() * textures.size());

		if (idx < textures.size())
			return idx;

		return textures.size() - 1;
	}

}
