#include "Input.h"

namespace vie
{
	std::unordered_map<unsigned int, bool> Input::keysMap;
	glm::vec2 Input::mousePosition;
	unsigned int Input::lastKey;

	void Input::setKey(unsigned int id, bool flag)
	{
		lastKey = id;
		keysMap[id] = flag;
	}

	void Input::setMousePosition(float x, float y)
	{
		mousePosition.x = x;
		mousePosition.y = y;
	}

	bool Input::isKeyPressed(unsigned int keyID)
	{
		if (keysMap.find(keyID) != keysMap.end())
			return keysMap[keyID];
		
		return false;
	}

	glm::vec2 Input::getMousePosition()
	{
		return mousePosition;
	}

	float Input::getMouseX()
	{
		return mousePosition.x;
	}

	float Input::getMouseY()
	{
		return mousePosition.y;
	}

	bool Input::isSomeMouseButtonPressed()
	{
		return isKeyPressed(SDL_BUTTON_LEFT) ||
			isKeyPressed(SDL_BUTTON_MIDDLE) ||
			isKeyPressed(SDL_BUTTON_RIGHT);
	}

	unsigned int Input::getLastKey()
	{
		return lastKey;
	}
}