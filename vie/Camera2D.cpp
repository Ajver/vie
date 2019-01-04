#include "Camera2D.h"

namespace vie
{

	Camera2D::Camera2D() :
		position(0.0f, 0.0f),
		cameraMatrix(1.0f),
		scale(1.0f),
		needsMatrixUpdate(true),
		screenWidth(500),
		screenHeight(500),
		orthoMatrix(1.0f)
	{
	}
	
	Camera2D::~Camera2D()
	{
	}

	void Camera2D::init(int sw, int sh)
	{
		screenWidth = sw;
		screenHeight = sh;

		orthoMatrix = glm::ortho(0.0f, (float)screenWidth, 0.0f, (float)screenHeight);
	}

	void Camera2D::update()
	{
		if (needsMatrixUpdate)
		{
			// Camera translation
			glm::vec3 translateVec(-position.x + screenWidth * 0.5f, -position.y + screenHeight * 0.5f, 0.0f);
			cameraMatrix = glm::translate(orthoMatrix, translateVec);

			// Camera scale
			glm::vec3 scaleVec(scale, scale, 0.0f);
			cameraMatrix = glm::scale(glm::mat4(1.0f), scaleVec) * cameraMatrix;

			needsMatrixUpdate = false;
		}
	}

	glm::vec2 Camera2D::screenToWorldPos(glm::vec2 screenPosition)
	{
		screenPosition -= glm::vec2(screenWidth * 0.5f, screenHeight * 0.5f);
		screenPosition /= scale;
		screenPosition += position;

		return screenPosition;
	}

	void Camera2D::setPosition(glm::vec2 npos)
	{
		position = npos;
		needsMatrixUpdate = true;
	}

	void Camera2D::setScale(float nscale)
	{
		scale = nscale;
		needsMatrixUpdate = true;
	}

	glm::vec2 Camera2D::getPosition()
	{
		return position;
	}

	float Camera2D::getScale()
	{
		return scale;
	}

	glm::mat4 Camera2D::getCameraMatrix()
	{
		return cameraMatrix;
	}

}
