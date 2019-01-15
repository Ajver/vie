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
		objects.clear();
		mouseListeners.clear();
		keyListeners.clear();
	}

	void ObjectsManager::update(float et)
	{
		for (int i = 0; i < objects.size(); i++)
			objects[i]->update(et);
	}

	void ObjectsManager::render(Graphics* g)
	{
		for (int i = 0; i < objects.size(); i++)
			objects[i]->render(g);
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
		mouseListeners.push_back(ob);
	}

	Object* ObjectsManager::getMouseInteractiveObject(size_t id) const
	{
		return mouseListeners[id];
	}

	void ObjectsManager::appendKeyInteractiveObject(Object* ob)
	{
		keyListeners.push_back(ob);
	}

	Object* ObjectsManager::getKeyInteractiveObject(size_t id) const
	{
		return keyListeners[id];
	}

	void ObjectsManager::onKeyPress()
	{
		forAllObjectsRunFunction(keyListeners, [](Object* ob) {
			ob->onKeyPress();
		});
	}

	void ObjectsManager::onKeyRelease()
	{
		forAllObjectsRunFunction(keyListeners, [](Object* ob) {
			ob->onKeyRelease();
		});
	}

	void ObjectsManager::onMousePress()
	{
		forAllObjectsRunFunction(mouseListeners, [](ObjectsManager* m, Object* ob) {
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
		if (isNoClickedObject())
			return;

		if (clickedObject->isPointInside(InputManager::getMousePosition()))
			mouseReleasedClickedObject();
		else
			mouseReleasedOutsideClickedObject();

		clickedObject = nullptr;
	}

	bool ObjectsManager::isNoClickedObject()
	{
		return clickedObject == nullptr;
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
		forAllObjectsRunFunction(mouseListeners, [](ObjectsManager* m, Object* ob) {
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
		if (isNoClickedObject())
			return;

		clickedObject->onMouseDrag();
	}

	void ObjectsManager::forAllObjectsRunFunction(const std::vector<Object*>& vtr, void(*fnc)(ObjectsManager*, Object*))
	{
		for (int i = 0; i < vtr.size(); i++)
			fnc(this, vtr[i]);
	}

	void ObjectsManager::forAllObjectsRunFunction(const std::vector<Object*>& vtr, void(*fnc)(Object*))
	{
		for (int i = 0; i < vtr.size(); i++)
			fnc(vtr[i]);
	}
}
