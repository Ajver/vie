#pragma once

#include <unordered_map>
#include <glm/glm.hpp>
#include <SDL/SDL.h>

namespace vie
{

	class Input
	{
	public:
		static void setKey(unsigned int id, bool flag);
		static void setMousePosition(float x, float y);

		static bool isKeyPressed(unsigned int keyID);
		static glm::vec2 getMousePosition();
		static float getMouseX();
		static float getMouseY();
		static bool isSomeMouseButtonPressed();
		static unsigned int getLastKey();
	
	private:
		static std::unordered_map<unsigned int, bool> keysMap;
		static glm::vec2 mousePosition;
		static unsigned int lastKey;
	};

}
