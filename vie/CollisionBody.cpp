#include "CollisionBody.h"

#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtx/rotate_vector.hpp>

#include "Object.h"

namespace vie
{

	CollisionBody::CollisionBody(vie::Object* nob, std::vector<glm::vec2> npoints) :
		ob(nob),
		points(npoints)
	{
	}

	CollisionBody::~CollisionBody()
	{
	}

	CollisionBody* CollisionBody::createDefault(vie::Object* nob)
	{
		glm::vec2 halfSize(nob->getSize() * 0.5f);

		return new CollisionBody(nob,
			{ 
				// Top-left point
				-halfSize,

				// Top-right point
				{ halfSize.x, -halfSize.y },

				// Bottom-right point
				halfSize,

				// Bottom-left point
				{ -halfSize.x, halfSize.y }
			});
	}

	void CollisionBody::setPoint(int i, glm::vec2 np)
	{
		points[i] = np;
	}

	glm::vec2 CollisionBody::getPosition() const
	{
		return ob->getPosition();
	}

	float CollisionBody::getRotate() const
	{
		return ob->getRotate();
	}

	glm::vec2 CollisionBody::getPoint(int i) const
	{
		return glm::rotate(points[i], ob->getRotate());
	}

	int CollisionBody::getPointsSize() const
	{
		return points.size();
	}

}