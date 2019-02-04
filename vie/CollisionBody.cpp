#include "CollisionBody.h"

#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtx/rotate_vector.hpp>

#include "Object.h"

namespace vie
{

	CollisionBody::CollisionBody(vie::Object* nob, std::vector<glm::vec2> npoints) :
		ob(nob),
		points(npoints),
		isStatic(false)
	{
	}

	CollisionBody::~CollisionBody()
	{
	}

	bool CollisionBody::isColliding(CollisionBody* other) const
	{
		return areColliding(this, other);
	}

	bool CollisionBody::areColliding(const CollisionBody* one, const CollisionBody* two)
	{
		for (int shape = 0; shape < 2; shape++)
		{
			if (shape == 1)
			{
				const CollisionBody* temp = one;
				one = two;
				two = temp;
			}

			glm::vec2 pos = one->getPosition();

			int onePSize = one->getPointsSize();
			for (int diag = 0; diag < onePSize; diag++)
			{
				glm::vec2 r(one->getPoint(diag) - pos);

				const int opSize = two->getPointsSize();
				for (int i = 0; i < opSize; i++)
				{
					glm::vec2 op1(two->getPoint(i));
					glm::vec2 op2(two->getPoint((i + 1) % opSize));
					glm::vec2 a(op2 - op1);

					glm::vec2 u(pos - op1);

					float h = a.x * r.y - r.x * a.y;

					float t1 = a.y * u.x + a.x * u.y;
					float t2 = r.y * u.x + r.x * u.y;
					t1 /= h;
					t2 /= h;

					if (t1 >= 0.0f && t1 < 1.0f && t2 >= 0.0f && t2 < 1.0f)
						return true;
				}
			}
		}

		return false;
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

	void CollisionBody::setIsStatic(bool flag)
	{
		isStatic = flag;
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

	bool CollisionBody::getIsStatic() const
	{
		return isStatic;
	}

}