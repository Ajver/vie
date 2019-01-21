#include "pch.h"

#include <glm/glm.hpp>
#include "../vie/Object.cpp"
#include "../vie/ObjectsManager.cpp"
#include "../vie/InputManager.cpp"

TEST(ObjectsManagerTest, ShouldAppendObject)
{
	vie::ObjectsManager om;
	vie::Object* object = new vie::Object();

	EXPECT_FALSE(om.containsObject(object));

	om.appendObject(object);
	EXPECT_TRUE(om.containsObject(object));
}

TEST(ObjectsManagerTest, ShouldAppendMouseListener)
{
	vie::ObjectsManager om;
	vie::Object* object = new vie::Object();

	EXPECT_FALSE(om.containsMouseListener(object));

	om.appendMouseListener(object);
	EXPECT_TRUE(om.containsMouseListener(object));
}

TEST(ObjectsManagerTest, ShouldAppendKeyListener)
{
	vie::ObjectsManager om;
	vie::Object* object = new vie::Object();

	EXPECT_FALSE(om.containsKeyListener(object));
	
	om.appendKeyListener(object);
	EXPECT_TRUE(om.containsKeyListener(object));
}
