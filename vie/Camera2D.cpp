#include "Camera2D.h"

#include <glm/gtc/matrix_transform.hpp>

#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtx/rotate_vector.hpp>

#include "Window.h"

namespace vie
{

	Camera2D::Camera2D() :
		position(0.0f, 0.0f),
		cameraMatrix(1.0f),
		scale(1.0f),
		needsMatrixUpdate(true),
		orthoMatrix(1.0f),
		rotateAngleInRadians(0.0f)
	{
	}

	Camera2D::~Camera2D()
	{
	}

	void Camera2D::init()
	{
		orthoMatrix = glm::ortho(0.0f, (float)Window::getScreenWidth(), 0.0f, (float)Window::getScreenHeight());
	}

	void Camera2D::update()
	{
		if (needsMatrixUpdate)
		{
			init();
			
			// Camera translation
			glm::vec3 translateVec(Window::getScreenWidth() * 0.5f, -Window::getScreenHeight() * 0.5f, 0.0f);
			cameraMatrix = glm::translate(orthoMatrix, translateVec);

			// Camera scale
			glm::vec3 scaleVec(scale, scale, 0.0f);
			cameraMatrix = glm::scale(glm::mat4(1.0f), scaleVec) * cameraMatrix;


			needsMatrixUpdate = false;
		}
	}

	glm::vec2 Camera2D::screenToWorldPos(glm::vec2 screenPosition) const
	{
		screenPosition -= glm::vec2(Window::getScreenWidth() * 0.5f, Window::getScreenHeight() * 0.5f);
		screenPosition /= scale;
		screenPosition += position;

		return screenPosition;
	}

	void Camera2D::move(const glm::vec2& translateVector)
	{
		position += glm::rotate(translateVector, -rotateAngleInRadians);
		needsMatrixUpdate = true;
	}

	void Camera2D::scaleUp(float scaleM)
	{
		scale *= scaleM;
		needsMatrixUpdate = true;
	}

	void Camera2D::scaleDown(float scaleM)
	{
		scale /= scaleM;
		needsMatrixUpdate = true;
	}

	void Camera2D::rotate(float angle)
	{
		rotateAngleInRadians += angle;
		needsMatrixUpdate = true;
	}

	void Camera2D::setPosition(const glm::vec2& npos)
	{
		position = glm::rotate(npos, -rotateAngleInRadians);
		needsMatrixUpdate = true;
	}

	void Camera2D::setScale(float nscale)
	{
		scale = nscale;
		needsMatrixUpdate = true;
	}

	void Camera2D::setRotate(float angle)
	{
		rotateAngleInRadians = angle;
		needsMatrixUpdate = true;
	}

	glm::vec2 Camera2D::getPosition() const
	{
		return position;
	}

	float Camera2D::getScale() const
	{
		return scale;
	}

	float Camera2D::getRotate() const
	{
		return rotateAngleInRadians;
	}

	glm::mat4 Camera2D::getCameraMatrix() const
	{
		return cameraMatrix;
	}

	bool  Camera2D::getNeedsMatrixUpdate() const
	{
		return needsMatrixUpdate;
	}

}