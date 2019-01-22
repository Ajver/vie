#include "pch.h"

#include "../vie/ObjectsManager.h"

TEST(ObjectsManagerTest, ShouldAppend_Object)
{
	vie::ObjectsManager om;
	vie::Object* object = new vie::Object();

	EXPECT_FALSE(om.containsObject(object));

	om.appendObject(object);
	EXPECT_TRUE(om.containsObject(object));
}

TEST(ObjectsManagerTest, ShouldAppend_Mouse_Listener)
{
	vie::ObjectsManager om;
	vie::Object* object = new vie::Object();

	EXPECT_FALSE(om.containsMouseListener(object));

	om.appendMouseListener(object);
	EXPECT_TRUE(om.containsMouseListener(object));
}

TEST(ObjectsManagerTest, ShouldAppend_Key_Listener)
{
	vie::ObjectsManager om;
	vie::Object* object = new vie::Object();

	EXPECT_FALSE(om.containsKeyListener(object));
	
	om.appendKeyListener(object);
	EXPECT_TRUE(om.containsKeyListener(object));
}

TEST(ObjectsManagerTest, ShouldRemove_Object)
{
	vie::ObjectsManager om;
	vie::Object* object = new vie::Object();

	om.appendObject(object);
	EXPECT_TRUE(om.containsObject(object));

	om.removeObject(object);
	EXPECT_FALSE(om.containsObject(object));
}

TEST(ObjectsManagerTest, ShouldRemove_Mouse_Listener)
{
	vie::ObjectsManager om;
	vie::Object* object = new vie::Object();

	om.appendMouseListener(object);
	EXPECT_TRUE(om.containsMouseListener(object));

	om.removeMouseListener(object);
	EXPECT_FALSE(om.containsMouseListener(object));
}

TEST(ObjectsManagerTest, ShouldRemove_Key_Listener)
{
	vie::ObjectsManager om;
	vie::Object* object = new vie::Object();

	om.appendKeyListener(object);
	EXPECT_TRUE(om.containsKeyListener(object));

	om.removeKeyListener(object);
	EXPECT_FALSE(om.containsKeyListener(object));
}