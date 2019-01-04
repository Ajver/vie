#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

namespace vie
{

	class Camera2D
	{
	public:
		Camera2D();
		~Camera2D();

		void init(int sw, int sh);
		void update();

		void setPosition(glm::vec2 npos);
		void setScale(float nscale);

		glm::vec2 screenToWorldPos(glm::vec2 screenPosition);

		glm::vec2 getPosition();
		float getScale();
		glm::mat4 getCameraMatrix();

	private:
		int screenWidth;
		int screenHeight;

		bool needsMatrixUpdate;

		glm::vec2 position;
		glm::mat4 cameraMatrix;
		glm::mat4 orthoMatrix;

		float scale;
	};

}