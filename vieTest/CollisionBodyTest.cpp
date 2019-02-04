#include "pch.h"

#include <vie/CollisionBody.h>
#include <vie/Object.h>

TEST(CollisionBodyTest, Should_CreateDefaultCollisionBody)
{
	vie::Object* o = new vie::Object();
	o->setSize({ 64, 128 });

	vie::CollisionBody* cb = vie::CollisionBody::createDefault(o);
	EXPECT_EQ(4, cb->getPointsSize());
	EXPECT_EQ(glm::vec2(-32, -64), cb->getPoint(0));
	EXPECT_EQ(glm::vec2( 32, -64), cb->getPoint(1));
	EXPECT_EQ(glm::vec2( 32,  64), cb->getPoint(2));
	EXPECT_EQ(glm::vec2(-32,  64), cb->getPoint(3));
}

TEST(CollisionBodyTest, Should_ReturnObjectPosition)
{
	vie::Object* o = new vie::Object();
	o->setPosition({ 100, 200 });

	vie::CollisionBody* cb = new vie::CollisionBody(o, {});
	o->setCollisionBody(cb);

	EXPECT_EQ(glm::vec2(100, 200), cb->getPosition());
}

TEST(CollisionBodyTest, Should_ReturnObjectRotate)
{
	vie::Object* o = new vie::Object();
	o->setRotate(3.14f);

	vie::CollisionBody* cb = new vie::CollisionBody(o, {});
	o->setCollisionBody(cb);

	EXPECT_EQ(3.14f, cb->getRotate());
}

TEST(CollisionBodyTest, Should_SetPoint)
{
	vie::Object* o = new vie::Object();
	vie::CollisionBody* cb = new vie::CollisionBody(o, { { 0, 0 } });

	EXPECT_EQ(glm::vec2(0, 0), cb->getPoint(0));

	cb->setPoint(0, { 10, 20 });
	EXPECT_EQ(glm::vec2(10, 20), cb->getPoint(0));
}

TEST(CollisionBodyTest, Should_CreateWithSpecificPoints)
{
	vie::CollisionBody* cb = new vie::CollisionBody(new vie::Object(),
		{
			{ 10, 10 },
			{ 20, 20 },
			{ 30, 30 }
		});

	EXPECT_EQ(3, cb->getPointsSize());
	EXPECT_EQ(glm::vec2(10, 10), cb->getPoint(0));
	EXPECT_EQ(glm::vec2(20, 20), cb->getPoint(1));
	EXPECT_EQ(glm::vec2(30, 30), cb->getPoint(2));
}

TEST(CollisionBody, Should_ReturnRotatedPoint)
{
	vie::Object* o = new vie::Object();
	o->setRotate(3.14f);

	vie::CollisionBody* cb = new vie::CollisionBody(o, { { 10, 15 } });

	glm::vec2 rotatedPoint = glm::rotate(glm::vec2(10, 15), 3.14f);
	EXPECT_EQ(rotatedPoint, cb->getPoint(0));
}