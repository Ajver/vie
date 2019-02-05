#include "Object.h"

#include <string>


namespace vie
{

	Object::Object() :
		position(0, 0),
		velocity(0, 0),
		acceleration(0, 0),
		size(0, 0),
		rotate(0),
		rotateVel(0),
		rotateAcc(0)
	{
	}

	Object::~Object()
	{
	}

	void Object::moveBy(const glm::vec2& moveVec)
	{
		position += moveVec;
	}

	void Object::setPosition(const glm::vec2& npos)
	{
		position = npos;
	}

	void Object::setVelocity(const glm::vec2& nvel)
	{
		velocity = nvel;
	}

	void Object::setAcceleration(const glm::vec2& nacc)
	{
		acceleration = nacc;
	}

	void Object::setSize(const glm::vec2& nsize)
	{
		// TODO - Should update size of collision body too
		size = nsize;
	}

	void Object::rotateBy(float rotateMod)
	{
		rotate += rotateMod;
	}

	void Object::setRotate(float nrotate)
	{
		rotate = nrotate;
	}

	void Object::setRotateVel(float nrotateVel)
	{
		rotateVel = nrotateVel;
	}

	void Object::setRotateAcc(float nrotateAcc)
	{
		rotateAcc = nrotateAcc;
	}

	void Object::setIsMouseHover(bool flag)
	{
		isMouseHover = flag;
	}

	void Object::setLabel(const std::string& nlabel)
	{
		label = nlabel;
	}

	glm::vec2 Object::getPosition() const
	{
		return position;
	}

	glm::vec2 Object::getVelocity() const
	{
		return velocity;
	}

	glm::vec2 Object::getAcceleration() const
	{
		return acceleration;
	}

	glm::vec2 Object::getSize() const
	{
		return size;
	}

	float Object::getRotate() const
	{
		return rotate;
	}

	float Object::getRotateVel() const
	{
		return rotateVel;
	}

	float Object::getRotateAcc() const
	{
		return rotateAcc;
	}

	bool Object::getIsMouseHover() const
	{
		return isMouseHover;
	}
	
	std::string Object::getLabel() const
	{
		return label;
	}

	bool Object::isPointInside(const glm::vec2& point) const
	{
		return point.x >= position.x &&
			point.x < position.x + size.x &&
			point.y >= position.y &&
			point.y < position.y + size.y;
	}

	bool Object::isLabeled(const std::string& lab) const
	{
		return label == lab;
	}

	void Object::update(float et) {}
	void Object::render(Graphics* g) {}

	void Object::onMouseEnter() {}
	void Object::onMouseLeave() {}
	void Object::onMouseMove() {}
	void Object::onMouseDrag() {}
	void Object::onMousePress() {}
	void Object::onMouseRelease() {}
	void Object::onKeyPress() {}
	void Object::onKeyRelease() {}

}