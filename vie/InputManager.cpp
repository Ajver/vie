#include "InputManager.h"

//#include <SDL/SDL.h>

namespace vie
{
	std::unordered_map<unsigned int, bool> InputManager::keysMap;
	glm::vec2 InputManager::mousePosition;
	unsigned int InputManager::lastKey;

	void InputManager::setKey(unsigned int id, bool flag)
	{
		lastKey = id;
		keysMap[id] = flag;
	}

	void InputManager::setMousePosition(float x, float y)
	{
		mousePosition.x = x;
		mousePosition.y = y;
	}

	bool InputManager::isKeyPressed(unsigned int keyID)
	{
		if (keysMap.find(keyID) != keysMap.end())
			return keysMap[keyID];
		

		return false;
	}

	glm::vec2 InputManager::getMousePosition()
	{
		return mousePosition;
	}

	float InputManager::getMouseX()
	{
		return mousePosition.x;
	}

	float InputManager::getMouseY()
	{
		return mousePosition.y;
	}

	bool InputManager::isSomeMouseButtonPressed()
	{
		return isKeyPressed(SDL_BUTTON_LEFT) ||
			isKeyPressed(SDL_BUTTON_MIDDLE) ||
			isKeyPressed(SDL_BUTTON_RIGHT);
	}

	unsigned int InputManager::getLastKey()
	{
		return lastKey;
	}
}