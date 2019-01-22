#include "pch.h"

#include <vie/Camera2D.h>

glm::vec2 getTransformedPoint(glm::vec2 point);

TEST(CameraTest, ShouldSet_Position)
{
	vie::Camera2D camera;
	camera.setPosition(glm::vec2(10.0f, 5.0f));
	EXPECT_EQ(glm::vec2(10.0f, 5.0f), camera.getPosition());
}

TEST(CameraTest, ShouldSet_Scale)
{
	vie::Camera2D camera;
	camera.setScale(2.0f);
	EXPECT_EQ(2.0f, camera.getScale());
}

TEST(CameraTest, Should_Move)
{
	vie::Camera2D camera;
	camera.move(glm::vec2(10.0f, 5.0f));
	EXPECT_EQ(glm::vec2(10.0f, 5.0f), camera.getPosition());

	camera.move(glm::vec2(-35.0f, -30.0f));
	EXPECT_EQ(glm::vec2(-25.0f, -25.0f), camera.getPosition());
}

TEST(CameraTest, Should_ScaleUp)
{
	vie::Camera2D camera;
	camera.scaleUp(1.5f);
	EXPECT_EQ(1.5f, camera.getScale());

	camera.scaleUp(1.5f);
	EXPECT_EQ(2.25f, camera.getScale());
}

TEST(CameraTest, Should_ScaleDown)
{
	vie::Camera2D camera;
	camera.scaleDown(0.5f);
	EXPECT_EQ(2.0f, camera.getScale());

	camera.scaleDown(4.0f);
	EXPECT_EQ(0.5f, camera.getScale());
}

TEST(CameraTest, Should_Not_ChangeOriginalVec2)
{
	vie::Camera2D camera;
	glm::vec2 newCameraPosition(10.0f, 5.0f);
	camera.setPosition(newCameraPosition);
	camera.move(glm::vec2(20.0f, -15.0f));
	EXPECT_EQ(glm::vec2(30.0f, -10.0f), camera.getPosition());
	EXPECT_EQ(glm::vec2(10.0f, 5.0f), newCameraPosition);
}

TEST(CameraTest, Should_TransformScreenToWorldPos)
{
	vie::Camera2D camera;
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