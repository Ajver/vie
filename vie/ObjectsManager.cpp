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

	void ObjectsManager::appendObject(Object* ob)
	{
		objects.push_back(ob);
	}

	Object* ObjectsManager::getObject(size_t id) const
	{
		return objects[id];
	}

	void ObjectsManager::appendMouseInteractiveObject(Object* ob)
	{
		mouseInteractiveObjects.push_back(ob);
	}

	Object* ObjectsManager::getMouseInteractiveObject(size_t id) const
	{
		return mouseInteractiveObjects[id];
	}

	void ObjectsManager::appendKeyInteractiveObject(Object* ob)
	{
		keyInteractiveObjects.push_back(ob);
	}

	Object* ObjectsManager::getKeyInteractiveObject(size_t id) const
	{
		return keyInteractiveObjects[id];
	}

	void ObjectsManager::onKeyPress()
	{
		forAllObjectsRunFunction(keyInteractiveObjects, [](Object* ob) {
			ob->onKeyPress();
		});
	}

	void ObjectsManager::onKeyRelease()
	{
		forAllObjectsRunFunction(keyInteractiveObjects, [](Object* ob) {
			ob->onKeyRelease();
		});
	}

	void ObjectsManager::onMousePress()
	{
		forAllObjectsRunFunction(mouseInteractiveObjects, [](ObjectsManager* m, Object* ob) {
			if (ob->isPointInside(InputManager::getMousePosition()))
				m->mouseClickedObject(ob);
		});
	}

	void ObjectsManager::mouseClickedObject(Object* ob)
	{
		clickedObject = ob;
		ob->onMousePress();
	}

	void ObjectsManager::onMouseRelease()
	{
		if (clickedObject == nullptr)
			return;

		if (clickedObject->isPointInside(InputManager::getMousePosition()))
			mouseReleasedClickedObject();
		else
			mouseReleasedOutsideClickedObject();

		clickedObject = nullptr;
	}

	void ObjectsManager::mouseReleasedClickedObject()
	{
		clickedObject->onMouseRelease();
	}

	void ObjectsManager::mouseReleasedOutsideClickedObject()
	{
		clickedObject->setIsMouseHover(false);
	}

	void ObjectsManager::onMouseMove() 
	{
		forAllObjectsRunFunction(mouseInteractiveObjects, [](ObjectsManager* m, Object* ob) {
			if (ob->isPointInside(InputManager::getMousePosition()))
				m->mouseIsInsideObject(ob);
			else
				m->mouseIsOutsideObject(ob);
		});
	}

	void ObjectsManager::mouseIsInsideObject(Object* ob)
	{
		if (!ob->getIsMouseHover())
			mouseEnteredObject(ob);

		ob->onMouseMove();
	}

	void ObjectsManager::mouseEnteredObject(Object* ob)
	{
		ob->setIsMouseHover(true);
		ob->onMouseEnter();
	}

	void ObjectsManager::mouseIsOutsideObject(Object* ob)
	{
		if (ob->getIsMouseHover())
			mouseLeavedObject(ob);
	}

	void ObjectsManager::mouseLeavedObject(Object* ob)
	{
		ob->setIsMouseHover(false);
		ob->onMouseLeave();
	}

	void ObjectsManager::onMouseDrag()
	{
		if (clickedObject != nullptr)
			clickedObject->onMouseDrag();
	}

	void ObjectsManager::forAllObjectsRunFunction(const std::vector<Object*>& vtr, void(*fnc)(ObjectsManager*, Object*))
	{
		if (vtr.size() == 0)
			return;

		Object* currentObject = vtr[0];
		for (int i = 0; i < vtr.size(); i++)
		{
			fnc(this, currentObject);
			currentObject++;
		}
	}

	void ObjectsManager::forAllObjectsRunFunction(const std::vector<Object*>& vtr, void(*fnc)(Object*))
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
