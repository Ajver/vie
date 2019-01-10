#pragma once

#include <glm/glm.hpp>
#include "Graphics.h"

namespace vie
{

	class Object
	{
	public:
		Object();
		~Object();

		virtual void update(float et) abstract;
		virtual void render(Graphics* g) abstract;

		void setPosition(const glm::vec2& npos);
		void setSize(const glm::vec2& nsize);
		void setVelocity(const glm::vec2& nvel);

		glm::vec2 getPosition();
		glm::vec2 getSize();
		glm::vec2 getVelocity();

	protected:
		glm::vec2 position;
		glm::vec2 size;
		glm::vec2 velocity;
	};

}
