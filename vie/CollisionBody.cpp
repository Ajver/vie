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

	bool CollisionBody::isColliding(CollisionBody* other)
	{
		if (mayBeCollision(other))
			return checkCollisionAndBoundIfWant(other, false);
		else
			return false;
	}

	bool CollisionBody::mayBeCollision(CollisionBody* other) const
	{
		float minDist = getRadius() + other->getRadius();
		return glm::distance(ob->getPosition(), other->getPosition()) < minDist;
	}

	bool CollisionBody::bound(CollisionBody* other)
	{
		if (mayBeCollision(other))
			return checkCollisionAndBoundIfWant(other, true);
		else
			return false;
	}

	bool CollisionBody::checkCollisionAndBoundIfWant(CollisionBody* other, bool wantBound)
	{
		/*
			Algorithm comes from Javidx9: https://www.youtube.com/watch?v=7Ik2vowGcU0
		*/

		CollisionBody* shape1 = this;
		CollisionBody* shape2 = other;

		for (int shape = 0; shape < 2; shape++)
		{
			if (shape == 1)
			{
				shape1 = other;
				shape2 = this;
			}

			// Check diagonals of polygon...
			const int poly1size = shape1->getPointsSize();
			for (int diag = 0; diag < poly1size; diag++)
			{
				glm::vec2 pos = shape1->getPosition();
				glm::vec2 p1 = shape1->getPoint(diag);

				glm::vec2 displacement(0, 0);

				// ...against edges of the other
				const int poly2size = shape2->getPointsSize();
				for (int q = 0; q < poly2size; q++)
				{
					glm::vec2 s2first = shape2->getPoint(q);
					glm::vec2 s2second = shape2->getPoint((q + 1) % poly2size);

					// Standard "off the shelf" line segment intersection
					float h = (s2second.x - s2first.x) * (pos.y - p1.y) - (pos.x - p1.x) * (s2second.y - s2first.y);
					float t1 = ((s2first.y - s2second.y) * (pos.x - s2first.x) + (s2second.x - s2first.x) * (pos.y - s2first.y)) / h;
					float t2 = ((pos.y - p1.y) * (pos.x - s2first.x) + (p1.x - pos.x) * (pos.y - s2first.y)) / h;

					if (t1 >= 0.0f && t1 < 1.0f && t2 >= 0.0f && t2 < 1.0f)
						if (wantBound)
						{
							// TODO - It is not working fine...
							displacement.x += (1.0f - t1) * (p1.x - pos.x);
							displacement.y += (1.0f - t1) * (p1.y - pos.y);
						}
						else
							return true;
				}

				if (wantBound)
					if (!isStatic)
						if (!other->getIsStatic())
						{
							 this->moveObject(displacement * -0.5f);
							other->moveObject(displacement * 0.5f);
						}
						else
							moveObject(-displacement);
					else if (!other->getIsStatic())
						other->moveObject(displacement);
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

	void CollisionBody::moveObject(const glm::vec2& moveVec)
	{
		ob->moveBy(moveVec);
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
		return glm::rotate(points[i], ob->getRotate()) + ob->getPosition();
	}

	int CollisionBody::getPointsSize() const
	{
		return points.size();
	}

	bool CollisionBody::getIsStatic() const
	{
		return isStatic;
	}

	float CollisionBody::getRadius() const
	{
		if (points.size() == 0)
			return 0;

		float topRadius = glm::length(points[0]);

		for (auto& p : points)
		{
			float rad = glm::length(p);
			if (rad > topRadius)
				topRadius = rad;
		}
		
		return topRadius;
	}

}