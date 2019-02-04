#pragma once

#include <vector>
#include <glm/glm.hpp>

namespace vie
{
	class Object;

	class CollisionBody
	{
	public:
		CollisionBody(vie::Object* nob, std::vector<glm::vec2> npoints);
		~CollisionBody();

		static CollisionBody* createDefault(vie::Object* nob);

		void setPoint(int i, glm::vec2 np);
		void setIsStatic(bool flag);

		glm::vec2 getPosition() const;
		float getRotate() const;

		glm::vec2 getPoint(int i) const;
		int getPointsSize() const;
		bool getIsStatic() const;

	private:
		CollisionBody();

		vie::Object* ob;
		std::vector<glm::vec2> points;

		bool isStatic;

	};

}
