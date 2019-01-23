#include "pch.h"

#include <vie/Camera2D.h>

glm::vec2 getTransformedPoint(glm::vec2 point);
vie::Camera2D getUpdatedCamera();
vie::Camera2D getInitedCamera();

TEST(CameraTest, Should_HasValidDefaultParameters)
{
	vie::Camera2D camera;
	EXPECT_EQ(glm::vec2(0.0f, 0.0f), camera.getPosition());
	EXPECT_EQ(1.0f, camera.getScale());
	EXPECT_EQ(0.0f, camera.getRotate());
	EXPECT_TRUE(camera.getNeedsMatrixUpdate());
}

TEST(CameraTest, Should_Update)
{
	vie::Camera2D camera;
	EXPECT_TRUE(camera.getNeedsMatrixUpdate());

	camera.update();
	EXPECT_FALSE(camera.getNeedsMatrixUpdate());
}

TEST(CameraTest, ShouldSet_Position)
{
	vie::Camera2D camera = getUpdatedCamera();
	camera.setPosition(glm::vec2(10.0f, 5.0f));
	EXPECT_EQ(glm::vec2(10.0f, 5.0f), camera.getPosition());
	EXPECT_TRUE(camera.getNeedsMatrixUpdate());
}

TEST(CameraTest, ShouldSet_Position_ByRotatedVector)
{
	vie::Camera2D camera = getUpdatedCamera();
	camera.setRotate(1.0f);
	camera.setPosition(glm::vec2(10.0f, 5.0f));
	glm::vec2 point(10.0f, 5.0f);
	EXPECT_EQ(glm::rotate(point, -1.0f), camera.getPosition());
}

TEST(CameraTest, ShouldSet_Scale)
{
	vie::Camera2D camera = getUpdatedCamera();
	camera.setScale(2.0f);
	EXPECT_EQ(2.0f, camera.getScale());
	EXPECT_TRUE(camera.getNeedsMatrixUpdate());
}

TEST(CameraTest, ShouldSet_Rotate)
{
	vie::Camera2D camera = getUpdatedCamera();
	camera.setRotate(2.0f);
	EXPECT_EQ(2.0f, camera.getRotate());
	EXPECT_TRUE(camera.getNeedsMatrixUpdate());
}

TEST(CameraTest, Should_Move)
{
	vie::Camera2D camera = getUpdatedCamera();
	camera.move(glm::vec2(10.0f, 5.0f));
	EXPECT_EQ(glm::vec2(10.0f, 5.0f), camera.getPosition());

	camera.move(glm::vec2(-35.0f, -30.0f));
	EXPECT_EQ(glm::vec2(-25.0f, -25.0f), camera.getPosition());

	EXPECT_TRUE(camera.getNeedsMatrixUpdate());
}

TEST(CameraTest, Should_Move_ByRotatedVector)
{
	vie::Camera2D camera = getUpdatedCamera();
	camera.setRotate(1.0f);
	camera.move(glm::vec2(10.0f, 5.0f));
	glm::vec2 point(10.0f, 5.0f);
	EXPECT_EQ(glm::rotate(point, -1.0f), camera.getPosition());
}

TEST(CameraTest, Should_ScaleUp)
{
	vie::Camera2D camera = getUpdatedCamera();
	camera.scaleUp(1.5f);
	EXPECT_EQ(1.5f, camera.getScale());

	camera.scaleUp(1.5f);
	EXPECT_EQ(2.25f, camera.getScale());

	EXPECT_TRUE(camera.getNeedsMatrixUpdate());
}

TEST(CameraTest, Should_ScaleDown)
{
	vie::Camera2D camera = getUpdatedCamera();
	camera.scaleDown(0.5f);
	EXPECT_EQ(2.0f, camera.getScale());

	camera.scaleDown(4.0f);
	EXPECT_EQ(0.5f, camera.getScale());

	EXPECT_TRUE(camera.getNeedsMatrixUpdate());
}

TEST(CameraTest, Should_Rotate)
{
	vie::Camera2D camera = getUpdatedCamera();
	camera.rotate(2.0f);
	EXPECT_EQ(2.0f, camera.getRotate());

	camera.rotate(-3.0f);
	EXPECT_EQ(-1.0f, camera.getRotate());

	EXPECT_TRUE(camera.getNeedsMatrixUpdate());
}

TEST(CameraTest, Should_Not_ChangeOriginalVec2)
{
	vie::Camera2D camera = getUpdatedCamera();
	glm::vec2 newCameraPosition(10.0f, 5.0f);
	camera.setPosition(newCameraPosition);
	camera.move(glm::vec2(20.0f, -15.0f));
	EXPECT_EQ(glm::vec2(30.0f, -10.0f), camera.getPosition());
	EXPECT_EQ(glm::vec2(10.0f, 5.0f), newCameraPosition);
}

TEST(CameraTest, Should_TransformScreenToWorldPos)
{
	vie::Camera2D camera = getUpdatedCamera();
	camera.setScale(2.0f);
	camera.setPosition(glm::vec2(30.0f, 50.0f));

	glm::vec2 point = getTransformedPoint(glm::vec2(100.0f, 10.0f));

	EXPECT_EQ(point, camera.screenToWorldPos(glm::vec2(100.0f, 10.0f)));
}


glm::vec2 getTransformedPoint(glm::vec2 point)
{
	point.x -= SCREEN_W * 0.5f;
	point.y -= SCREEN_H * 0.5f;
	point /= 2.0f;
	point.x += 30.0f;
	point.y += 50.0f;

	return point;
}

vie::Camera2D getUpdatedCamera()
{
	vie::Camera2D camera;
	camera.update();
	return camera;
}

vie::Camera2D getInitedCamera()
{
	vie::Camera2D camera;
	camera.init();
	return camera;
}