#pragma once

#include <glm/glm.hpp>

#include "Graphics.h"

namespace vie
{
	class CollisionBody;

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
		void setVelocity(const glm::vec2& nvel);
		void setAcceleration(const glm::vec2& nvel);
		void setSize(const glm::vec2& nsize);
		void setRotate(float nrotate);
		void setRotateVel(float nrotateVel);
		void setRotateAcc(float nrotateAcc);
		void setIsMouseHover(bool flag);
		void setLabel(const std::string& nlabel);
		void setCollisionBody(CollisionBody* ncollisionBody);

		void createDefaultCollisionBody();

		glm::vec2 getPosition() const;
		glm::vec2 getVelocity() const;
		glm::vec2 getAcceleration() const;

		glm::vec2 getSize() const;

		float getRotate() const;
		float getRotateVel() const;
		float getRotateAcc() const;

		bool getIsMouseHover() const;
		bool isPointInside(const glm::vec2& point) const;

		bool hasCollisionBody() const;
		CollisionBody* getCollisionBody() const;

		bool isLabeled(const std::string& lab) const;
		std::string getLabel() const;

	protected:
		glm::vec2 position;
		glm::vec2 velocity;
		glm::vec2 acceleration;

		glm::vec2 size;
		
		float rotate;
		float rotateVel;
		float rotateAcc;

		CollisionBody* collisionBody;

		bool isMouseHover;

		std::string label;
	};

}
