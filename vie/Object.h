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

		virtual void update(float et);
		virtual void render(Graphics* g);

		virtual void onKeyPress();
		virtual void onKeyRelease();
		virtual void onMouseEnter();
		virtual void onMouseLeave();
		virtual void onMouseMove();
		virtual void onMouseDrag();
		virtual void onMousePress();
		virtual void onMouseRelease();

		void setPosition(const glm::vec2& npos);
		void setSize(const glm::vec2& nsize);
		void setVelocity(const glm::vec2& nvel);
		void setIsMouseHover(bool flag);

		glm::vec2 getPosition() const;
		glm::vec2 getSize() const;
		glm::vec2 getVelocity() const;
		bool getIsMouseHover() const;

		bool isPointInside(const glm::vec2& point) const;

	protected:
		glm::vec2 position;
		glm::vec2 size;
		glm::vec2 velocity;
		
		bool isMouseHover;

	};

}
