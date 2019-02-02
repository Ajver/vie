#pragma once

#include <glm/glm.hpp>

namespace vie
{

	class Camera2D
	{
	public:
		Camera2D();
		~Camera2D();

		void init();
		void update();
		void beginFrame();

		void move(const glm::vec2& translateVector);
		void scaleUp(float scaleM);
		void scaleDown(float scaleM);
		void rotate(float angle);

		void setPosition(const glm::vec2& npos);
		void setScale(float nscale);
		void setRotate(float angle);

		bool isPointInView(glm::vec2 point) const;
		glm::vec2 screenToWorldPos(glm::vec2 screenPosition) const;
		glm::vec2 worldToScreenPos(glm::vec2 worldPosition) const;

		glm::vec2 getPosition() const;
		float getScale() const;
		float getRotate() const;
		glm::mat4 getCameraMatrix() const;

		bool getNeedsMatrixUpdate() const;
		bool getWasUpdatedThisFrame() const;


	private:
		bool needsMatrixUpdate;
		bool wasUpdatedThisFrame;

		glm::vec2 position;
		glm::mat4 cameraMatrix;
		glm::mat4 orthoMatrix;

		float scale;
		float rotateAngleInRadians;
	};

}