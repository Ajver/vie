#include "ObjectsManager.h"

#include "Errors.h"
#include "InputManager.h"

#include <iostream>

namespace vie
{

	ObjectsManager::ObjectsManager() :
		clickedObject(nullptr)
	{
	}

	ObjectsManager::~ObjectsManager()
	{
		Object* currentObject = objects[0];
		for (int i = 0; i < objects.size(); i++)
		{
			delete currentObject;
			currentObject++;
		}
		objects.clear();

		currentObject = mouseInteractiveObjects[0];
		for (int i = 0; i < mouseInteractiveObjects.size(); i++)
		{
			delete currentObject;
			currentObject++;
		}
		mouseInteractiveObjects.clear();

		currentObject = keyInteractiveObjects[0];
		for (int i = 0; i < keyInteractiveObjects.size(); i++)
		{
			delete currentObject;
			currentObject++;
		}
		keyInteractiveObjects.clear();
	}

	void ObjectsManager::update(float et)
	{
		if (objects.size() == 0)
			return;

		Object* currentObject = objects[0];
		for (int i = 0; i < objects.size(); i++)
		{
			currentObject->update(et);
			currentObject++;
		}
	}

	void ObjectsManager::render(Graphics* g)
	{
		if (objects.size() == 0)
			return;

		Object* currentObject = objects[0];
		for (int i = 0; i < objects.size(); i++)
		{
			currentObject->render(g);
			currentObject++;
		}
	}

	void ObjectsManager::appendObject(vie::Object* ob)
	{
		objects.push_back(ob);
	}

	vie::Object* ObjectsManager::getObject(size_t id) const
	{
		return objects[id];
	}

	void ObjectsManager::appendMouseInteractiveObject(vie::Object* ob)
	{
		mouseInteractiveObjects.push_back(ob);
	}

	vie::Object* ObjectsManager::getMouseInteractiveObject(size_t id) const
	{
		return mouseInteractiveObjects[id];
	}

	void ObjectsManager::appendKeyInteractiveObject(vie::Object* ob)
	{
		keyInteractiveObjects.push_back(ob);
	}

	vie::Object* ObjectsManager::getKeyInteractiveObject(size_t id) const
	{
		return keyInteractiveObjects[id];
	}

	//////////////////////////////////////////////////////////

	void ObjectsManager::onKeyPress(unsigned int keyID)
	{
		if (keyInteractiveObjects.size() == 0)
			return;

		Object* currentObject = keyInteractiveObjects[0];
		for (int i = 0; i < keyInteractiveObjects.size(); i++)
		{
			currentObject->onKeyPress(keyID);
			currentObject++;
		}
	}

	void ObjectsManager::onKeyRelease(unsigned int keyID)
	{
		if (keyInteractiveObjects.size() == 0)
			return;

		Object* currentObject = keyInteractiveObjects[0];
		for (int i = 0; i < keyInteractiveObjects.size(); i++)
		{
			currentObject->onKeyRelease(keyID);
			currentObject++;
		}
	}

	void ObjectsManager::onMousePress(unsigned int keyID)
	{
		if (mouseInteractiveObjects.size() == 0)
			return;

		Object* currentObject = mouseInteractiveObjects[0];
		for (int i = 0; i < mouseInteractiveObjects.size(); i++)
		{
			if (currentObject->isPointInside(InputManager::getMousePosition()))
				mouseClickedObject(currentObject, keyID);

			currentObject++;
		}
	}

	void ObjectsManager::mouseClickedObject(vie::Object* ob, unsigned int keyID)
	{
		clickedObject = ob;
		ob->onMousePress(keyID);
	}

	void ObjectsManager::onMouseRelease(unsigned int keyID)
	{
		if (clickedObject == nullptr)
			return;

		if (clickedObject->isPointInside(InputManager::getMousePosition()))
			mouseReleasedClickedObject(keyID);
		else
			mouseReleasedOutsideClickedObject();

		clickedObject = nullptr;
	}

	void ObjectsManager::mouseReleasedClickedObject(unsigned int keyID)
	{
		clickedObject->onMouseRelease(keyID);
	}

	void ObjectsManager::mouseReleasedOutsideClickedObject()
	{
		clickedObject->setIsMouseHover(false);
	}

	void* checkgMouseMoved(vie::Object* ob);
	void* fooo(vie::Object* ob)
	{
		if (ob->isPointInside(InputManager::getMousePosition()))
			;// mouseIsInsideObject(ob);
		else
			;// mouseIsOutsideObject(ob);

		return nullptr;
	}

	void ObjectsManager::onMouseMove() 
	{
		forAllElementsRunFunction(mouseInteractiveObjects, ((void*) ObjectsManager::*)checkMouseMoved);
	}

	void* ObjectsManager::checkMouseMoved(vie::Object* ob)
	{
		if (ob->isPointInside(InputManager::getMousePosition()))
			mouseIsInsideObject(ob);
		else
			mouseIsOutsideObject(ob);

		return nullptr;
	}

	void ObjectsManager::mouseIsInsideObject(vie::Object* ob)
	{
		if (!ob->getIsMouseHover())
			mouseEnteredObject(ob);

		ob->onMouseMove();
	}

	void ObjectsManager::mouseEnteredObject(vie::Object* ob)
	{
		ob->setIsMouseHover(true);
		ob->onMouseEnter();
	}

	void ObjectsManager::mouseIsOutsideObject(vie::Object* ob)
	{
		if (ob->getIsMouseHover())
			mouseLeavedObject(ob);
	}

	void ObjectsManager::mouseLeavedObject(vie::Object* ob)
	{
		ob->setIsMouseHover(false);
		ob->onMouseLeave();
	}

	void ObjectsManager::onMouseDrag()
	{
		if (clickedObject != nullptr)
			clickedObject->onMouseDrag();
	}

	void ObjectsManager::forAllElementsRunFunction(const std::vector<vie::Object*>& vtr, void* ObjectsManager::* fnc(vie::Object* ob)) const
	{
		if (vtr.size() == 0)
			return;

		Object* currentObject = vtr[0];
		for (int i = 0; i < vtr.size(); i++)
		{
			fnc(currentObject);
			currentObject++;
		}
	}
}
