#pragma once

#include <unordered_map>
#include <glm/glm.hpp>

namespace vie
{

	class InputManager
	{
	public:
		InputManager();
		~InputManager();

		static void setKey(unsigned int id, bool flag);
		static void setMousePosition(float x, float y);

		static bool isKeyPressed(unsigned int keyID);
		static glm::vec2 getMousePosition();
		static float getMouseX();
		static float getMouseY();

	private:
		static std::unordered_map<unsigned int, bool> keysMap;
		static glm::vec2 mousePosition;
	};

}
