#include "pch.h"

#include <vie/ObjectsManager.h>

TEST(ObjectsManagerTest, ShouldAppend_Object)
{
	vie::ObjectsManager om(nullptr);
	vie::Object* object = new vie::Object();

	EXPECT_FALSE(om.containsObject(object));

	om.appendObject(object);
	EXPECT_TRUE(om.containsObject(object));
}

TEST(ObjectsManagerTest, ShouldAppend_Mouse_Listener)
{
	vie::ObjectsManager om(nullptr);
	vie::Object* object = new vie::Object();

	EXPECT_FALSE(om.containsMouseListener(object));

	om.appendMouseListener(object);
	EXPECT_TRUE(om.containsMouseListener(object));
}

TEST(ObjectsManagerTest, ShouldAppend_Key_Listener)
{
	vie::ObjectsManager om(nullptr);
	vie::Object* object = new vie::Object();

	EXPECT_FALSE(om.containsKeyListener(object));
	
	om.appendKeyListener(object);
	EXPECT_TRUE(om.containsKeyListener(object));
}

TEST(ObjectsManagerTest, ShouldAppend_All)
{
	vie::ObjectsManager om(nullptr);
	vie::Object* object = new vie::Object();

	EXPECT_FALSE(om.containsObject(object));
	EXPECT_FALSE(om.containsMouseListener(object));
	EXPECT_FALSE(om.containsKeyListener(object));

	om.appendAll(object);
	EXPECT_TRUE(om.containsObject(object));
	EXPECT_TRUE(om.containsMouseListener(object));
	EXPECT_TRUE(om.containsKeyListener(object));
}

TEST(ObjectsManagerTest, Should_Contains_Object_WithLabel)
{
	vie::ObjectsManager om(nullptr);
	vie::Object* object = new vie::Object();
	object->setLabel("test_label");

	EXPECT_FALSE(om.containsObjectWithLabel("test_label"));

	om.appendObject(object);
	EXPECT_TRUE(om.containsObjectWithLabel("test_label"));
}

TEST(ObjectsManagerTest, Should_Contains_Mouse_Listener_WithLabel)
{
	vie::ObjectsManager om(nullptr);
	vie::Object* object = new vie::Object();
	object->setLabel("test_label");

	EXPECT_FALSE(om.containsMouseListenerWithLabel("test_label"));

	om.appendMouseListener(object);
	EXPECT_TRUE(om.containsMouseListenerWithLabel("test_label"));
}

TEST(ObjectsManagerTest, Should_Contains_Key_Listener_WithLabel)
{
	vie::ObjectsManager om(nullptr);
	vie::Object* object = new vie::Object();
	object->setLabel("test_label");

	EXPECT_FALSE(om.containsKeyListenerWithLabel("test_label"));

	om.appendKeyListener(object);
	EXPECT_TRUE(om.containsKeyListenerWithLabel("test_label"));
}

TEST(ObjectsManagerTest, ShouldRemove_Object)
{
	vie::ObjectsManager om(nullptr);
	vie::Object* object = new vie::Object();

	om.appendObject(object);
	EXPECT_TRUE(om.containsObject(object));

	om.removeObject(object);
	EXPECT_FALSE(om.containsObject(object));
}

TEST(ObjectsManagerTest, ShouldRemove_Mouse_Listener)
{
	vie::ObjectsManager om(nullptr);
	vie::Object* object = new vie::Object();

	om.appendMouseListener(object);
	EXPECT_TRUE(om.containsMouseListener(object));

	om.removeMouseListener(object);
	EXPECT_FALSE(om.containsMouseListener(object));
}

TEST(ObjectsManagerTest, ShouldRemove_Key_Listener)
{
	vie::ObjectsManager om(nullptr);
	vie::Object* object = new vie::Object();

	om.appendKeyListener(object);
	EXPECT_TRUE(om.containsKeyListener(object));

	om.removeKeyListener(object);
	EXPECT_FALSE(om.containsKeyListener(object));
}

TEST(ObjectsManagerTest, ShouldRemove_All)
{
	vie::ObjectsManager om(nullptr);
	vie::Object* object = new vie::Object();

	om.appendAll(object);
	EXPECT_TRUE(om.containsObject(object));
	EXPECT_TRUE(om.containsMouseListener(object));
	EXPECT_TRUE(om.containsKeyListener(object));

	om.removeAll(object);
	EXPECT_FALSE(om.containsObject(object));
	EXPECT_FALSE(om.containsMouseListener(object));
	EXPECT_FALSE(om.containsKeyListener(object));
}

TEST(ObjectsManagerTest, ShouldDestroy_Object)
{
	vie::ObjectsManager om(nullptr);
	vie::Object* object = new vie::Object();

	om.appendAll(object);
	om.destroyObject(object);
	EXPECT_FALSE(om.containsObject(object));
	EXPECT_FALSE(om.containsMouseListener(object));
	EXPECT_FALSE(om.containsKeyListener(object));

	EXPECT_EQ(nullptr, object);
}

TEST(ObjectsManagerTest, ShouldReturn_Object_ByLabel)
{
	vie::ObjectsManager om(nullptr);
	vie::Object* object = new vie::Object();
	object->setLabel("test_label");
	om.appendObject(object);
	EXPECT_EQ(object, om.getObjectByLabel("test_label"));
}

TEST(ObjectsManagerTest, ShouldReturn_nullptr_IfNo_Object_WithLabel)
{
	vie::ObjectsManager om(nullptr);
	EXPECT_EQ(nullptr, om.getObjectByLabel("wrong_label_name"));
}

TEST(ObjectsManagerTest, ShouldReturn_Mouse_Listener_ByLabel)
{
	vie::ObjectsManager om(nullptr);
	vie::Object* object = new vie::Object();
	object->setLabel("test_label");
	om.appendMouseListener(object);
	EXPECT_EQ(object, om.getMouseListenerByLabel("test_label"));
}

TEST(ObjectsManagerTest, ShouldReturn_nullptr_IfNo_Mouse_Listener_WithLabel)
{
	vie::ObjectsManager om(nullptr);
	EXPECT_EQ(nullptr, om.getMouseListenerByLabel("wrong_label_name"));
}

TEST(ObjectsManagerTest, ShouldReturn_Key_Listener_ByLabel)
{
	vie::ObjectsManager om(nullptr);
	vie::Object* object = new vie::Object();
	object->setLabel("test_label");
	om.appendKeyListener(object);
	EXPECT_EQ(object, om.getKeyListenerByLabel("test_label"));
}

TEST(ObjectsManagerTest, ShouldReturn_nullptr_IfNo_Key_Listener_WithLabel)
{
	vie::ObjectsManager om(nullptr);
	EXPECT_EQ(nullptr, om.getKeyListenerByLabel("wrong_label_name"));
}

TEST(ObjectsManagerTest, ShouldReturn_objectsVector)
{
	vie::ObjectsManager om(nullptr);
	EXPECT_EQ(0, om.getObjectsVector().size());

	vie::Object* object = new vie::Object();
	om.appendObject(object);
	EXPECT_EQ(1, om.getObjectsVector().size());
	EXPECT_EQ(object, om.getObjectsVector()[0]);
}